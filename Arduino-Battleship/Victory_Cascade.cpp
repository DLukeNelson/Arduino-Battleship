/* Blink the LEDs in a fancy pattern for the winner.
 */

#include "Victory_Cascade.h"

// First pin is used to decide between blinking the green lights (for
// the winner) or the red lights (for the loser).
void Victory_Cascade(int firstpin) {
  
  int bluePin = 36;   
  int greenPin = 37;
  int redPin = 38;
  
  // Initializes the RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  int reset;
    
  while (true) {
    
    // Use the joystick button press to break this loop (and restart the
    // game). Because we use delays in this function, the button must be
    // held in to ensure that it is pressed at the moment that the
    // program reads for it. Reminiscent of classic game consoles, we
    // left this in.
    reset = digitalRead(9);
    if (!reset) {break;}
    
    // This loop turns all the lights on, one by one.
    for (int i = 0; i <= 6; ++i ) {
      digitalWrite(i*2 + firstpin, HIGH); 
      
      // This if-statement is to make the RGB LED transistion through
      // each of its colors. The colors change as a function of the
      // value of "i". Of the three lines present in each statement, one
      // turns a certain color on while the other two lines turn the 
      // other colours off.
      if ((i == 1 )||(i == 2)) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 200);
        analogWrite(bluePin, 0);  
      } else if ((i == 3) || (i == 4)) {
        analogWrite(redPin, 200);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);  
      } else {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 200);  
      }
      
      delay(75);
    }
    // This loop turns all the lights off, one by one.
    for (int i = 0; i <= 6; ++i ) {
      digitalWrite(i*2 + firstpin, LOW);
      
      // This if-statement is identical to the one in the winner's case
      if ((i == 1 )||(i == 2)) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 200);
        analogWrite(bluePin, 0);  
      } else if ((i == 3) || (i == 4)) {
        analogWrite(redPin, 200);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);  
      } else {
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 200);  
      }
      delay(75);
    }
  }
}
