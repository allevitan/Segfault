byte START_BYTE = 170;
byte SYREN_ADDR = 128;
byte CMD_FORWARD1 = 0;
byte CMD_BACKWARD1 = 1;
byte CMD_FORWARD2 = 4;
byte CMD_BACKWARD2 = 5;


void prepSabretooth(){
//  Serial.println("Initializing Sabretooth Communication...");
  Serial1.begin(9600);
  delay(3000);
  Serial1.write(START_BYTE); // set the baud rate 
//  Serial.println("Sabretooth Communication Initialized");
}

void driveMotorRS(int8_t data){
  if (data >= 0){
    Serial1.write(SYREN_ADDR); // send address byte
    Serial1.write(CMD_FORWARD1);
    Serial1.write(byte(data));
    Serial1.write( 0x7F & (SYREN_ADDR + CMD_FORWARD1 + byte(data)));
  } else {
    Serial1.write(SYREN_ADDR); // send address byte
    Serial1.write(CMD_BACKWARD1);
    Serial1.write(byte(-data));
    Serial1.write(0x7F & (SYREN_ADDR + CMD_BACKWARD1 + byte(-data)));
  }
}

void driveMotorLS(int8_t data){
  if (data >= 0){
    Serial1.write(SYREN_ADDR); // send address byte
    Serial1.write(CMD_FORWARD2);
    Serial1.write(byte(data));
    Serial1.write( 0x7F & (SYREN_ADDR + CMD_FORWARD2 + byte(data)));
  } else {
    Serial1.write(SYREN_ADDR); // send address byte
    Serial1.write(CMD_BACKWARD2);
    Serial1.write(byte(-data));
    Serial1.write(0x7F & (SYREN_ADDR + CMD_BACKWARD2 + byte(-data)));
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
