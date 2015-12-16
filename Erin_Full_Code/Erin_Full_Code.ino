#include <Wire.h>
#include "Energia.h"
#include "Timer.h"
#include <I2Cdev.h>

// These lines are only when running an Arduino Master
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(10, 11); // RX, TX

const bool FLIPPED = false;
bool go=true;

// MPU Variables
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
float pi=3.141592;
// theta is in degrees, omega is in degrees/second
float theta, omega, theta_a, theta_g;

// Encoder Variables
int16_t raw_encoder_data[2] = {0,0};
float encoder_RS = 0;
float encoder_LS = 0;

// Control Parameters
const float kv = 0.6; // in volts per radian
const float kv_converted = kv * float(127)/24; // In steps per radian
float omega_error;
float Vc=0; float Vcm1 = 0; float Vcm2 = 0;
float thetam1=0; float thetam2=0;
Timer myTimer;
float dt=20; 

//Safety Parameters
const float THETA_KILLYOFAMILY = 40;
int SAFETY_PIN = 33;
bool ALLGOODCAPN = true;

uint8_t status = 1;
const uint8_t myLED = BLUE_LED;

void timerFunction()
{
    status = 1 - status;
    digitalWrite(myLED, status);
    go=true;
}


void setup()
{ 
  pinMode(myLED, OUTPUT);
  digitalWrite(myLED, HIGH);

  pinMode(SAFETY_PIN, INPUT);

  Wire.begin();
  Serial.begin(9600);
  delay(50);
  Serial.println("Serial Initialized");

  prepSabretooth();  
  prepMPUs();
 

  myTimer.begin(timerFunction, 20);
  myTimer.start();
  digitalWrite(myLED, LOW);
}


void loop() 
{
if (go==true){
  go=false;
  collectMPUData();
  collectEncoderData();
  //Serial.println(encoder_RS);
  //Serial.println(1.5*theta);
  
  //Control code goes here
  //Vc=theta*(pi/180)*200;//WORKS
  //Vc = 1.03*(theta*(pi/180))-(0.9703*(thetam1*(pi/180)))+Vcm1;
  //Vc = 15.38*(theta*(pi/180))-(14.62*(thetam1*(pi/180)))+Vcm1;
  
  Vc = 5*21.74*(theta*(pi/180)) - 5*20.74*(thetam1*(pi/180)) + 1.002*Vcm1;
  
  //Limiting and stuff

  Protect();
  if (ALLGOODCAPN){
    VelocityControlMotorRS(Vc); 
    VelocityControlMotorLS(Vc);
  } else {
    driveMotorRS(0);
    driveMotorLS(0); 
  }
  UpdateVars();
} 
}


void Protect(){
  digitalWrite(RED_LED,!digitalRead(SAFETY_PIN));
  if ((abs(theta) > THETA_KILLYOFAMILY) || digitalRead(SAFETY_PIN)){
    ALLGOODCAPN = false;
    Vc = 0;
    Vcm1 = 0;
    Vcm2 = 0;
  } else {
    ALLGOODCAPN = true;
  }
  Vc=max(min(Vc,15),-15);
}


void UpdateVars(){
  thetam2=thetam1;
  thetam1=theta;
  Vcm2=Vcm1;
  Vcm1=Vc; 
}
