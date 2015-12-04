#define LED_PIN RED_LED

#include "Wire.h"
#include "I2Cdev.h"

byte START_BYTE = 170;
byte SYREN_ADDR = 128;
byte CMD_FORWARD1 = 0;
byte CMD_BACKWARD1 = 1;
byte CMD_FORWARD2 = 4;
byte CMD_BACKWARD2 = 5;
byte _cmd1 = CMD_FORWARD1;
byte _cmd2 = CMD_FORWARD2;
byte _data = 0;
byte _checksum = 0;
int data;
byte encoder_set = 4;
float RSerr;
float LSerr;
byte RSset=0;
byte LSset=0;
int pRS=0; // the p control value for Right Shark
int pLS=0; // the p control value for Left Shark
int iRS=0; // the i control value for Left Shark
int iLS=0; // the i control value for Left Shark
float pk=1.3;
float ik=1;
long int loop_start=0;
long int loop_endt=0;
long last_loop = 0;
int loop_time = 20;

volatile unsigned long time;
int8_t encoder[2] = {0, 0};
// Define variables for interfacing with the x86
byte _ledState = 0;
char _buff[10];
int _indx = 0;

void setup() {
  Wire.begin(42);
  Serial.begin(9600);
 // establishContact();
  
  Serial1.begin(9600);
  delay(3000); // allow motor controller to boot
  
//  Serial.println('Serial Starting'); // set the baud rate
  Serial1.write(START_BYTE); // set the baud rate
  
  pinMode(LED_PIN, OUTPUT);  // enable LED
  last_loop = millis();
}

void loop() {
if (millis()-last_loop > loop_time)
{
  last_loop = millis();
  
//    if (Serial.available() > 0) { 
//    data = Serial.parseInt();
//    encoder_set=(byte) data;
//    }
_checksum = 0x7F & (SYREN_ADDR + _cmd1 + RSset); //Right Shark
Serial1.write(SYREN_ADDR); // send address byte
Serial1.write(_cmd1);
Serial1.write(RSset);
Serial1.write(_checksum);
  
_checksum = 0x7F & (SYREN_ADDR + _cmd2 + LSset); // Left Shark
Serial1.write(SYREN_ADDR); // send address byte
Serial1.write(_cmd2);
Serial1.write(LSset);
Serial1.write(_checksum);

    
//time = millis();
//Serial.print(time);
//Serial.print(",");
//Serial.print(_data);
//Serial.print(",");
//Serial.print(encoder[0]); // Right Shark
//Serial.print(",");
//Serial.println(encoder[1]); // Left Shark
     
//delay(1);
  
  Wire.requestFrom(43, 2);    // request 2 bytes from slave device #43
  if(Wire.available())    
   { 
    encoder[0] = (int8_t) Wire.read();
    encoder[1] = (int8_t) Wire.read();    
   }
RSerr=encoder_set-encoder[0];
LSerr=encoder_set-encoder[1];

pRS = RSerr*pk;
pLS = LSerr*pk;

iRS = min(iRS + RSerr*ik,50); //saturate the I signal at 50
iLS = min(iLS + LSerr*ik,50); //saturate the I signal at 50

RSset= max(min(pRS + iRS,255),0); // saturate control signal to avoid rollover
LSset= max(min(pLS + iLS,255),0); // saturate control signal to avoid rollover

RSset=(byte) RSset;
LSset=(byte) LSset;

if (RSset > 30) {RSset=30;}
if (LSset > 30) {LSset=30;}
//Serial.print("Speed Set: "); Serial.println(encoder_set);
//Serial.print("Right Shark Speed Set: "); Serial.print(RSset); Serial.print(" Speed: "); Serial.print(encoder[0]); Serial.print(" Err: "); Serial.println(RSerr);
//Serial.print("Left Shark Speed Set: "); Serial.print(LSset); Serial.print(" Speed: "); Serial.print(encoder[1]); Serial.print(" Err: "); Serial.println(LSerr);
//Serial.println("----");

}

}
void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

