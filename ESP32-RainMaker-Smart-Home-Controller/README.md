# ESP32 Smart Home Controller with RainMaker
This project is an advanced smart home controller based on the ESP32 and the ESP-RainMaker platform. It provides multiple ways to control up to three connected devices via relays: the ESP-RainMaker mobile app, an infrared (IR) remote, and local physical switches. The controller also includes a DHT11 sensor to monitor temperature and humidity, and an LDR to measure ambient light.

# Components Needed
ESP32 Development Board

3-channel Relay Module

3 Tactile Pushbuttons

IR Receiver Module (e.g., VS1838B)

DHT11 Temperature and Humidity Sensor

LDR (Light Dependent Resistor)

A 10k Ohm Resistor (for the LDR)

Jumper wires and a breadboard

# Circuit Connections

Relays: Connect the control pins for the three relays to ESP32 digital pins 23, 22, and 21 respectively.


Physical Switches: Connect the three pushbuttons to ESP32 digital pins 13, 12, and 14, using a INPUT_PULLUP configuration.


IR Receiver: The data pin of the IR receiver connects to ESP32 digital pin 35.


DHT11 Sensor: The data pin of the DHT11 sensor connects to ESP32 digital pin 16.


LDR: Connect one leg of the LDR to 3.3V and the other to ESP32 digital pin 34. Connect a 10k Ohm resistor from the same pin (34) to ground to create a voltage divider.


Status LED: An onboard WiFi LED is connected to digital pin 2.

# Libraries Used
RMaker.h & WiFiProv.h (Part of the ESP-IDF framework, managed by Arduino core for ESP32)

IRremote.h

DHT.h

SimpleTimer.h

AceButton.h

# Code Description
The ESP32_RainMaker_Controller.ino sketch sets up an ESP32 as an IoT hub.


ESP-RainMaker Integration: The device connects to Wi-Fi using ESP-RainMaker provisioning, allowing it to be controlled and monitored via a mobile app. The code defines three switches (

Switch1, Switch2, Switch3) and also reports sensor data from the DHT11 and LDR.


# Control Methods:


App Control: The write_callback function handles commands received from the RainMaker app to turn the relays on or off.




IR Remote: The ir_remote() function decodes IR signals. Pre-defined IR codes (e.g., IR_Button_1) can toggle the state of the relays. A separate command (IR_All_Off) can turn all relays off at once.



Physical Switches: The code uses the AceButton library to handle button presses from the three physical switches, which can also toggle the state of their corresponding relays.


