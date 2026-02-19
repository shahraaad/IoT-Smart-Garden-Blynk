# Smart Soil Moisture Monitor & Auto-Irrigation System (ESP32 + Blynk)

An IoT-based plant watering system that monitors soil moisture levels in real-time and automatically controls a water pump. The system uses an ESP32 microcontroller and connects to the Blynk IoT app for remote monitoring.

## 🌟 Features
*   **Real-time Monitoring:** View soil moisture percentage on your smartphone via Blynk.
*   **Automatic Control:** Automatically turns the pump ON when soil is dry and OFF when wet.
*   **Hysteresis Logic:** Prevents the pump from rapidly toggling on/off (ON < 30%, OFF > 70%).
*   **Status Feedback:** LED indicator on the app shows if the pump is currently running.
*   **Non-Blocking Code:** Uses timers instead of `delay()` for stable connectivity.

## 🛠 Hardware Required
1.  **ESP32 Development Board** (Doit DevKit V1 or similar)
2.  **Capacitive Soil Moisture Sensor v1.2** (More corrosion-resistant than resistive sensors)
3.  **Relay Module** (Supports High-Level Trigger)
4.  **Mini Submersible Water Pump** (3V - 5V)
5.  **External Power Supply** (Recommended for the pump)
6.  **Jumper Wires & Breadboard**

## 🔌 Circuit Wiring

### 1. Soil Moisture Sensor
| Sensor Pin | ESP32 Pin |
| :--- | :--- |
| VCC | 3.3V |
| GND | GND |
| AOUT | GPIO 34 |

### 2. Relay Module
| Relay Pin | Connection |
| :--- | :--- |
| VCC | VIN (5V) |
| GND | GND |
| IN | GPIO 26 |

### 3. Pump Power Wiring
*   **Adapter (+)** → Relay **(+)** Terminal
*   **Adapter (-)** → Relay **(-)** Terminal AND Pump **(-)** Wire
*   **Relay (Load)** → Pump **(+)** Wire

## 📱 Blynk App Setup
1.  Create a new Template in Blynk IoT.
2.  Add two Datastreams:
    *   **V0 (Virtual Pin):** Integer, Min: 0, Max: 100 (For Moisture Gauge)
    *   **V1 (Virtual Pin):** Integer, Min: 0, Max: 1 (For Pump LED)
3.  Create a Mobile Dashboard:
    *   Add a **Gauge** widget linked to **V0**.
    *   Add an **LED** widget linked to **V1**.

## 🚀 How to Run
1.  Install the [Blynk Library](https://github.com/blynkkk/blynk-library) in Arduino IDE.
2.  Open `src/SmartIrrigation.ino`.
3.  Update the following lines with your credentials:
```cpp
#define BLYNK_TEMPLATE_ID "YOUR_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_NAME"
char auth[] = "YOUR_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASS";

