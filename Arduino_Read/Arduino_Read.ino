/* This code matches with test_i2c to illustrate communication between 
the arduino (slave) and Launchpad (master)*/

#include <Wire.h>

int8_t data[2] = {0, 0};

void setup()
{
  Wire.begin(42);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.requestFrom(43, 2);    // request 2 bytes from slave device #43

  
 if(Wire.available()) // If there are byte, assume there will always be 2
{ 
 data[0] = (int8_t)Wire.read();
 data[0] = (int8_t)Wire.read();
 Serial.print(data[0]);Serial.println(data[1]);  // print the data
 }
delay(1000);
}
