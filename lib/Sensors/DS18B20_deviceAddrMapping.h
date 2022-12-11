/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

DS18B20 sensor address definition block
---------------------------------------

[NB: DEFINE DS18B20 DEVICE ADDRESS ONLY]

[vishnus_technologies (C) 2022]
---------------------------------------------
*/

#include <Arduino.h>

// define your DS18B20's sddress here (add more, if needed!): 
uint8_t x_addr[8] = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };  // @X_AXIS_MOTOR
uint8_t y_addr[8] = { 0x28, 0x61, 0x64, 0x12, 0x3C, 0x7C, 0x2F, 0x27 };  // @Y_AXIS_MOTOR
uint8_t z_addr[8] = { 0x28, 0x61, 0x64, 0x12, 0x3F, 0xFD, 0x80, 0xC6 };  // @Z_AXIS_MOTOR
uint8_t e_addr[8] = { 0x28, 0x61, 0x64, 0x12, 0x3F, 0xFD, 0x80, 0xC6 };  // @EXTRUDER_MOTOR


// ************************ADDRESS DEFINITION ENDS HERE************************

