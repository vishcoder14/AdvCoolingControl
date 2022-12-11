/* 
[Part of ADVANCED COOLING CONTROL ALGORITHM]

Control algorithm for temperature based Relay Control Systems
-------------------------------------------------------------

Controls device control relay modules. These systems are used for controlling (ON/OFF)
thermoelectric devices, coolants, exhausts etc... based only on thermal sensor values.
Mainly it control two independent RCS(s), named RCS-1, RCS-2.
-> RCS-1 controls all coolant fans, radiator, exhausts, based on the tempsensor-1 @A0, 
-> RCS-2 controls all thermoelectric devices systems, based on tempsensor-2 @A1

[vishnus_technologies (C) 2022]
--------------------------------------------------------------------------------------
*/

#include <Arduino.h>

#define peltier1 PE1
#define peltier2 PE2
#define flood_coolant_fan FCF
#define CS_PUMP1 CSWP
#define HS_PUMP2 HSWP
#define TRIGG_RELAY LOW
#define RELEASE_RELAY HIGH


// [RCS-1] Thermoelectric devices control:
void ThermoElec_RelayControl(int _temp1) {
  if(_temp1<14) {
    if(digitalRead(peltier1)==1) {
      digitalWrite(peltier1, RELEASE_RELAY);
      Serial.println("[CT below 14C, P1 has switched OFF]");
      if(digitalRead(peltier2)==1) {
        digitalWrite(peltier2, RELEASE_RELAY); 
        Serial.println("[CT below 14C, P2 has switched OFF]"); 
      }
    }
  }
  else if(_temp1>22) {
    if(digitalRead(peltier1)==0) {
      digitalWrite(peltier1, TRIGG_RELAY);
      Serial.println("[CT above 28C, P1 has switched ON]"); 
    }
    if(digitalRead(peltier2)==1) {
      digitalWrite(peltier2, RELEASE_RELAY);
    }
  }
  else if(_temp1>32) {
    if(digitalRead(peltier1)==0) {
      digitalWrite(peltier1, TRIGG_RELAY);
      Serial.println("[CT above 32C, P1 has switched ON]"); }
    else { 
      Serial.println("[CT above 32C, P1 has already switched ON]"); }
    
    if(digitalRead(peltier2)==0) {  
      digitalWrite(peltier2, TRIGG_RELAY);
      Serial.println("[CT above 32C, P2 has switched ON]"); }
    else { 
      Serial.println("[CT above 32C, P2 has already switched ON]"); }
  }
}


// [RCS-2] Coolant fans control:
void CFan_RelayControl(int _temp0) {
  if(_temp0<20) {
    if(digitalRead(flood_coolant_fan)==1) {
      digitalWrite(flood_coolant_fan, RELEASE_RELAY);
      Serial.println(F("[Radiator fan, switched OFF]"));
    } 
  }
  else if(_temp0>45) {
    if(digitalRead(flood_coolant_fan)==0) {
      digitalWrite(flood_coolant_fan, TRIGG_RELAY);
      Serial.println(F("[Radiator fan, switched ON]"));
    } 
  }
}