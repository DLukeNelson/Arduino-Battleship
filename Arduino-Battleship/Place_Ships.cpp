/* Function for a player to place his ships at the start of the game.
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "Place_Ships.h"
#include "Draw_Screen.h"
#include "lcd_image.h"
#include "Images.h"
#include "Cursor.h"
#include "SoundFX.h"

Ship Ship_Array[5]; // Creates an array of 5 ships that will be
                    // defined below.

// Checks if a selected location is a valid ship placement. (ie. Ensures
// that a player cannot overlap ships.)
bool Valid_Horiz(int8_t* Array, int location, int size) {
  for( int i=0; i<size; i++ ) { // checks each square in a ship's size
    // if that location is nonzero, then a ship must be there
    if( Array[location+i] != 0 ) {
      return 1; // return 1 for invalid location
    }
  }
  // return 0 if the location is fine. Can only reach this point by
  // checking each square in the grid. 
  return 0;
}

// Works just as Valid_Horiz, but for a vertically placed ship.
bool Valid_Vert(int8_t* Array, int location, int size) {
  for( int i=0; i<size; i++ ) {
    if( Array[location+i*10] != 0 ) {
      return 1;
    }
  }
  return 0;
}

Ship* Place_Ships(int8_t* Array, int8_t* ArraytoCheck) {
  // draw a green square at the top left corner
  tft.fillRect(0, 0, 8, 8, 0x07E0);
  // draw the screen (will always be a blank ocean).
  Draw_Screen(Array, ArraytoCheck);
  
  // Carrier = 5 (#defined in Place_Ships.h)
  int remainingShips = Carrier;
  
  // create some text settings for use later
  tft.setTextWrap(false);
  tft.setTextColor(0xFFFF, 0);
  
  // initialize the array of ships
  Ship_Array[Carrier]    = (Ship){"Carrier",    1, 5, 0};
  Ship_Array[Battleship] = (Ship){"Battleship", 1, 4, 0};
  Ship_Array[Cruiser]    = (Ship){"Cruiser",    1, 3, 0};
  Ship_Array[Submarine]  = (Ship){"Submarine",  1, 3, 0};
  Ship_Array[Destroyer]  = (Ship){"Destroyer",  1, 2, 0};
  
  // A while loop was chosen over a for loop so it is easy to repeat
  // when an invalid ship placement attempt occurs.
  while( remainingShips >= 0 ) {
    // set the cursor and write text at the bottom of the screen.
    tft.setCursor(0, 129);
    tft.println("Please place your:");
    tft.print(Ship_Array[remainingShips].name);
    tft.print(" (");
    tft.print(Ship_Array[remainingShips].size);
    tft.print(")   ");
    // draw an example of the ship to be placed at the bottom.
    lcd_image_draw(&Images[shipl], &tft, 0, 0, 25, 146, unit, unit);
    for(int i = 1; i<Ship_Array[remainingShips].size; i++) {
      if( i+1 != Ship_Array[remainingShips].size ) {
        lcd_image_draw(&Images[shipm], &tft, 0, 0, 25+(12*i), 146, unit, unit);
      }
      else {
        lcd_image_draw(&Images[shipr], &tft, 0, 0, 25+(12*i), 146, unit, unit);
        if( remainingShips != 4 ) {
          tft.fillRect(25+(unit*(i+1)), 146, unit, unit, 0);
        }
      }
    }
    // Use the cursor to select a location for the ship.
    Ship_Array[remainingShips].location = Cursor(
                      Ship_Array[remainingShips].size,
                      &Ship_Array[remainingShips].orientation, Array);
    
    // Refer to line 49 in Battleship.cpp for how My_Ocean (called Array
    // in this function) works.
                      
    // For horizontal ships.
    if( Ship_Array[remainingShips].orientation == 1 ) {
      if( Valid_Horiz(Array, Ship_Array[remainingShips].location,
                Ship_Array[remainingShips].size) ) {
        // if the location was invalid, write an error message.
        tft.setCursor(0,129);
        tft.print("Invalid location  ");
        // redraw the spot where the cursor was.
        HorizontalRedraw(Ship_Array[remainingShips].size,
              Array, Ship_Array[remainingShips].location);
              
        Sound_Error(); // play an error sound effect.
        delay(500); // A short delay (plus the delay from the sound
                    // effect) to allow time to see the error message.
      }
      else { // if the location was valid.
        // Set the value of Array[location] to shipl, associated to the
        // ship currently being placed.
        Array[Ship_Array[remainingShips].location] = shipl+10*remainingShips;
        // Draw a shipl image.
        lcd_image_draw(&Images[shipl], &tft, 0, 0,
                        (Ship_Array[remainingShips].location%10)*unit+8,
                        (Ship_Array[remainingShips].location/10)*unit+8,
                                  unit, unit);
        
        // goes through each remaining piece of the ship.
        for( int i = 1; i<Ship_Array[remainingShips].size; i++ ) {
          // assigns each piece (up to size-1) of the ship to its
          // corresponding position in the array as shipm, and draws it.
          if( i+1 != Ship_Array[remainingShips].size ) {
            Array[Ship_Array[remainingShips].location+i] = shipm+10*remainingShips;
            lcd_image_draw(&Images[shipm], &tft, 0, 0,
                              ((Ship_Array[remainingShips].location+i)%10)*12+8,
                              (Ship_Array[remainingShips].location/10)*12+8,
                                  unit, unit);
          }
          // assigns the last piece of the ship, shipr to its
          // corresponding position in the array, and draws it.
          else {
            Array[Ship_Array[remainingShips].location+i] = shipr+10*remainingShips;
            lcd_image_draw(&Images[shipr], &tft, 0, 0,
                              ((Ship_Array[remainingShips].location+i)%10)*12+8,
                              (Ship_Array[remainingShips].location/10)*12+8,
                                  unit, unit);
          }
        }
        // decrement remaining ships. (Is not decremented when the
        // placement fails the validity check, so that the loop repeats
        // for the same ship over again.)
        remainingShips--;
      }
    }
    // For vertical ships.
    else if( Ship_Array[remainingShips].orientation == 0 ) {
      // if the location was invalid
      if( Valid_Vert(Array, Ship_Array[remainingShips].location,
                Ship_Array[remainingShips].size) ) {
        tft.setCursor(0,129);
        tft.print("Invalid location  ");
        Ship_Array[remainingShips].orientation = 1;
        // redraw the spot where the cursor was
        VerticalRedraw(Ship_Array[remainingShips].size,
              Array, Ship_Array[remainingShips].location);
        Sound_Error();
        delay(500); // delay to view the error message.
      }
      else { // location was invalid
        // Same process as above, with slight modifications for vertical
        // instead of horizontal.
        Array[Ship_Array[remainingShips].location] = shipt+10*remainingShips;
        
        lcd_image_draw(&Images[shipt], &tft, 0, 0,
                          (Ship_Array[remainingShips].location%10)*12+8,
                          (Ship_Array[remainingShips].location/10)*12+8,
                                  unit, unit);
        
        
        for( int i = 1; i<Ship_Array[remainingShips].size; i++ ) {
          if( i+1 != Ship_Array[remainingShips].size ) {
            Array[Ship_Array[remainingShips].location+10*i] = shipm+10*remainingShips;
            lcd_image_draw(&Images[shipm], &tft, 0, 0,
                        (Ship_Array[remainingShips].location%10)*12+8,
                        (Ship_Array[remainingShips].location/10+i)*12+8,
                                  unit, unit);
          }
          else {
            Array[Ship_Array[remainingShips].location+10*i] = shipb+10*remainingShips;
            lcd_image_draw(&Images[shipb], &tft, 0, 0,
                          (Ship_Array[remainingShips].location%10)*12+8,
                          (Ship_Array[remainingShips].location/10+i)*12+8,
                                  unit, unit);
          }
        }
      remainingShips--;
      }
    }
  }
  return Ship_Array;
}
