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
                                
// device mapping:
#define peltier1 PE1
#define peltier2 PE2
#define flood_coolant_fan FCF
#define CS_PUMP1 CSWP
#define HS_PUMP2 HSWP

// relay states:
#define TRIGG_RELAY LOW
#define RELEASE_RELAY HIGH
#define SWITCH_ON 1
#define SWITCH_OFF 0 

// temperature states:
#define lowtemp 14
#define mediantemp 22
#define hightemp 30

// RELAY (RCS) CONTROL METHOD:
void RelayController(uint8_t _relaydef, bool _state, String _deviceID) {
  // @_state ON/1
  if(_state == HIGH) {
    if(digitalRead(_relaydef)!=_state) {
      digitalWrite(_relaydef, TRIGG_RELAY);
      Serial.println(_deviceID);
      Serial.println(" switched ON");
    }
    else if(digitalRead(_relaydef) == _state) {
      Serial.println(_deviceID);
      Serial.println(" is already ON");
    }
  }
  // @_state OFF/0
  else if(_state == LOW) {
    if(digitalRead(_relaydef) != _state) {
      digitalWrite(_relaydef, RELEASE_RELAY);
      Serial.println(_deviceID);
      Serial.println(" switched OFF");
    }
    else if(digitalRead(_relaydef) == _state) {
      Serial.println(_deviceID);
      Serial.println(" is already OFF");
    }
  }
}

// [RCS-1] Thermoelectric devices control:
void ThermoElec_RelayControl(int _temp1) {
  if(_temp1<lowtemp) {
    RelayController(peltier1, SWITCH_ON, "peltier1");
  }
  else if(_temp1>mediantemp) { 
    RelayController(peltier1, SWITCH_ON, "peltier1");
  }
  else if(_temp1>hightemp) {
    RelayController(peltier1, SWITCH_ON, "peltier1");
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