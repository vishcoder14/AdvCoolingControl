/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

DS18B20 sensor address definition block
---------------------------------------

[NB: DEFINE DS18B20 DEVICE ADDRESS ONLY]

[vishnus_technologies (C) 2022]
---------------------------------------------
*/

#include <Arduino.h>


// *** ONLY ALTER ADDRESS, DON'T DEFINE FUNCTION OR CODE HERE ***
// define your DS18B20's sddress here (add more, if needed!):             (sensor at:)
uint8_t x_addr[8] = {     /* ADDRESS OF X AXIS MOTOR SENSOR */     };  // @X_AXIS_MOTOR
uint8_t y_addr[8] = {     /* ADDRESS OF Y AXIS MOTOR SENSOR */     };  // @Y_AXIS_MOTOR
uint8_t z_addr[8] = {     /* ADDRESS OF Z AXIS MOTOR SENSOR */     };  // @Z_AXIS_MOTOR
uint8_t e_addr[8] = {     /* ADDRESS OF EXTRUDER MOTOR SENSOR */   };  // @EXTRUDER_MOTOR


// ************************ADDRESS DEFINITION BLOCK ENDS HERE************************
