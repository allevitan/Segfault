#include "Wire.h"

#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro1(MPU6050_ADDRESS_AD0_LOW);
MPU6050 accelgyro2(MPU6050_ADDRESS_AD0_HIGH);


int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;

int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;
int filt;

#define LED_PIN RED_LED
bool blinkState = false;
char start='0';

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    accelgyro1.initialize();
    accelgyro2.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro1.testConnection() ? "MPU6050 A connection successful" : "MPU6050 A connection failed");
    Serial.println(accelgyro2.testConnection() ? "MPU6050 B connection successful" : "MPU6050 B connection failed");

    pinMode(LED_PIN, OUTPUT);
    
 accelgyro1.setRate(0);
 accelgyro1.setDLPFMode(1); //BW 184
 accelgyro1.setFullScaleGyroRange(1); //pm 500
 accelgyro1.setFullScaleAccelRange(1); //pm 4g
 
 accelgyro2.setRate(0);
 accelgyro2.setDLPFMode(1); //BW 184
 accelgyro2.setFullScaleGyroRange(1); //pm 500
 accelgyro2.setFullScaleAccelRange(1); //pm 4g
    
    
    
}

void loop() {
  
    // read raw accel/gyro measurements from device
    accelgyro1.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
    accelgyro2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
    
    Serial.print("a/g:\t");
    Serial.print(ax1); Serial.print("\t");
    Serial.print(ay1); Serial.print("\t");
    Serial.print(az1); Serial.print("\t");
    Serial.print(gx1); Serial.print("\t");
    Serial.print(gy1); Serial.print("\t");
    Serial.print(gz1);Serial.print("\t");
    Serial.print(ax2); Serial.print("\t");
    Serial.print(ay2); Serial.print("\t");
    Serial.print(az2); Serial.print("\t");
    Serial.print(gx2); Serial.print("\t");
    Serial.print(gy2); Serial.print("\t");
    Serial.println(gz2);
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
//    delay(40);
    // blink LED to indicate activity

}
