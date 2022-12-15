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

// device pin mapping:
#define PELTIER1 PE1
#define PELTIER2 PE2
#define FLOOD_COOLANT_FAN FCF
#define CS_PUMP CSWP
#define HS_PUMP HSWP

// relay states:
#define TRIGG_RELAY LOW
#define RELEASE_RELAY HIGH

// temperature constants:
#define LOW_TEMP 14
#define MEDIAN_TEMP 22
#define HIGH_TEMP 32


// RELAY SWITCH CONTROL SECTION (RSCS):
void switchRelay(uint8_t _deviceID, bool _state) {
  String _deviceName = "";

  if(_deviceID == 3) _deviceName = "MAIN POWER";
  else if(_deviceID == PE1) _deviceName = "Peltier1";
  else if(_deviceID == PE2) _deviceName = "Peltier2";
  else if(_deviceID == FCF) _deviceName = "Coolant fan";
  else if(_deviceID == CSWP) _deviceName = "CS PUMP";
  else if(_deviceID == HSWP) _deviceName = "HS PUMP";
  else _deviceName = "Undefined device";

  // @_state: ON/1
  if(_state == TRIGG_RELAY) {
    if(digitalRead(_deviceID)!=_state) {
      digitalWrite(_deviceID, TRIGG_RELAY);
      Serial.print(_deviceName);
      Serial.println(F(" switched ON"));
    }
    else if(digitalRead(_deviceID) == _state) {
      Serial.print(_deviceName);
      Serial.println(F(" is already ON"));
    }
  }
  // @_state: OFF/0
  else if(_state == RELEASE_RELAY) {
    if(digitalRead(_deviceID) != _state) {
      digitalWrite(_deviceID, RELEASE_RELAY);
      Serial.print(_deviceName);
      Serial.println(" switched OFF");
    }
    else if(digitalRead(_deviceID) == _state) {
      Serial.print(_deviceName);
      Serial.println(" is already OFF");
    }
  }
}

// [RCS-1] Thermoelectric devices control:
// (for NTC-S1 @peltier cool side)
void NTC_CS(int _temp1) {
  if(_temp1<LOW_TEMP) {
    switchRelay(PELTIER1, RELEASE_RELAY);
    switchRelay(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp1>MEDIAN_TEMP) { 
    switchRelay(PELTIER1, TRIGG_RELAY);
    switchRelay(PELTIER2, RELEASE_RELAY);
  }
  else if(_temp1>HIGH_TEMP) {
    switchRelay(PELTIER1, TRIGG_RELAY);
    switchRelay(PELTIER2, TRIGG_RELAY);
  }
}

// [RCS-2] Coolant fans control:
// (for NTC-S2 @peltier hot side)
void NTC_HS(int _temp0) {
  if(_temp0<20) {
    switchRelay(FLOOD_COOLANT_FAN, RELEASE_RELAY);
  }
  else if(_temp0>45) {
    switchRelay(FLOOD_COOLANT_FAN, TRIGG_RELAY);
  }
}

