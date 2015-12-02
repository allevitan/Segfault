const int MOT=18;
  uint32_t speed =70; 
  uint32_t on=0;
  uint32_t off=0; 
  int rev=0; 
void setup() {                
  // initialize the digital pin as an output.
  pinMode(MOT, OUTPUT);  
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
   if (speed>110) {
   rev=0;
  }
  
  if (speed<50) {
   rev=1;
  }
  on=1000+speed;
  off=20000-on;
  for (long i=0; i <= 100; i++){
  digitalWrite(MOT, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(on);               // wait for a second
  digitalWrite(MOT, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(off);
  }
  if (rev==1){
  speed=speed+10;
  }
  if (rev==0){
    speed=speed-10;
  }
//delay(5000);  // wait for a second
//  Serial.print(on);
//  Serial.print("\t");
//  Serial.println(off);
}
