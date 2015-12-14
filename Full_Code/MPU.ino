#include <MPU6050.h>

MPU6050 accelgyro1(MPU6050_ADDRESS_AD0_LOW);
MPU6050 accelgyro2(MPU6050_ADDRESS_AD0_HIGH);

int gz1_offset = 88;

void prepMPUs()
{
  Serial.println("Initializing MPUs...");
  //accelgyro1.initialize();
  accelgyro2.initialize();
  Serial.println("Testing device connections...");
  //Serial.println(accelgyro1.testConnection() ? "MPU6050 A connection successful" : "MPU6050 A connection failed");
  Serial.println(accelgyro2.testConnection() ? "MPU6050 B connection successful" : "MPU6050 B connection failed");
   
  //accelgyro1.setRate(0);
  //accelgyro1.setDLPFMode(1); //BW 184
  //accelgyro1.setFullScaleGyroRange(1); //pm 500
  //accelgyro1.setFullScaleAccelRange(1); //pm 4g
 
  accelgyro2.setRate(0);
  accelgyro2.setDLPFMode(1); //BW 184
  accelgyro2.setFullScaleGyroRange(1); //pm 500
  accelgyro2.setFullScaleAccelRange(1); //pm 4g
  
  collectMPUData(); //Populate the data
  if (FLIPPED) {
    theta_a = -atan2(ax1,ay1)*180/3.1415;
    theta_g = theta_a;
    theta = theta_a;
  } else{
    theta_a = -atan2(-ax1,-ay1)*180/3.1415; // Initialize the angle
    theta_g = theta_a;
    theta = theta_a;
  }
  
  Serial.println("MPUs Initialized");
}


// Collects the MPU data and updates the angle guess.
void collectMPUData(){
  accelgyro2.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  //accelgyro2.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);

  if (FLIPPED) {
    omega = -float(gz1+gz1_offset)/65; //radians per second
    theta = 0.98 * (theta + omega*((float)dt)/1000) + 0.02 * -atan2(ax1,ay1)*180/3.1415;
    theta_a = -atan2(ax1,ay1)*180/3.1415; // Just accelerometer part
    theta_g = (theta_g + omega*((float)dt)/1000); // Just gyro part
  } else { 
    omega = -float(gz1+gz1_offset)/65; //radians per second
    theta = 0.98 * (theta + omega*((float)dt)/1000) + 0.02 * -atan2(-ax1,-ay1)*180/3.1415;
    theta_a = -atan2(-ax1,-ay1)*180/3.1415; // Just accelerometer part
    theta_g = (theta_g + omega*((float)dt)/1000); // Just gyro part
  }
}


// Prints out all the MPU data, if we want to see it
void serialOutMPUData(){
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
}
