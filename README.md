# RFID Access Control - Project R-Alpha

**An RFID access control system using Arduino Nano, RDM6300 RFID Reader, and ST7735 TFT Display.**  
This project reads RFID tags and displays access status with a sleek user interface.

---

## 📦 Devices Used

- 🔌 Arduino Nano
- 📘 RDM6300 RFID Reader (125kHz)
- 🖥️ 1.8" TFT Display (ST7735)

---

## 🧩 Wiring Diagram

### TFT Display (ST7735):

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

### RDM6300 RFID Reader:

| RDM6300 Pin | Arduino Nano Pin |
|-------------|------------------|
| VCC         | 5V               |
| GND         | GND              |
| TX          | D2               |

---

## ⚙️ How It Works

- On power-up, a welcome screen appears with **"Bonjour Null Labz"**.
- The screen prompts **"Scan RFID..."** in blue.
- When an RFID card is scanned:
  - If the card is **authorized**, "Access GRANTED" (green) is shown.
  - If unauthorized, "Access DENIED" (red) is displayed.
- After a 2-second display, it returns to scan mode.

---

## 🧾 Authorized Tag List

You can customize the authorized tag list in the `.ino` file:

```cpp
long allowed_tags[] = {669262, 379461, 372014, 740380};
