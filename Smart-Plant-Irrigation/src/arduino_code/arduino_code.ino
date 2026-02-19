/**
 * Smart Plant Irrigation System with ESP32 & Blynk IoT
 * 
 * This project monitors soil moisture using a capacitive sensor and automatically 
 * controls a water pump via a relay module. It connects to the Blynk IoT platform 
 * for real-time monitoring and status feedback.
 * 
 * Hardware:
 * - ESP32 Development Board
 * - Capacitive Soil Moisture Sensor v1.2
 * - 1-Channel Relay Module (High Level Trigger)
 * - 5V DC Water Pump
 * 
 * Logic:
 * - Hysteresis Loop: Pump ON < 30% | Pump OFF > 70%
 * - Non-blocking timer using BlynkTimer
 */

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// --- CONFIGURATION ---
// Fill in your specific Blynk Template ID and Name here
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"

char auth[] = "YOUR_BLYNK_AUTH_TOKEN"; // Enter your Blynk Auth Token
char ssid[] = "YOUR_WIFI_SSID";        // Enter your WiFi Name
char pass[] = "YOUR_WIFI_PASSWORD";    // Enter your WiFi Password

// --- PIN DEFINITIONS ---
const int sensorPin = 34; // Analog input for Soil Sensor
const int pumpPin = 26;   // Digital output for Relay

// --- CALIBRATION ---
// Update these values based on your sensor calibration
const int dryValue = 2600; // Value in air
const int wetValue = 1300; // Value in water

// --- HYSTERESIS SETTINGS ---
const int startPumpLevel = 30; // Pump ON threshold (%)
const int stopPumpLevel = 70;  // Pump OFF threshold (%)

bool pumpState = false;
BlynkTimer timer;

void checkSoilMoisture() {
  int sensorValue = analogRead(sensorPin);
  int moisturePercentage = map(sensorValue, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);

  Serial.printf("Raw: %d | Moisture: %d%%\n", sensorValue, moisturePercentage);

  // Hysteresis Logic
  if (moisturePercentage < startPumpLevel) {
    pumpState = true;
  } else if (moisturePercentage > stopPumpLevel) {
    pumpState = false;
  }

  digitalWrite(pumpPin, pumpState ? HIGH : LOW);

  // Send data to Blynk
  Blynk.virtualWrite(V0, moisturePercentage); // V0: Moisture Gauge
  Blynk.virtualWrite(V1, pumpState ? 255 : 0); // V1: Pump LED Status
}

void setup() {
  Serial.begin(115200);
  
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  Blynk.begin(auth, ssid, pass);
  
  // Check sensor every 2 seconds
  timer.setInterval(2000L, checkSoilMoisture);
}

void loop() {
  Blynk.run();
  timer.run();
}
