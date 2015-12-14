#include <Wire.h>

#include <I2Cdev.h>

// These lines are only when running an Arduino Master
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(10, 11); // RX, TX

const int dt = 20; // timescale of the entire control loop
long tlast, tcur; // used to help time the main loop.

const bool FLIPPED = true;

// MPU Variables
int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;
int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
// theta is in degrees, omega is in degrees/second
float theta, omega, theta_a, theta_g;

// Encoder Variables
int16_t raw_encoder_data[2] = {0,0};
float encoder_RS = 0;
float encoder_LS = 0;

// Control Parameters
const float kv = 1.5; // in volts per radian
const float kv_converted = kv * float(127)/24; // In steps per radian
float omega_error;

void setup()
{ 
  Wire.begin();
  Serial.begin(9600);
  delay(50);
  Serial.println("Serial Initialized");
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  prepSabretooth();
  prepMPUs();
  tlast = millis();
}

void loop()
{  // put your main code here, to run repeatedly:
  tcur = millis();
  if (tcur-tlast > dt){
    tlast = tcur;
    collectEncoderData();
    Serial.print(encoder_RS);
    Serial.print(',');
    Serial.println(encoder_LS);
    //collectMPUData();
    //Serial.println(theta);
    //driveMotorRS((int8_t)theta);
    //driveMotorLS((int8_t)theta);
    VelocityControlMotorRS(float(8));
    VelocityControlMotorLS(float(8));
  }
}


void VelocityControlMotorRS(float Target_Velocity){
  omega_error = Target_Velocity - encoder_RS;
  driveMotorRS(max(-127,min(127,omega_error*kv_converted)));
}

void VelocityControlMotorLS(float Target_Velocity){
  omega_error = Target_Velocity - encoder_LS;
  driveMotorLS(max(-127,min(127,omega_error*kv_converted)));
}
