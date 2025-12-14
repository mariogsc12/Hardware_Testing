# Hardware Testing Repository

This repository contains a collection of **hardware testing and validation projects** focused on **sensors, actuators, and communication modules**, mainly using **ESP32** boards and **PlatformIO**.

The goal of this repository is to provide **isolated, reproducible tests** for individual hardware components before integrating them into larger robotic or embedded systems.

---

## 📌 Scope

This repository includes tests for:

- 🧭 Sensors (IMU, encoders, Hall sensors)
- ⚙️ Actuators (brushless motors, motor controllers)
- 📡 Communication interfaces (WiFi, LoRa, radio, RC receivers)
- 💾 Storage devices (MicroSD)
- 🔌 Controllers and peripherals

All tests are designed to:
- Validate hardware functionality
- Measure performance and reliability
- Serve as reference implementations for future projects

---

## 🧰 Technologies Used

- **Microcontroller:** ESP32
- **Framework:** PlatformIO
- **Programming Language:** C / C++
- **Interfaces:** I2C, SPI, UART, PWM, GPIO
- **Development Environment:** VS Code + PlatformIO

---

## 📂 Repository Structure

```text
Hardware_Testing/
│
├── Brushless_Identification/     # Brushless motor characterization and identification
├── Encoder/                      # Encoder testing and signal validation
├── ESP32/                        # ESP32-specific experiments and utilities
├── lora_communication/           # LoRa communication tests
├── MicroSD/                      # MicroSD read/write tests
├── MPU6050/                      # MPU6050 IMU tests
├── MPU9250/                      # MPU9250 IMU tests
├── radio_communication/          # Generic radio communication tests
├── RC_Receiver_Test/             # RC receiver signal decoding
├── Test Hall Sensor/             # Hall effect sensor testing
├── Test WT901/                   # WT901 IMU basic tests
├── Test_MPU9250/                 # Alternative MPU9250 test implementations
├── Wifi/                         # WiFi communication tests
├── WT901C/                       # WT901C IMU advanced tests
├── ZS_CONTROLLER/                # ZS motor controller tests
│
└── .gitignore
