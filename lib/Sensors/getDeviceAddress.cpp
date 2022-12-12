/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Arduino compatible algorithm for accessing DS18B20
1-wire protocol supported temperature sensor

[vishnus_technologies (C) 2022]
--------------------------------------------
*/

#include <Arduino.h>
#include <DallasTemperature.h>

#define ONEWIRE_PORT 2
int deviceCount;
DeviceAddress AddrBuffer;

OneWire oneWire(ONEWIRE_PORT);	
DallasTemperature sensors(&oneWire);

void printAddress(DeviceAddress);

void getDeviceAddr() {
  // Locate all the devices on bus
  Serial.println("Locating devices...");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");

  Serial.println("Printing addresses...");
  for (int d_ID = 0;  d_ID < deviceCount;  d_ID++) {
    Serial.print("Sensor ");
    Serial.print(d_ID+1);
    Serial.print(" : ");
    sensors.getAddress(AddrBuffer, d_ID);
    printAddress(AddrBuffer);
 }
}

void printAddress(DeviceAddress deviceAddress) { 
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print("0x");
      if (deviceAddress[i] < 0x10) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
      if (i < 7) Serial.print(", ");
    }
    Serial.println("");
  }

  void setup(){
    getDeviceAddr();
  }