// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

/* Code to partner with Launchpad, sends two dummy values*/
#include <Wire.h>
byte tosend[2] = {0, 0};

void setup() {
  Wire.begin(43);                // join i2c bus with address #43
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
  tosend[0] = 12;
  tosend[1] = 42;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(tosend,2); // Send the array, length 2

}
