#include "Wire.h"

#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro1(MPU6050_ADDRESS_AD0_LOW);
MPU6050 accelgyro2(MPU6050_ADDRESS_AD0_HIGH);

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;

int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;

byte START_BYTE = 170;
byte SAB_ADDR = 128;
byte CMD_FORWARD = 8;
byte CMD_BACKWARD = 9;
byte cmd = CMD_FORWARD;
byte speed = 0;
byte turn = 0;
byte checksum = 0;

int8_t encoder[2] = {0, 0};
void setup()
{
  // put your setup code here, to run once:
   Wire.begin(42);
   Serial.begin(9600);
   
   Serial1.begin(9600);
   delay(3000); // allow motor controller to boot
   Serial1.write(START_BYTE); // set the baud rate
   
   checksum = 0x7F & (SAB_ADDR + 10 + turn);
   Serial1.write(SAB_ADDR); // send address byte
   Serial1.write(10);
   Serial1.write(turn);
   Serial1.write(checksum);
   
   Serial.println("Initializing I2C devices...");
   accelgyro1.initialize();
   accelgyro2.initialize();

   Serial.println("Testing device connections...");
   Serial.println(accelgyro1.testConnection() ? "MPU6050 A connection successful" : "MPU6050 A connection failed");
   Serial.println(accelgyro2.testConnection() ? "MPU6050 B connection successful" : "MPU6050 B connection failed");
   
   accelgyro1.setRate(0);
   accelgyro1.setDLPFMode(1); //BW 184
   accelgyro1.setFullScaleGyroRange(1); //pm 500
   accelgyro1.setFullScaleAccelRange(1); //pm 4g
 
   accelgyro2.setRate(0);
   accelgyro2.setDLPFMode(1); //BW 184
   accelgyro2.setFullScaleGyroRange(1); //pm 500
   accelgyro2.setFullScaleAccelRange(1); //pm 4g
}

void loop()
{
  // put your main code here, to run repeatedly:
  accelgyro1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  accelgyro2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
  
 // Serial.println("Got Data");
  int16_t var = gx1;
  if (var > 0) {cmd=CMD_FORWARD;}
  if (var < 0) {cmd=CMD_BACKWARD; var=var*-1;}
  
  var=var/5000;
  
  if (speed > 25) {speed=25;}
  speed= (byte) var;
  
  //Serial.println("Did Math");
  delay (10);
  checksum = 0x7F & (SAB_ADDR + 8 + speed);
  Serial1.write(SAB_ADDR); // send address byte
  Serial1.write(8);
  Serial1.write(speed);
  Serial1.write(checksum);
  delay(10);
  
  //Serial.println("Wrote to Motors");
  Wire.requestFrom(43, 2);    // request 2 bytes from slave device #43
  

  if(Wire.available())    // slave may send less than requested
   { 
    encoder[0] = (int8_t) Wire.read();
    encoder[1] = (int8_t) Wire.read();    
   }
// 
 
   Serial.print("a/g:\t");
   Serial.print(ax1); Serial.print("\t");
  Serial.print(ay1); Serial.print("\t");
 Serial.print(az1); Serial.print("\t");
 Serial.print(gx1); Serial.print("\t");
Serial.print(gy1); Serial.print("\t");
 Serial.print(gz1); Serial.print("\t");
 Serial.print(ax2); Serial.print("\t");
 Serial.print(ay2); Serial.print("\t");
 Serial.print(az2); Serial.print("\t");
 Serial.print(gx2); Serial.print("\t");
 Serial.print(gy2); Serial.print("\t");
 Serial.println(gz2);
 
 
 Serial.print("Speed "); Serial.print(speed); 
 if (cmd==CMD_FORWARD) {Serial.println(" Forward");}
 if (cmd==CMD_BACKWARD) {Serial.println(" Backwards");}
 
 Serial.print("Motor 1: "); Serial.println(encoder[0]);
 Serial.print("Motor 2: "); Serial.println(encoder[1]);
 Serial.println("----");

  delay(10);
}
