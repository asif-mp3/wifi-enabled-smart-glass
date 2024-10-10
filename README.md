# 🤖 Wearable Smart Glass for Health Monitoring

A simple yet effective wearable health monitoring system that tracks real-time **heart rate** and **step count** using a **Pulse Sensor** and **accelerometer**. Data is displayed on an **OLED screen** and processed by the **NodeMCU V3** for portable health tracking.

---

## 🛠️ Components Used

- **NodeMCU V3**: Microcontroller board based on the ESP8266 WiFi module
- **Pulse Sensor**: For detecting heart rate (BPM)
- **Accelerometer**: For step counting
- **OLED Display (SH1106)**: 128x64 pixels I2C display
- **Wires & Breadboard**: For circuit assembly
- **Arduino IDE**: Software to program and upload code to NodeMCU
- **Power Source**: Battery or USB

---

## 🚀 Project Roadmap

### Phase 1: Initialization
- [x] Setup NodeMCU and connect the Pulse Sensor, accelerometer, and OLED.
- [x] Code the basic functions for heart rate detection and step counting.
- [x] Display readings on the OLED.

### Phase 2: Optimizations
- [ ] Optimize heart rate reading accuracy with threshold adjustments.
- [ ] Calibrate accelerometer to avoid false step counts.
- [ ] Improve OLED display by adding UI elements.

### Phase 3: Final Build
- [ ] Create a PCB for more compact assembly.
- [ ] Add a case for portability.

---

## 🧑‍💻 How to Set Up and Run

1. **Install Arduino IDE** from [here](https://www.arduino.cc/en/software).
2. **Install the NodeMCU ESP8266 Board**:
    - Open Arduino IDE.
    - Go to **File > Preferences** and paste this in "Additional Boards Manager URLs": 
      ```
      http://arduino.esp8266.com/stable/package_esp8266com_index.json
      ```
    - Go to **Tools > Board > Boards Manager** and search for **ESP8266**.
    - Install **ESP8266 by ESP8266 Community**.

3. **Install Required Libraries**:
    - **PulseSensor Playground**: Go to **Sketch > Include Library > Manage Libraries**, search for **PulseSensor Playground**, and install.
    - **Adafruit GFX Library**: Install the **Adafruit GFX** and **Adafruit SH110X** libraries from the library manager.
    
4. **Wiring Setup**:
    - **Pulse Sensor**: Connect to `D0`.
    - **Accelerometer**: Connect the analog pin to `A0`.
    - **OLED Display**: Connect SDA to `D1` and SCL to `D2`.

5. **Upload the Code**:
    - Open the Arduino IDE.
    - Select **NodeMCU 1.0 (ESP-12E Module)** under **Tools > Board**.
    - Connect the NodeMCU to your PC and select the correct **Port**.
    - Upload the code from the separate Arduino file.

---

## 📝 To Do List

- [ ] Calibrate accelerometer for better accuracy.
- [ ] Improve BPM detection with noise filtering.
- [ ] Add Bluetooth support for mobile app connectivity.
- [ ] Create a 3D-printed case for wearable purposes.

---

## 🎯 How it Works

1. The **Pulse Sensor** measures the user's heart rate and sends data to the **NodeMCU**.
2. The **Accelerometer** detects motion and counts steps based on movement.
3. The data is processed and displayed on the **OLED** screen.
4. The display alternates between showing the **step count** and the **current heart rate** every 3 seconds.

---

## 📦 Components Required

- **NodeMCU V3 (ESP8266)**
- **Pulse Sensor**
- **Accelerometer (ADXL345 or similar)**
- **OLED Display (SH1106 or SSD1306)**
- **Jumper Wires**
- **Breadboard**
- **USB Cable**

---

## 🤝 Contributions

Feel free to submit issues or pull requests to improve the project!

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
