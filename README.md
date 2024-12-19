# AirMonitoringProject-GitHub-Repository
//An air quality monitoring system using SDS011 sensor and ESP8266. It tracks PM2.5 and PM10 levels in real-time and triggers an air purifier when thresholds are exceeded. The system offers a web dashboard for live data and automatic air purification, ideal for homes and offices.//
#include "SdsDustSensor.h"
 
int rxPin = 0;
int txPin = 1;
SdsDustSensor sds(rxPin, txPin);

 
void setup() {
  Serial.begin(9600);
  sds.begin();
 
  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  Serial.println(sds.setActiveReportingMode().toString()); // ensures sensor is in 'active' reporting mode
  Serial.println(sds.setContinuousWorkingPeriod().toString()); // ensures sensor has continuous working period - default but not recommended
}
 
void loop() {
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
 
    // if you want to just print the measured values, you can use toString() method as well
    Serial.println(pm.toString());
  } else {
    // notice that loop delay is set to 0.5s and some reads are not available
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }
 
  delay(500);
}
