/*
[Part of ADVANCED COOLING CONTROL ALGORITHM]

PCF8574 I/O expander external arduino compatible library
--------------------------------------------------------

(I2C Protocol based) For scanning address of the available 
connected PCF8574 I2C modules and to initiate its pins in
arduino environment.

[vishnus_technologies (C) 2022]
----------------------------------------------------------
*/


#include <PCF8574.h>
#include <Wire.h>

// set yours PCF8574's default address:
#define PCF8574_defaultAddr 0x20

#define PE1 P1
#define PE2 P2
#define FCF P3
#define CSWP P4  
#define HSWP P5
int nDevices;

/* [PCF8574 8-BIT ADDRESS TABLE]
1. 000 = 0x20
2. 001 = 0x21
3. 010 = 0x22
4. 011 = 0x23
5. 100 = 0x24
6. 101 = 0x25
7. 110 = 0x26
8. 111 = 0x27  */


// I2C address scanner for PCF8574 module: 
void run_PCF8574_addrScanner() {
  byte error, address;

  Serial.println(F("Scanning..."));
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
     
    if (error == 0) {
      Serial.print(F("I2C device found at: 0x"));
      if (address<16) { Serial.print("0"); }
      Serial.print(address,HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print(F("Unknown error at address 0x"));
      if (address<16) { Serial.print("0"); }
      Serial.println(address,HEX);
    }    
  }

  if (nDevices == 0) { Serial.println(F("No I2C devices found\n")); }
  else { Serial.println(F("done\n")); }
}


// pin initiator for PCF8574:
void initPins_PCF8574() {
  if(nDevices>=1) {
    PCF8574 pcf8574(PCF8574_defaultAddr);
    delay(1450);
    if (pcf8574.begin()) {
      Serial.println("\n[PCF8574 module initiated]"); 
      // PCF8574 pin mode definition:
      //for(int pin=2;pin<=6;pin++){ pcf8574.pinMode('P'+pin, OUTPUT); }
      pcf8574.pinMode(PE1, OUTPUT);
      pcf8574.pinMode(PE2, OUTPUT);
      pcf8574.pinMode(CSWP, OUTPUT);
      pcf8574.pinMode(HSWP, OUTPUT);
      pcf8574.pinMode(FCF, OUTPUT);
      Serial.println("[PCF8574 I/O pins initiated]"); 
    }
    else { Serial.println("[Error initializing PCF8574, I/O pins]"); }
  }
}
