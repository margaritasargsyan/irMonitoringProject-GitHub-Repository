#include <SoftwareSerial.h>

// Define pins
#define RX_PIN 3  // ESP8266 RX pin
#define TX_PIN 2  // ESP8266 TX pin
#define RELAY_PIN 4  // Relay pin to control air purifier

// Create a software serial connection for the SDS011 sensor
SoftwareSerial sensorSerial(RX_PIN, TX_PIN);

// Threshold for air purifier activation (PM2.5 level)
#define PM_THRESHOLD 50

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  sensorSerial.begin(9600);
  
  // Set relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Start with the air purifier off
  
  Serial.println("Air Quality Monitoring System Started...");
}

void loop() {
  // Variables for storing sensor data
  int pm25 = 0;
  int pm10 = 0;
  
  // Read data from SDS011 sensor
  if (sensorSerial.available()) {
    byte data[10];
    if (sensorSerial.readBytes(data, 10) == 10) {
      // Extract PM2.5 and PM10 values from the data packet
      pm25 = data[2] * 256 + data[3];
      pm10 = data[4] * 256 + data[5];
      
      // Print sensor values to the serial monitor
      Serial.print("PM2.5: ");
      Serial.print(pm25);
      Serial.print(" µg/m³  PM10: ");
      Serial.println(pm10);
      
      // Check if PM2.5 exceeds the threshold and activate the air purifier
      if (pm25 > PM_THRESHOLD) {
        digitalWrite(RELAY_PIN, HIGH);  // Turn on air purifier
        Serial.println("Air purifier ON");
      } else {
        digitalWrite(RELAY_PIN, LOW);  // Turn off air purifier
        Serial.println("Air purifier OFF");
      }
    }
  }
  
  delay(1000);  // Wait for 1 second before reading the sensor again
}