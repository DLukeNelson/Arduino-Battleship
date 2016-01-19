/* Fire is used to target a square in the other player's ocean and
 * communicate your attack via serial3. It also reads back the result
 * of the shot.
 * Get_Shot_At does the opposite. ie. it waits to receive an "attack"
 * from Serial3, then calculates the result and writes it back to the
 * other arduino.
 */ 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#include "CursorT.h"
#include "Shots.h"
#include "Write_Message.h"
#include "SoundFX.h"

// Checks if a hit actually sinks a ship, and returns 1 if it does.
// Otherwise returns 0.
bool Hit_My_Ship(int8_t* Array, int8_t target, Ship* Ships) {
  // The tens digit of the value in the Array tracks which ship is there
  // so an integer division by 10 returns a number from 0-4.
  // If that ship has a nonzero size (remaining pieces) even after the
  // decrement, then Hit_My_Ship returns 0, because the ship is still
  // alive.
  if( --Ships[Array[target]/10].size ) {
    return 0;
  }
  // If the decrement reduces the ship's "size" to 0, this will return 1
  // which indicates that a ship has been sunk.
  else {
    return 1;
  }
}

// Uses cursorT to target a square and send that "attack" to the other
// arduino. Waits to receive the result and updates the local info.
bool Fire(int8_t* Array) {
  // Select a square
  int8_t target = CursorT(Array);
  // write that square to the other arduino.
  Serial3.write(target);
  // waits for a result.
  while( !Serial3.available() ) {}
  // reads the result.
  int8_t result = Serial3.read();
  
  // if the result is greater than 10, we know we sunk a ship.
  if( result/10 ) {
    Write_Message("You sunk a ship!");
  }
  // %10 ensures that a 12 (ship sunk) becomes a 2 (hit), otherwise, has
  // no effect (nothing else greater than 10 should be read).
  Array[target] = result%10;
  
  // draws the resulting image patch to the target square.
  lcd_image_draw(&Images[Array[target]%10], &tft, 0, 0,
          (12*(target%10))+8, (12*(target/10))+8, 12, 12);
  // return a 1 if a ship was sunk, in order to decrement the counter
  // of the other players remaining ships. return 0 otherwise.
  delay(3000); // This delay allows a player to view the result of their
               // shot, and also makes an approximate synchronization
               // with the other player's delay from the sound effect.
  return result/10;
}

// Waits for an "attack" then calculates its result and write the result
// arduino. Also updates our own information with the result.
bool Get_Shot_At(int8_t* Array, Ship* Ships) {
  // Waits for an "attack" through serial3.
  while( !Serial3.available() ) {}
  // reads which square has been targeted.
  int8_t target = Serial3.read();
  
  // If that square has 0 or 1 (water or miss).
  if( Array[target] <=1 ) {
    // set its value to 1 (miss)
    Array[target] = 1;
    // Write a 1 (miss) to other arduino.
    Serial3.write(1);
    // draw a miss square
    lcd_image_draw(&Images[miss], &tft, 0, 0,
          (12*(target%10))+8, (12*(target/10))+8, 12, 12);
    // play a miss sound effect.
    Sound_Miss();
  }
  // If that square has 2 (already been hit)
  else if( Array[target] == 2) {
    // Write a 2 (so that other arduino still has the correct data)
    Serial3.write(2);
    // But, play a miss sound effect.
    Sound_Miss();
  }
  // By elimination, a ship must have been hit. Calls Hit_My_Ship
  else{
    // If Hit_My_Ship returns 1, a ship has been sunk.
    if( Hit_My_Ship(Array, target, Ships) ) {
      Write_Message("They sunk a ship!");
      // The two represents a hit (for the image patch), the 10 denotes
      // that a ship has been sunk.
      Serial3.write(12);
      // set our array to 2 (hit)
      Array[target] = 2;
      // draw a hit square
      lcd_image_draw(&Images[Array[target]%10], &tft, 0, 0,
          (12*(target%10))+8, (12*(target/10))+8, 12, 12);
      // play a hit sound effect.
      Sound_Hit();
      // return 1 to decrement our counter of how many ships are alive.
      return(1);
    }
    else { // A ship was not sunk.
      // Write back a 2 (hit)
      Serial3.write(2);
      // set our array to 2 (hit)
      Array[target] = 2;
      // draw a hit square
      lcd_image_draw(&Images[Array[target]%10], &tft, 0, 0,
          (12*(target%10))+8, (12*(target/10))+8, 12, 12);
      // play a hit sound effect.
      Sound_Hit();
    }
  }
  // Note that the playing of the sound effects creates an adequate
  // delay to allow a player to view the effects of the shot.
  // (about 4 seconds).
  // if a ship has not been sunk, return 0.
  return 0;
}
