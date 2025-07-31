# Smart Single-Space Parking System with IoT

## Introduction

[cite_start]This project demonstrates a smart parking system designed for a single parking space[cite: 16]. [cite_start]The system uses a Sonar sensor (HC-SR04) to detect the presence of a car[cite: 16]. [cite_start]When a car parks in the space, the system changes the status from "Available" to "Occupied"[cite: 17]. [cite_start]This status is then indicated by LED lights and uploaded to a cloud platform for remote monitoring and data logging[cite: 18].

## How It Works

[cite_start]The core of the system is an ESP32 microcontroller and an HC-SR04 Sonar sensor[cite: 28, 29]. [cite_start]The Sonar sensor measures the distance to any object in the parking space[cite: 25].
- [cite_start]If the measured distance is less than 200 cm, the system considers the space "Occupied"[cite: 122, 123]. [cite_start]A red LED is turned on to visually indicate this status[cite: 24, 125].
- [cite_start]If the measured distance is greater than or equal to 200 cm, the system considers the space "Available"[cite: 128, 129]. [cite_start]A green LED is turned on to visually indicate this status[cite: 23, 131].

[cite_start]The ESP32 is connected to the internet via Wi-Fi[cite: 98, 112]. [cite_start]It sends the distance and parking status to a ThingSpeak channel[cite: 134, 135]. [cite_start]ThingSpeak is used for cloud integration and keeps a log of the parking space status[cite: 26, 36].

## Component List

The following components were used in this project:
- [cite_start]ESP32 Microcontroller [cite: 28]
- [cite_start]Sonar Sensor (HC-SR04) [cite: 29]
- [cite_start]Green LED [cite: 30]
- [cite_start]Red LED [cite: 31]
- [cite_start]Resistors (330 Ohms) [cite: 32]
- [cite_start]Wires [cite: 33]

## Wire Diagram

The circuit connections are as follows:

- **HC-SR04 Sonar Sensor to ESP32**:
    - [cite_start]`Trigpin` to ESP32 pin 12 [cite: 42]
    - [cite_start]`Echopin` to ESP32 pin 13 [cite: 43]
    - [cite_start]`GND` to ESP32 `GND` [cite: 44]
    - [cite_start]`5V` to ESP32 `VCC/5V` [cite: 45]
- **LEDs to ESP32**:
    - [cite_start]Red LED positive to ESP32 pin 2 [cite: 47]
    - [cite_start]Green LED positive to ESP32 pin 0 [cite: 48]
    - [cite_start]All LED `GND` to ESP32 `GND` [cite: 49]

![Circuit Visualization](https://i.imgur.com/8Q6P4vM.png)
*(You would replace this with a permanent image link to your circuit diagram.)*

## Included Files

- [cite_start]`213014027 lab final report.pdf`: The complete final report for the lab assignment, detailing the project from requirements analysis to implementation and future work[cite: 15, 181].
- [cite_start]`diagram.json`: The JSON file for the Wokwi.com simulation, outlining the components and their connections[cite: 35].
- [cite_start]`sketch.ino`: The Arduino code for the ESP32, which includes logic for the sensor, LEDs, and ThingSpeak cloud integration[cite: 74].
- [cite_start]`213014027 feeds.csv`: A sample CSV file containing logged data from the ThingSpeak channel[cite: 180].

## Future Works

[cite_start]This project can be expanded to manage multiple parking spaces[cite: 182]. For such an implementation, the following would be needed:
- [cite_start]Multiple sonar sensors and multiple LED lights, each named according to its position[cite: 182].
- [cite_start]The cloud platform would require multiple fields and statuses to display the data for each parking space[cite: 183].
- [cite_start]The system would be able to generate a single Excel file containing the log data from all parking spaces[cite: 184].
- [cite_start]Live feeds from all parking spaces would be viewable on the Thingspeak channel dashboard or mobile application[cite: 185].
