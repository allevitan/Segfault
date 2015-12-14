#include <Wire.h>
#include "Energia.h"
#include "Timer.h"
#include <I2Cdev.h>

// These lines are only when running an Arduino Master
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(10, 11); // RX, TX

const bool FLIPPED = true;

// MPU Variables
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
// theta is in degrees, omega is in degrees/second
float theta, omega, theta_a, theta_g,thetam1;

// Encoder Variables
int16_t raw_encoder_data[2] = {0,0};
float encoder_RS = 0;
float encoder_LS = 0;

// Control Parameters
const float kv = 1; // in volts per radian
const float kv_converted = kv * float(127)/24; // In steps per radian
float omega_error;
float Vc=0;
float Vcm1=0;
Timer myTimer;
float dt=10; 

uint8_t status = 1;
const uint8_t myLED = BLUE_LED;

void timerFunction()
{  // put your main code here, to run repeatedly:
    collectEncoderData();
//    Serial.print(encoder_RS);
//    Serial.print(',');
//    Serial.println(encoder_LS);
    collectMPUData();
    
//    Serial.print(theta_a);
//    Serial.print(",");
//    Serial.print(theta_g);
//    Serial.print(",");
//    Serial.println(theta);
//    driveMotorRS((int8_t)theta);
//    driveMotorLS((int8_t)theta);
    Vc=(theta-thetam1+(98.5*Vcm1))/101.5;
    Vc=min(Vc,20);
    Vc=max(Vc,-20);
    VelocityControlMotorRS(Vc);
    VelocityControlMotorLS(Vc);
    thetam1=theta;
    Vcm1=Vc;
//    digitalWrite(13,HIGH);
//    delay(1);
//    digitalWrite(13,LOW);
    status = 1 - status;
    digitalWrite(myLED, status);
}


void setup()
{ 
  Wire.begin();
  Wire.setTimeout(100);
  Serial.begin(9600);
  delay(50);
  Serial.println("Serial Initialized");
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  prepSabretooth();
  prepMPUs();
  pinMode(myLED, OUTPUT);
  myTimer.begin(timerFunction, 10);
  myTimer.start();
}




void VelocityControlMotorRS(float Target_Velocity){
  omega_error = Target_Velocity - encoder_RS;
  driveMotorRS(max(-127,min(127,omega_error*kv_converted)));
}

void VelocityControlMotorLS(float Target_Velocity){
  omega_error = Target_Velocity - encoder_LS;
  driveMotorLS(max(-127,min(127,omega_error*kv_converted)));
}


void loop() 
{
    
}