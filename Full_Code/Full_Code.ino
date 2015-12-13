#include <Wire.h>

#include <I2Cdev.h>

// These lines are only when running an Arduino Master
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(10, 11); // RX, TX

const int dt = 100; // timescale of the entire control loop
long tlast, tcur; // used to help time the main loop.

const bool FLIPPED = true;

// MPU Variables
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
// theta is in degrees, omega is in degrees/second
float theta, omega, theta_a, theta_g;

void setup()
{ 
  Wire.begin();
  Serial.begin(9600);
  delay(50);
  Serial.println("Serial Initialized");
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  prepSabretooth();
  //prepMPUs();
  tlast = millis();
}

void loop()
{  // put your main code here, to run repeatedly:
  tcur = millis();
  if (tcur-tlast > dt){
    tlast = tcur;
    collectMPUData();
    //Serial.print(theta_a);
    //Serial.print(",");
    //Serial.print(theta_g);
    //Serial.print(",");
    Serial.println(theta);
    driveMotor1((int8_t)theta);
    driveMotor2((int8_t)theta);
    digitalWrite(13,HIGH);
    delay(1);
    digitalWrite(13,LOW);
  }
}


