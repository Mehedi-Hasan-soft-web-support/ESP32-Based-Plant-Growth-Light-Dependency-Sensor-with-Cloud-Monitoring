# 🌱 ESP32-Based Plant Growth Light Dependency Sensor

This project is a smart environmental monitoring system using the **ESP32 microcontroller**. It measures **temperature**, **humidity**, and **light intensity**, helping to understand how these parameters affect **plant growth**, especially light dependency. The data is displayed on an **I2C LCD screen** and sent to **ThingSpeak** for cloud storage and visualization. The system also provides real-time alerts using an **LED** and **buzzer** after successful data uploads.

---

## 🌿 Project Objective

To help researchers and hobbyists **monitor environmental conditions** for plants and study **light intensity's effect on plant growth**, by collecting consistent sensor data and storing it in the cloud.

---

## 🧰 Components Used

| Component               | Quantity |
|------------------------|----------|
| ESP32 Dev Board         | 1        |
| DHT22 Sensor (Temp/Hum) | 1        |
| BH1750 Light Sensor     | 1        |
| I2C 16x2 LCD Display    | 1        |
| LED (Indicator)         | 1        |
| Buzzer (Alert)          | 1        |
| Resistor (220Ω for LED) | 1        |
| Breadboard + Jumper Wires | As needed |

---

## 📐 Pin Connections

| Component      | ESP32 Pin |
|----------------|-----------|
| DHT22          | GPIO 4    |
| BH1750         | SDA - 21  |
|                | SCL - 22  |
| LCD (I2C)      | SDA - 21  |
|                | SCL - 22  |
| Buzzer         | GPIO 5    |
| LED            | GPIO 2    |

> Ensure all components share a common **GND** with ESP32.

---

## ⚙️ Functional Features

- Measures temperature, humidity, and light intensity
- Displays data on LCD in real-time
- Sends data to ThingSpeak every 15 seconds
- LED and buzzer activate on successful data transmission
- Useful for plant growth research in controlled environments

---

## 📦 Required Libraries

Install these from **Arduino Library Manager**:

- [WiFi.h](https://github.com/espressif/arduino-esp32) (ESP32 core)
- [ThingSpeak](https://github.com/mathworks/thingspeak-arduino)
- [DHT sensor library by Adafruit](https://github.com/adafruit/DHT-sensor-library)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [BH1750](https://github.com/claws/BH1750)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

---

## 🚀 Setup Instructions

1. Open the `.ino` sketch in Arduino IDE.
2. Select your ESP32 board under **Tools > Board**.
3. Install all required libraries (see above).
4. Replace your WiFi and ThingSpeak credentials:
   ```cpp
   const char* ssid = "YourWiFi";
   const char* password = "YourPassword";
   const char* writeAPIKey = "YourWriteAPIKey";
   unsigned long channelID = YourChannelID;
