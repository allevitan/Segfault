#include <Wire.h>

byte d1=0;
byte d2=0;
//byte ADDR=2;
bool opt=1;
void setup()
{
  Wire.begin(42);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.requestFrom(2, 2, opt);    // request 2 bytes from slave device #43

  
 if(Wire.available())    // slave may send less than requested
{ 
 d1 = Wire.read();
 d2 = Wire.read();    // receive a byte as character
 Serial.print(d1,d2);         // print the character
 }
Serial.println("loop");
delay(1000);
}
