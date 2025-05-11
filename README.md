# Secure Tag – RFID Access Control System

**Secure Tag** is a lightweight, real-time access control solution built using the Arduino Nano, RDM6300 RFID Reader (125kHz), and ST7735 TFT Display. It scans RFID tags and displays access status through a user-friendly graphical interface. This project is suitable for prototype-level security, educational demonstrations, or basic access control systems.

---

## Features

- Real-time RFID scanning and validation
- Clear visual interface for access status
- Configurable authorized tag list
- Modular, open-source implementation

---

## Hardware Requirements

| Component                  | Description                        |
|---------------------------|------------------------------------|
| Arduino Nano              | Microcontroller                    |
| RDM6300 RFID Reader       | 125kHz RFID tag scanner            |
| ST7735 TFT Display (1.8") | SPI-based color display            |

---

## Wiring Configuration

### TFT Display (ST7735)

| TFT Pin | Arduino Nano Pin |
|---------|------------------|
| VCC     | 5V               |
| GND     | GND              |
| CS      | D10              |
| RESET   | D9               |
| DC      | D8               |
| SDA     | D11              |
| SCL     | D13              |
| BL      | 5V               |

### RDM6300 RFID Reader

| RFID Pin | Arduino Nano Pin         |
|----------|--------------------------|
| VCC      | 5V                       |
| GND      | GND                      |
| TX       | D2 (RX for SoftwareSerial) |

> Note: Only the TX pin of the RDM6300 is required for data transmission.

---

## System Workflow

1. On power-up, the TFT screen displays a welcome message.
2. The display then prompts: `Scan RFID...`
3. Upon scanning:
   - If the RFID tag is authorized, the screen displays:  
     **Access GRANTED** (in green).
   - If the tag is not recognized, the screen displays:  
     **Access DENIED** (in red).
4. After 2 seconds, the display returns to scan mode.

---

## Configuring Authorized Tags

You can customize the authorized tag list in the `.ino` file by modifying this section:
> ```cpp
> long allowed_tags[] = {669262, 379461, 372014, 740380};
> ```

## Library Dependencies
The following libraries must be installed to compile and run the project:

## Installation Instructions
1. Open the **Arduino IDE**.
2. Go to:  
   `Sketch → Include Library → Manage Libraries...`
3. In the Library Manager, search for and install the following:
   - **Adafruit GFX Library**
   - **Adafruit ST7735 and ST7789 Library**
   - **Adafruit BusIO**

> The **SoftwareSerial** library is bundled with the Arduino AVR boards core and does not require separate installation.

**Developed by:**  
Yousuf Humran



