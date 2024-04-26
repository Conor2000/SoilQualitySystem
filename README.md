# IoT Soil Quality Monitoring System

## Overview
This project aims to create a low-cost IoT soil monitoring system to help farmers optimise soil conditions for improved grassland farming productivity. Utilising Arduino Uno and Raspberry Pi, the system measures key soil parameters like moisture, pH, and nutrient levels (NPK), transmitting data to a Firebase database for real-time monitoring.

## Hardware Requirements
- Arduino Uno
- Raspberry Pi 3 Model B
- pH sensor (PH-4502C)
- Soil moisture sensor (FC28)
- NPK sensor

## Software Requirements
- Raspberry Pi with OS installed
- Thonny
- Arduino IDE for programming Arduino Uno
- Firebase account for data storage and management

## Installation

### Setting Up Arduino
1. Connect the sensors to Arduino Uno.
2. Use Arduino IDE to upload the sensor reading code to Arduino Uno.
   - Code is available in the `arduino_code` folder.

### Setting Up Raspberry Pi
1. Ensure Raspberry Pi is running Raspberry Pi OS.
2. Connect Raspberry Pi to your network.
3. Download `Main_Program.py` onto the Raspberry Pi.


## Usage
To start the system, manually run the main program script on Raspberry Pi. This script reads data from Arduino over a serial connection and uploads it to Firebase.

