const int MOT=19;
  uint32_t speed =0; 
  uint32_t on=3;
  uint32_t off=0;  
void setup() {                
  // initialize the digital pin as an output.
  pinMode(MOT, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(MOT, HIGH);
  delayMicroseconds(1);
  digitalWrite(MOT, LOW);
  delayMicroseconds(10);
}
