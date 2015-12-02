// This code runs the encoder for our Fall 2015 Controls Project
// Abe Levitan, Erin Pierce, Paul Titchener
//
// When a byte (any byte) is written to the board over I2c,
// It will respond with a series of ?? bytes, the first
// ?? being a float with the data from encoder 1 and the
// second ?? being a float with the data from encoder 2. The
// output is the number of counts in the last LOOPTIME
//
// OPTIONS
// QUADRATURE: If true, the program will attempt to calculate
//             direction as well as speed
// LOOPTIME: The time to wait in between recounts
//


#include <Wire.h>

// More than we need, but basically a set of high-speed read and
// write operations
#define portOfPin(P)\
  (((P)>=0&&(P)<8)?&PORTD:(((P)>7&&(P)<14)?&PORTB:&PORTC))
#define ddrOfPin(P)\
  (((P)>=0&&(P)<8)?&DDRD:(((P)>7&&(P)<14)?&DDRB:&DDRC))
#define pinOfPin(P)\
  (((P)>=0&&(P)<8)?&PIND:(((P)>7&&(P)<14)?&PINB:&PINC))
#define pinIndex(P)((uint8_t)(P>13?P-14:P&7))
#define pinMask(P)((uint8_t)(1<<pinIndex(P)))

#define pinAsInput(P) *(ddrOfPin(P))&=~pinMask(P)
#define pinAsInputPullUp(P) *(ddrOfPin(P))&=~pinMask(P);digitalHigh(P)
#define pinAsOutput(P) *(ddrOfPin(P))|=pinMask(P)
#define digitalLow(P) *(portOfPin(P))&=~pinMask(P)
#define digitalHigh(P) *(portOfPin(P))|=pinMask(P)
#define isHigh(P)((*(pinOfPin(P))& pinMask(P))>0)
#define isLow(P)((*(pinOfPin(P))& pinMask(P))==0)
#define digitalState(P)((uint8_t)isHigh(P))


const bool QUADRATURE = true;

const int MASTER_ADDR = 42;
const int MY_ADDR = 43;

const int E1_PIN1 = 2;
const int E1_PIN2 = 4;
const int E2_PIN1 = 3;
const int E2_PIN2 = 5;

const int LOOPTIME = 50; //Time for each counting period, in ms

volatile int8_t E1Steps = 0;
volatile int8_t E2Steps = 0;
int8_t E1StepsOut = 0;
int8_t E2StepsOut = 0;

long int lastTime = 0;

byte tosend[2] = {0, 0};

//Quadrature
void E1_ISR_Q(){
  E1Steps += (isHigh(E1_PIN1) != isHigh(E1_PIN2))*2-1;
}

//Birature
void E1_ISR_B(){
  E1Steps += 1;
}


//Quadrature
void E2_ISR_Q(){
  E2Steps += (isHigh(E2_PIN1) != isHigh(E2_PIN2))*2-1;
}

//Birature
void E2_ISR_B(){
  E2Steps += 1;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Wire.begin(MY_ADDR); // join i2c bus with address #42
  Wire.onRequest(requestEvent);

  Serial.begin(9600);
  pinMode(E1_PIN2,INPUT);
  pinMode(E2_PIN2,INPUT);
  if (QUADRATURE){
    attachInterrupt(digitalPinToInterrupt(E1_PIN1), E1_ISR_Q, CHANGE);
    attachInterrupt(digitalPinToInterrupt(E2_PIN1), E2_ISR_Q, CHANGE);
  }else{
    attachInterrupt(digitalPinToInterrupt(E1_PIN1), E1_ISR_B, CHANGE);
    attachInterrupt(digitalPinToInterrupt(E2_PIN1), E2_ISR_B, CHANGE);
  }
  lastTime = millis();
}

void loop() {

  // This does the counting work
  if (millis() - lastTime > LOOPTIME){
    lastTime = millis();
    E1StepsOut = E1Steps;
    E2StepsOut = E2Steps;
    E1Steps = 0;
    E2Steps = 0;

    tosend[0]=byte(E1StepsOut);
    tosend[1]=byte(E2StepsOut);

    // Comment this out in "production", leave in for early debugging
    //Serial.print(E1StepsOut);
    //Serial.print(',');
    //Serial.println(E2StepsOut);
  }

}

void requestEvent(){
  Wire.write(tosend,2);
}
