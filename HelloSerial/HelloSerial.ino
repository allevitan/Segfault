#include "Wire.h"

#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
char ch;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    
 accelgyro.setRate(0);
accelgyro.setDLPFMode(1); //BW 184
 accelgyro.setFullScaleGyroRange(1); //pm 500
accelgyro.setFullScaleAccelRange(1); //pm 4g    
} 


void loop() {
accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  if (Serial.available()) 
  {

     ch = Serial.read();

     if ( ch == '1' ) { 
          Serial.print("a/g:\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.print("\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.println(gz);
     } 

  }

}
