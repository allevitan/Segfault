#define LED_PIN RED_LED

#include "Wire.h"
#include "I2Cdev.h"

byte START_BYTE = 170;
byte SYREN_ADDR = 128;
byte CMD_FORWARD1 = 0;
byte CMD_BACKWARD1 = 1;
byte CMD_FORWARD2 = 4;
byte CMD_BACKWARD2 = 5;
byte _cmd1 = CMD_BACKWARD1;
byte _cmd2 = CMD_BACKWARD2;
byte _data = 0;
byte _checksum = 0;
int data;

int8_t encoder[2] = {0, 0};
// Define variables for interfacing with the x86
byte _ledState = 0;
char _buff[10];
int _indx = 0;

void setup() {
  Wire.begin(42);
  Serial.begin(9600);
  establishContact();
  
  Serial1.begin(9600);
  delay(3000); // allow motor controller to boot
  
//  Serial.println('Serial Starting'); // set the baud rate
  Serial1.write(START_BYTE); // set the baud rate
  
  pinMode(LED_PIN, OUTPUT);  // enable LED
}

void loop() {
  
    if (Serial.available() > 0) { 
    data = Serial.parseInt();
    _data=(byte) data;
    Serial.println(_data);
    
    
_checksum = 0x7F & (SYREN_ADDR + _cmd1 + _data);
Serial1.write(SYREN_ADDR); // send address byte
 Serial1.write(_cmd1);
Serial1.write(_data);
Serial1.write(_checksum);
  
 _checksum = 0x7F & (SYREN_ADDR + _cmd2 + _data);
Serial1.write(SYREN_ADDR); // send address byte
Serial1.write(_cmd2);
 Serial1.write(_data);
Serial1.write(_checksum);
    }  
  delay(100);
  
  Wire.requestFrom(43, 2);    // request 2 bytes from slave device #43
  if(Wire.available())    
   { 
    encoder[0] = (int8_t) Wire.read();
    encoder[1] = (int8_t) Wire.read();    
   }
 
     Serial.print("Motor 1: "); Serial.println(encoder[0]);
   Serial.print("Motor 2: "); Serial.println(encoder[1]);
   Serial.println("----");
}
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

