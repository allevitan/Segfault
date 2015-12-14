const int ENCODER_ADDR = 43;
const float ENCODER_LOOPTIME = 0.02;
const float ENCODER_CONVFACTOR = 6.283185307 / 1200 / ENCODER_LOOPTIME / 5 ;

void collectEncoderData(){
  Wire.requestFrom(ENCODER_ADDR, 8);    // request 8 bytes from slave device
  while(!Wire.available()){};
  raw_encoder_data[0] = Wire.read();
  raw_encoder_data[0] += Wire.read() << 8;
  raw_encoder_data[1] = Wire.read();
  raw_encoder_data[1] += Wire.read() << 8;
  encoder_RS = ENCODER_CONVFACTOR * raw_encoder_data[0];
  encoder_LS = ENCODER_CONVFACTOR * raw_encoder_data[1];
}
