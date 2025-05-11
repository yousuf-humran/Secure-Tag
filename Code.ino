/*
  == RFID Project "Secure Tag" ==
  Developed by: Yousuf Humran

  📟 Devices Used:
    - Arduino Nano
    - RDM6300 RFID Reader (125kHz)
    - 1.8" TFT Display (ST7735)

  🧩 Wiring:

  --- TFT Display ---
    VCC  →  5V (Nano)
    GND  →  GND
    CS   →  D10
    RESET→  D9
    DC   →  D8
    SDA  →  D11
    SCL  →  D13
    BL   →  5V

  --- RDM6300 RFID Reader ---
    VCC  →  5V
    GND  →  GND
    TX   →  D2 (Nano RX for SoftwareSerial)

  Note:
    - D3 is unused TX in SoftwareSerial
    - Only RX from RDM6300 is needed
*/

#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// === TFT DISPLAY PINS ===
#define TFT_CS     10
#define TFT_DC     8
#define TFT_RST    9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// === RFID on SoftwareSerial (TX from RDM6300 to D2) ===
SoftwareSerial ssrfid(2, 3); // RX, TX (TX not used)

// === Data Frame Constants ===
const int BUFFER_SIZE       = 14;
const int DATA_SIZE         = 10;
const int DATA_TAG_SIZE     = 8;
const int CHECKSUM_SIZE     = 2;

uint8_t buffer[BUFFER_SIZE];
int buffer_index = 0;
long lasttag     = 0;

// === Authorized Tag List ===
long allowed_tags[] = {669262, 379461, 372014, 740380};
const int num_tags  = sizeof(allowed_tags) / sizeof(allowed_tags[0]);

// === Setup ===
void setup() {
  Serial.begin(9600);
  ssrfid.begin(9600);
  ssrfid.listen();

  // Initialize TFT Display
  tft.initR(INITR_BLACKTAB);

  // Welcome Message
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(2);
  tft.setCursor(5, 30);
  tft.println("Bonjour");
  tft.setCursor(5, 55);
  tft.println("Welcome");

  tft.setTextSize(1);
  tft.setCursor(10, 90);
  tft.println("Project RFID Scanner");

  delay(3000); // Display welcome for 3 seconds
  showScanPrompt(); // Prompt for RFID scan
}

// === Main Loop ===
void loop() {
  if (ssrfid.available() > 0) {
    bool call_extract_tag = false;
    int ssvalue = ssrfid.read();
    if (ssvalue == -1) return;

    if (ssvalue == 2) buffer_index = 0;        // Start of tag frame
    else if (ssvalue == 3) call_extract_tag = true; // End of frame

    if (buffer_index >= BUFFER_SIZE) {
      Serial.println("Buffer overflow");
      return;
    }

    buffer[buffer_index++] = ssvalue;

    if (call_extract_tag && buffer_index == BUFFER_SIZE) {
      extract_tag();
    } else if (call_extract_tag) {
      buffer_index = 0;
      return;
    }
  }
}

// === Tag Authorization Check ===
bool is_allowed(long tag) {
  for (int i = 0; i < num_tags; i++) {
    if (allowed_tags[i] == tag) return true;
  }
  return false;
}

// === Extract Tag and Validate ===
unsigned extract_tag() {
  uint8_t* msg_data_tag = buffer + 3;
  uint8_t* msg_checksum = buffer + 11;

  long tag = hexstr_to_value((char*)msg_data_tag, DATA_TAG_SIZE);

  if (tag != lasttag) {
    Serial.print("Tag: ");
    Serial.println(tag);

    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);

    if (is_allowed(tag)) {
      tft.setTextColor(ST7735_GREEN);
      tft.println("Access");
      tft.setCursor(10, 40);
      tft.println("GRANTED");
    } else {
      tft.setTextColor(ST7735_RED);
      tft.println("Access");
      tft.setCursor(10, 40);
      tft.println("DENIED");
    }

    delay(2000); // Display result
    showScanPrompt(); // Back to scan screen
  }

  lasttag = tag;

  // === Checksum Verification ===
  long checksum = 0;
  for (int i = 0; i < DATA_SIZE; i += CHECKSUM_SIZE) {
    long val = hexstr_to_value((char*)(buffer + 1 + i), CHECKSUM_SIZE);
    checksum ^= val;
  }

  if (checksum != hexstr_to_value((char*)msg_checksum, CHECKSUM_SIZE)) {
    Serial.println("Checksum mismatch");
  }

  return tag;
}

// === Hex String to Long Conversion ===
long hexstr_to_value(char* str, unsigned int length) {
  char copy[11];
  strncpy(copy, str, length);
  copy[length] = '\0';
  return strtol(copy, NULL, 16);
}

// === Display Scan Prompt ===
void showScanPrompt() {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Scan RFID...");
}
