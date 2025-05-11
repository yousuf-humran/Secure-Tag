# 🔐 RFID Access Control - Secure Tag

**An RFID access control system using Arduino Nano, RDM6300 RFID Reader, and ST7735 TFT Display.**  
This project reads RFID tags and displays access status with a sleek user interface.

---

## 📦 Devices Used

- 🔌 **Arduino Nano**  
- 📘 **RDM6300 RFID Reader (125kHz)**  
- 🖥️ **1.8" TFT Display (ST7735)**

---

## 🧩 Wiring Diagram

### 🔌 TFT Display (ST7735)

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

### 📘 RDM6300 RFID Reader

| RDM6300 Pin | Arduino Nano Pin |
|-------------|------------------|
| VCC         | 5V               |
| GND         | GND              |
| TX          | D2               |

---

## ⚙️ How It Works

- On power-up, a welcome screen appears with:  
  **`Bonjour Developer`** and  
  **`Project RFID Scanner`**
- The screen prompts: **Scan RFID...** (blue text).
- When an RFID tag is scanned:
  - ✅ If **authorized**, the screen shows:  
    **Access GRANTED** (in green)
  - ❌ If **unauthorized**, the screen shows:  
    **Access DENIED** (in red)
- After 2 seconds, the system returns to scan mode.

---

# 🧾 Authorized Tag List

You can customize the authorized tag list in the `.ino` file by modifying this section:
> ```cpp
> long allowed_tags[] = {669262, 379461, 372014, 740380};
> ```

## 📚 Library Installation Guide

To use this project, install the required libraries directly from the `.zip` files available in the [`Libraries` branch`](https://github.com/yousuf-humran/Secure-Tag/tree/Libraries).

### ✅ Steps

1. Go to the [`Libraries` branch`](https://github.com/yousuf-humran/Secure-Tag/tree/Libraries).
2. Download the following `.zip` files:
   - `Adafruit-GFX-Library-master.zip`
   - `Adafruit_BusIO-master.zip`
   - `Adafruit_ST7735-master.zip`
   - `ArduinoCore-avr-master.zip`
   - `rdm6300-master.zip`
3. Open the **Arduino IDE**.
4. Navigate to:  
   **Sketch** → **Include Library** → **Add .ZIP Library...**
5. One by one, select each downloaded `.zip` file to install.
6. Restart the Arduino IDE if prompted.

> 💡 Once installed, these libraries will be available for use in your sketches. No manual extraction needed.

---

## 👨‍💻 Developed by

**Yousuf Humran & The Null Labz Team**
