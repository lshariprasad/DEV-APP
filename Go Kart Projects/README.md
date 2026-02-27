# 🚀 Build Your Own F2 Car with AI Based Multi Sensor Monitoring System using Arduino Mega 2560 and ESP32

## 📌 Project Overview

This project is a **Real-Time Multi-Sensor Environmental & Safety Monitoring System** built using **Arduino Mega 2560**.

Thank You for Cirkit Design IBM Website Link : https://app.cirkitdesigner.com/

This is Finaly Version Circuit Diagram Link : https://app.cirkitdesigner.com/project/c6b07012-2e5c-4ac3-8564-523325f02eda

It integrates multiple sensors to monitor:

- 🌡 Non-contact Temperature (MLX90614)
- 📍 GPS Location (NEO-6M)
- 💨 Gas Concentration (MQ Series)
- 🔥 Flame Detection
- 💧 Humidity & Temperature (DHT11)
- 📊 Acceleration (ADXL335)
- 🧲 Magnetic Field Detection (Hall Effect Sensor)

The system continuously reads real-time data from all sensors and displays the output in the Serial Monitor.

---

# 🧠 Features

- ✅ Real-time multi-sensor monitoring
- ✅ I2C + Analog + Digital communication
- ✅ Modular sensor testing architecture
- ✅ Expandable for IoT / Cloud integration
- ✅ Industrial & safety monitoring ready
- ✅ Clean power distribution using breadboard rails

---

# 🛠 Hardware Components

| Component | Model |
|------------|--------|
| Microcontroller | Arduino Mega 2560 |
| IR Temperature Sensor | GY-906 (MLX90614) |
| GPS Module | GY-GPS6MV2 (NEO-6M) |
| Gas Sensor | MQ Series |
| Flame Sensor | IR Flame Sensor |
| Humidity Sensor | DHT11 |
| Accelerometer | GY-61 (ADXL335) |
| Hall Effect Sensor | A3144 / 49E |
| Breadboard | Standard |
| Jumper Wires | Male-Male |
| Power Supply | 5V & 3.3V from Mega |

---

# 🖼️ Picture (Circuit Diagram) 📸

## 1) Main Version Of Circuit Diagram :
<img width="1600" height="1130" alt="image" src="https://github.com/user-attachments/assets/c719eafb-b99b-4905-8766-4cee41b33e4d" />

## 2) Final Version Of Circuit Diagram :
<img width="1600" height="1109" alt="image" src="https://github.com/user-attachments/assets/9350bfd0-1a0c-4aa6-93df-2e12003f75cd" />

## 3) Display Of Circuit Diagram :
<img width="1600" height="849" alt="image" src="https://github.com/user-attachments/assets/48dca9a0-0eeb-435f-a8cc-daabdd36d932" />

## 4) Display UI/UX Interface :
<img width="1600" height="998" alt="image" src="https://github.com/user-attachments/assets/f07aeb0b-3d86-42e1-a1cc-f147e5e6a7a7" />


## 4) Video Link :

#### 1 ) Display : 




---

# 🔌 Power Distribution (Arduino Mega → Breadboard)

| Arduino Mega Pin | Breadboard Rail |
|------------------|-----------------|
| 5V | 5V Rail (Red) |
| 3.3V | 3.3V Rail |
| GND | GND Rail (Blue) |

⚠️ All sensors share a common GND.

---

# 🔗 Sensor Pin Connections (Arduino Mega 2560)

## 🔵 MLX90614 (GY-906) - I2C

| Sensor Pin | Mega Pin |
|------------|----------|
| VCC | 5V (or 3.3V if required) |
| GND | GND |
| SDA | 20 |
| SCL | 21 |

---

## 🔵 GPS Module (NEO-6M)

| GPS Pin | Mega Pin |
|----------|----------|
| VCC | 5V |
| GND | GND |
| TX | 19 (RX1) |
| RX | 18 (TX1) |

---

## 🔵 MQ Gas Sensor

| MQ Pin | Mega Pin |
|--------|----------|
| VCC | 5V |
| GND | GND |
| A0 | A0 |

---

## 🔵 Flame Sensor

| Flame Pin | Mega Pin |
|------------|----------|
| VCC | 5V |
| GND | GND |
| A0 | A1 |

---

## 🔵 DHT11 Sensor

| DHT Pin | Mega Pin |
|----------|----------|
| VCC | 5V |
| GND | GND |
| DATA | 7 |

---

## 🔵 ADXL335 (GY-61 Accelerometer)

⚠️ Use 3.3V only.

| GY-61 Pin | Mega Pin |
|------------|----------|
| VCC | 3.3V |
| GND | GND |
| X | A2 |
| Y | A3 |
| Z | A4 |

---

## 🔵 Hall Effect Sensor

### Digital Type (A3144)

| Hall Pin | Mega Pin |
|-----------|----------|
| VCC | 5V |
| GND | GND |
| DO | 2 |

### OR

### Analog Type (49E)

| Hall Pin | Mega Pin |
|-----------|----------|
| VCC | 5V |
| GND | GND |
| AO | A5 |

---

# 🧩 Software Requirements

- Arduino IDE
- Cirkit Designer (for circuit diagram)
- Required Libraries:
  - Wire.h
  - Adafruit_MLX90614
  - TinyGPS++
  - DHT

---

# 📂 Project Structure
Multi-Sensor-System/
│
├── main.ino
├── README.md
├── circuit_diagram.png
└── libraries_used.txt


---

# 🧪 How to Run

1. Connect all sensors as per wiring table.
2. Distribute power properly (5V, 3.3V, GND).
3. Upload the Arduino code.
4. Open Serial Monitor (9600 baud rate).
5. Monitor real-time sensor values.

---

# 📊 Example Serial Output
Ambient Temp: 29.3 °C | Object Temp: 31.8 °C
Humidity: 65%
Gas Level: 350
Flame: Not Detected
GPS: 13.0827, 80.2707
Acceleration X: 520 Y: 498 Z: 612
Hall Sensor: Magnet Detected


---

# 🔥 Applications

- Industrial Safety Monitoring
- Fire & Gas Alert System
- Smart Environment Monitoring
- Vehicle Tracking & Accident Detection
- IoT Smart Embedded Systems
- Academic & Research Projects

---

# 🚀 Future Improvements

- GSM/WiFi Cloud Integration
- IoT Dashboard
- OLED/LCD Display
- Buzzer Alert System
- SD Card Data Logging
- AI-Based Anomaly Detection

---

# 👨‍💻 Author

Hari Prasad L S  
Build Your Own F2 Car 😊
---

# 📜 License

This project is open-source and free for educational and research purposes.
