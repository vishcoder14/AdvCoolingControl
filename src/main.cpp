/*
# main.cpp

ADVANCED COOLING CONTROL ALGORITHM (For Ender-3 PRO)
----------------------------------------------------

This is an intelligent algorithm, specially desgined for 3d printers
(Ender-3 PRO). This algorithm adds more saftey to your printer.By 
installing this software/algorithm you can leave your printer unattended.
It has several advanced saftey features. You can run your printer for
high temperature prints also. Has advanced saftey for the stepper motor
too, also for the print head. Make sures motor looses not steps. Cool :)

[vishnus_technologies (C) 2022]
[# 20-DECEMBER-2022 08:46PM]
-------------------------------------------------------------------------
*/

#include <Arduino.h>
#include <PCF8547_IOEXP.h>
#include <Sensors.h>
#include <RelayControl.h>

// mapping of peltier sensors:
#define HSTS A0
#define CSTS A1 
#define NCTS A2  
#define main_power 3

double TEMP1, TEMP2, TEMP3;
char buffer[20];

ntc10k NTC;
ds18b20 DS18B20;


void setup() {
	Serial.begin(9600);
  delay(1000);
  
  // switch ON main power:
  switchRelay(main_power, SWITCH_ON, "main power");
  
  // MCU pin mode definition:
  pinMode(main_power, OUTPUT);
  pinMode(HSTS, INPUT);
  pinMode(CSTS, INPUT);
  pinMode(NCTS, INPUT);
  Serial.println(F("[MCU I/O pin modes initiated]"));
  
  // init_PCF8574_addrScanner();
  // initPins_PCF8574(); 

  if(DS18B20.init_sensor() == EXIT_SUCCESS) {
    Serial.println(F("[initiated DS18B20]"));
   }
}


void loop() {
  TEMP1 = NTC.GetTemperature(analogRead(CSTS));  // NTC-S1 @peltier cool side [for thermoele.dev control]
  TEMP2 = NTC.GetTemperature(analogRead(HSTS));  // NTC-S2 @peltier hot side [for coolant fan control]
  sprintf(buffer, "Peltier temp: hotside: %f | coolside: %f", TEMP1,TEMP2);
  Serial.println(buffer);
  NTC_CS(TEMP1);
  NTC_HS(TEMP2);

  // NTC-sensor-3
  TEMP3 = NTC.GetTemperature(analogRead(NCTS));
  Serial.println("Normal coolant temp: "+String(TEMP3));
  Serial.println(F("Motor C-Block temp(s): "));

  // DS18B20 sensor batch-1

}