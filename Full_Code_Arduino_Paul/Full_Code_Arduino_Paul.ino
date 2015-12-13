#include <I2Cdev2.h>

#include "Wire.h"
//#include "I2Cdev2.h"

const int dt = 100; // timescale of the entire control loop
long tlast, tcur; // used to help time the main loop.

const bool FLIPPED = true;

// MPU Variables
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
// theta is in degrees, omega is in degrees/second
float theta, omega;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(50);
  Serial.println("Serial Initialized");
  prepMPUs();
  prepSabretooth();
  tlast = millis();
}

void loop()
{  // put your main code here, to run repeatedly:
  tcur = millis();
  if (tcur-tlast > dt){
    tlast = tcur;
    collectMPUData();
    //Serial.println(theta);
    //driveMotor1((int8_t)theta);
    //driveMotor2((int8_t)theta);
  }
}


