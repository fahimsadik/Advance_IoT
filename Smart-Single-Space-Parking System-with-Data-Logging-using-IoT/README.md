# Smart Single-Space Parking System with IoT

## Introduction

This project demonstrates a smart parking system designed for a single parking space. The system uses a Sonar sensor (HC-SR04) to detect the presence of a car. When a car parks in the space, the system changes the status from "Available" to "Occupied". This status is then indicated by LED lights and uploaded to a cloud platform for remote monitoring and data logging.

## How It Works

The core of the system is an ESP32 microcontroller and an HC-SR04 Sonar sensor. The Sonar sensor measures the distance to any object in the parking space.
- If the measured distance is less than 200 cm, the system considers the space "Occupied". A red LED is turned on to visually indicate this status.
- If the measured distance is greater than or equal to 200 cm, the system considers the space "Available". A green LED is turned on to visually indicate this status.

The ESP32 is connected to the internet via Wi-Fi. It sends the distance and parking status to a ThingSpeak channel. ThingSpeak is used for cloud integration and keeps a log of the parking space status and the logs are sent to Google Sheets.

## Component List

The following components were used in this project:
- ESP32 Microcontroller
- Sonar Sensor (HC-SR04)
- Green LED
- Red LED
- Resistors (330 Ohms)
- Wires

## Wire Diagram

The circuit connections are as follows:

- **HC-SR04 Sonar Sensor to ESP32**:
    - `Trigpin` to ESP32 pin 12
    - `Echopin` to ESP32 pin 13
    - `GND` to ESP32 `GND`
    - `5V` to ESP32 `VCC/5V`
- **LEDs to ESP32**:
    - Red LED positive to ESP32 pin 2
    - Green LED positive to ESP32 pin 0
    - All LED `GND` to ESP32 `GND`

For a visual representation of the circuit, please refer to the `project-visual.mkv` video file in this repository.

## Explanation of the Code (`sketch.ino`)

The provided code is an Arduino sketch for the ESP32 microcontroller.
* **Header Files**: The code starts by including the `<WiFi.h>` and `"ThingSpeak.h"` libraries to enable Wi-Fi connectivity and communication with the ThingSpeak cloud platform.
* **Constants and Variables**: It defines constants for the Wi-Fi network credentials (`ssid`, `pass`), ThingSpeak channel information (`myChannelNumber`, `myWriteAPIKey`), and the pins for the Sonar sensor and LEDs. It also declares variables to store the duration, distance, and parking status.
* **`setup()` function**: This function runs once at the beginning. It initializes the pins for the Sonar sensor and LEDs as either `OUTPUT` or `INPUT`. It also initializes serial communication, sets the Wi-Fi mode, and starts the ThingSpeak library.
* **`loop()` function**: This function runs continuously. It performs the following steps:
    1.  **Distance Measurement**: It sends a short pulse from the `TRIG_PIN` and measures the time it takes for the pulse to return to the `ECHO_PIN`. This time is then used to calculate the distance.
    2.  **Wi-Fi Connection**: It checks if the ESP32 is connected to Wi-Fi and attempts to reconnect if necessary.
    3.  **Status Logic**: It uses an `if-else` statement to determine the parking status based on the calculated distance. The corresponding LED is turned on, and the status string is updated.
    4.  **ThingSpeak Update**: It sends the distance value to Field 1 and the status string to Field 2 on the ThingSpeak channel. It then checks for a successful update (HTTP code 200) and prints the result to the serial monitor.
    5.  **Delay**: A `delay` of 20 seconds is included before the loop repeats.

## How Data is Shown in ThingSpeak
The ESP32 microcontroller, running the 

Smart-Single-Space-Parking System-with-Data-Logging-using-IoT.ino code, sends data to a ThingSpeak channel. The project is configured to use two fields in the ThingSpeak channel:


Field 1: Distance : The distance measured by the Sonar sensor is sent to this field. The report shows a numeric display widget for this field, which displays the live distance in centimeters.


Field 2: Parking Status : The parking status, a string indicating "Parking Occupied" or "Parking Available", is sent to this field. The report shows two lamp indicator widgets on the ThingSpeak dashboard for this field:

A green lamp indicator labeled "Parking Available" lights up when the distance is higher than 200 cm.

A red lamp indicator labeled "Parking Occupied" lights up when the distance is lower than 200 cm.

The code uses 

ThingSpeak.setField(1, distance) and ThingSpeak.setField(2, status) to prepare the data. The 

ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey) function then updates the channel. If the update is successful, the serial monitor prints "Channel update successful". The report includes screenshots of the ThingSpeak dashboard showing the widgets for distance and parking status.

# How ThingSpeak Produces a CSV File
The project uses ThingSpeak's data logging and export feature. The final report states that after the data is logged, a log can be exported from the export section of the ThingSpeak channel. This produces a CSV (Comma-Separated Values) file. A sample CSV file log is provided in the report, showing a table of data that includes a timestamp, distance measurement, and the parking status. The report also mentions that this log can be used to keep a record of the "parking occupied" and "parking available" events.

## Included Files

- `project-report.pdf`: The complete final report for the lab assignment, detailing the project from requirements analysis to implementation and future work.
- `diagram.json`: The JSON file for the Wokwi.com simulation, outlining the components and their connections.
- `Smart-Single-Space-Parking System-with-Data-Logging-using-IoT.ino`: The Arduino code for the ESP32, which includes logic for the sensor, LEDs, and ThingSpeak cloud integration.
- `log-feeds.csv`: A sample CSV file containing logged data from the ThingSpeak channel.
- `project-visual.mkv`: A video file showing the circuit and its connections.

## Future Works

This project can be expanded to manage multiple parking spaces. For such an implementation, the following would be needed:
- Multiple sonar sensors and multiple LED lights, each named according to its position.
- The cloud platform would require multiple fields and statuses to display the data for each parking space.
- The system would be able to generate a single Excel file containing the log data from all parking spaces.
- Live feeds from all parking spaces would be viewable on the Thingspeak channel dashboard or mobile application.
