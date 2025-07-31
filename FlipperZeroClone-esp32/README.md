# 🐬 Flipper Clone with ESP32

This is a DIY clone of the Flipper Zero — a multi-tool device for pentesters, hackers, and hardware tinkerers — built using an ESP32, joystick, OLED display, and various modules (IR, RF, RFID, WiFi, Bluetooth).

## 📦 Features

- 📺 **OLED Display**: 0.91" I2C display
- 🕹️ **Joystick Navigation**: Multi-directional input with press and hold actions
- 🔁 **IR & RF Modules**: Send, receive, save, and replay signals
- 🌐 **WiFi Tools**:
  - Scan networks
  - Deauthentication attack
  - Repeater mode ("Mr. Great Guy")
- 🔒 **RFID/NFC Emulation & Reading**
- 📡 **Bluetooth HID & BLE Extender**:
  - BLE keyboard input
  - Audio redirection
- 💾 **SD Card Support**:
  - Store IR/RF/NFC data and music files
- 🔄 **EEPROM Fallback**: When SD is not present
- 🎵 **Music Player**: Play MP3 files over Bluetooth

# Hardware Used
Component	Details
Microcontroller	ESP32 Dev Module
Display	0.91" OLED (I2C)
Input	Joystick with center press
Storage	SD Card Module
IR	IR LED and receiver
RF	315/433 MHz transmitter/receiver
RFID/NFC	RC522 module
Bluetooth Audio	Built-in ESP32 BT or external module
Power Supply	Li-ion battery or USB

# 🎮 Navigation Controls
Joystick Press: Select item

Joystick Left: Go back

Joystick Right (hold): Shortcut to WiFi Deauth

Joystick Left (hold): WiFi Scan

Joystick Up (hold): IR Blast

Joystick Down (hold): RF Scan

## 📘 Menu Structure
# Main Menu
# IR

IR Scan

IR Send

IR List

# RF

RF Scan

RF Block

# WiFi

WiFi Scan

WiFi Deauth

WiFi Repeater

Bluetooth

HID Keyboard

BLE Audio Extender

# NFC

Read/Emulate NFC Tags

# 💾 Data Management
All scanned IR/RF/NFC data saved to SD card (or EEPROM fallback)

Stored in structured files for easy access

MP3s in SD card /music/ folder

# 🚀 Getting Started
Flash flipperzero.ino to your ESP32 using Arduino IDE

Install required libraries:

Adafruit SSD1306

SPI

Wire

IRremote

MFRC522

ESP32 WiFi

SD

Assemble your hardware modules

Insert SD card (optional)

Power the ESP32 and start exploring!
