#define LED_PIN RED_LED

byte START_BYTE = 170;
byte SYREN_ADDR = 128;
byte CMD_FORWARD1 = 0;
byte CMD_BACKWARD1 = 1;
byte CMD_FORWARD2 = 4;
byte CMD_BACKWARD2 = 5;
byte _cmd1 = CMD_BACKWARD1;
byte _cmd2 = CMD_BACKWARD2;
byte _data = 20;
byte _checksum = 0;

// Define variables for interfacing with the x86
byte _ledState = 0;
char _buff[10];
int _indx = 0;

void setup() {
//  Serial.begin(9600);
  
  Serial1.begin(9600);
  delay(3000); // allow motor controller to boot
  
//  Serial.println('Serial Starting'); // set the baud rate
  Serial1.write(START_BYTE); // set the baud rate
  
  pinMode(LED_PIN, OUTPUT);  // enable LED
}

void loop() {
  // Read in a speed command
//  Serial.println('Serial Starting');
//  while (Serial.available() && _indx < 9) {
//    _buff[_indx++] = Serial.read();
//    if (_buff[_indx-1] == 0x0A) {  // if last char is newline char
//      _indx = 0;
//      int speed = atoi(_buff);
//      
//      if (speed <= 127 && speed >= -127) {
//        if (speed > 0) {
//          _cmd = CMD_FORWARD;
//          _data = speed;
//        } else {
//          _cmd = CMD_BACKWARD;
//          _data = -speed;
//        }
//        _checksum = 0x7F & (SYREN_ADDR + _cmd + _data);
//      
//        Serial.print("Speed: ");
//        Serial.print(speed);
//        Serial.print(", Cmd: ");
//        Serial.print(_cmd);
//        Serial.print(", Data: ");
//        Serial.print(_data);
//        Serial.print(", Checksum: ");
//        Serial.println(_checksum);
//      } else {
//        Serial.println("Invalid speed.");
//      }
//    
//      digitalWrite(LED_PIN, _ledState);
//      _ledState = !_ledState; 
//    }
//  }
  _checksum = 0x7F & (SYREN_ADDR + _cmd1 + _data);
  Serial1.write(SYREN_ADDR); // send address byte
  Serial1.write(_cmd1);
  Serial1.write(_data);
  Serial1.write(_checksum);
  
  _checksum = 0x7F & (SYREN_ADDR + _cmd2 + _data);
  Serial1.write(SYREN_ADDR); // send address byte
  Serial1.write(_cmd2);
  Serial1.write(_data);
  Serial1.write(_checksum);
  
  delay(1000);
}
