/* This function controls the cursor movement for placing ships,
 * and returns the selected location.
 * It has its own function so that it can account for the size and
 * orientation of the ships that are being placed.
 */
 
#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "lcd_image.h"
#include "Images.h"
#include "Cursor.h"

bool button1Press;

// Joystick info
int vertical, horizontal, select, swap_orientation;
int cursor_x, cursor_y, old_cursor_x, old_cursor_y;
int init_vert, init_horiz; 
int delta_vert, delta_horiz;

// called by the main function during initialization in order to
// calibrate the joystick.
void Initialize_Cursor() {
  init_vert = analogRead(VERT);
  init_horiz = analogRead(HORIZ); 
}

// Redraws "size" number of squares in the horizontal (right) direction
// from the location of the cursor.
void HorizontalRedraw(int size, int8_t* Array, int loc) {
    for (int i = 0; i < size; ++i) {
      // i+loc represents the square to draw. This if ensures that the
      // redraw process does not carry from one row to the next.
      // The constraints on the cursor usually prevent this from being
      // an issue, but will not always cover this when swapping between
      // vertical and horizontal ship orientations.
      if ((i+loc)/10 != loc/10) {break;}
      
      // Find and draw the replacement images.
      int replacementImage = Array[loc+i]%10;
      lcd_image_draw(&Images[replacementImage], &tft, 0, 
                   0, old_cursor_x+unit*i, old_cursor_y, unit, unit);
    }
}

// Redraws "size" number of squares in the vertical (downward) direction
// from the location of the cursor.
void VerticalRedraw(int size, int8_t* Array, int loc) {
    for (int j = 0; j < size; ++j) {
      
      // This if works just as in horizontal redraw.
      if ((loc+10*j) > 99) {break;}
      int replacementImage = Array[loc+j*10]%10;
      lcd_image_draw(&Images[replacementImage], &tft, 0, 
                   0, old_cursor_x, old_cursor_y+unit*j, unit, unit);
    }
}

int Cursor(int size, bool* Orientation, int8_t* Array) {
  // initial cursor position
  cursor_x = 68;
  cursor_y = 68; 
  
  // These values hold the last cursors value.
  old_cursor_x = cursor_x;
  old_cursor_y = cursor_y;
  
  // draw the initial cursor
  tft.drawRect(cursor_x, cursor_y, unit*size, unit, 0xFFFF);  
  
  
  while (true) {
    // read inputs from the joystick as well as the pushbutton
    swap_orientation = digitalRead(Button1);
    select = digitalRead(SEL);
    vertical = analogRead(VERT);        
    horizontal = analogRead(HORIZ);
    
    // If the joystick has moved, this if-statement will update the
    // position of the cursor and redraw the map inplace of the
    // old cursor.
    if (old_cursor_x != cursor_x || old_cursor_y != cursor_y) {
      // Find the current location
      // (converts pixel location to grid location).
      int location = (old_cursor_x/unit)+(10*(old_cursor_y/unit));
      
      if (*Orientation == HORIZ) {  // horizontal ship/cursor.
        HorizontalRedraw(size, Array, location);
        tft.drawRect(cursor_x, cursor_y, unit*size, unit, 0xFFFF);
      } else { // vertical ship/cursor.
        VerticalRedraw(size, Array, location);
        tft.drawRect(cursor_x, cursor_y, unit, unit*size, 0xFFFF);  
      }
    }
    
    if( select == LOW ) { // if joystick button is pushed.
      // Find the current location.
      int location = (cursor_x/unit)+(10*(cursor_y/unit));
      
      // returns the location (leftmost or uppermost grid square)
      // Since the orientation was sent here as a pointer, it is
      // essentially "returned" as well.
      return location;
    }
    
    // If the orientation button is pressed
    if( swap_orientation == LOW ) {
        button1Press = 1;
    }
    // This part eliminates any issues with a button press being
    // counted twice because it is held in for slightly too long.
    if( (button1Press == 1) && (swap_orientation == HIGH) ) {
        // swap the orientation from its old truth value, and make the
        // value of 'button1Press' to 0 again, allowing it to be used
        // once more
        *Orientation = !(*Orientation);
        button1Press = 0;
        
        // redraw over the old cursor.
        int location = (cursor_x/unit)+(10*(cursor_y/unit));
        if (*Orientation == HORIZ) {
            // Because vertical is the prior orientation.
            VerticalRedraw(size, Array, location); 
        }
        if (*Orientation == VERT) {
            // Because horizontal is the prior orientation.
            HorizontalRedraw(size, Array, location);
        }
        // constrain the cursor. (only an issue at right and bottom
        // edges of the screen).
        if (cursor_x >= 128-size*unit) {cursor_x = 128-size*unit;}
        if (cursor_y >= 128-size*unit) {cursor_y = 128-size*unit;}
        
        // Redraw the cursor of the correct size and proper orientation.
        if (*Orientation == HORIZ) {
          tft.drawRect(cursor_x, cursor_y, unit*size, unit, 0xFFFF);
        }
        if (*Orientation == VERT) {
          tft.drawRect(cursor_x, cursor_y, unit, unit*size, 0xFFFF);
        }
    }
    
    // sets the joystick read to either a one or a zero, to ensure that
    // the cursor moves only one grid square at a time.
    delta_vert = (vertical - init_vert)/300;
    delta_horiz = (horizontal - init_horiz)/300;
    
    // Sets the old position of the cursor
    old_cursor_x = cursor_x;
    old_cursor_y = cursor_y;
    
    // Ensure that the cursor never leaves the playing area.
    // There is also a small delay in order to keep the cursor from
    // moving too fast in order to provide more control of the joystick.
    if (delta_horiz < 0) {
      if( *Orientation == HORIZ ) {
        cursor_x = constrain(cursor_x+unit, 8, 128-size*unit);
        delay(100);
      }
      else {
        cursor_x = constrain(cursor_x+unit, 8, 116);
        delay(100);
      }
    }
    if (delta_horiz > 0) {
      if( *Orientation == HORIZ ) {
        cursor_x = constrain(cursor_x-unit, 8, 128-size*unit);
        delay(100);
      }
      else {
        cursor_x = constrain(cursor_x-unit, 8, 116);
        delay(100);
      }
    }
    if (delta_vert < 0) {
      if( *Orientation == VERT ) {
        cursor_y = constrain(cursor_y+unit, 8, 128-size*unit);
        delay(100);
      }
      else {
        cursor_y = constrain(cursor_y+unit, 8, 116);
        delay(100);
      }
    }
    if (delta_vert > 0) {
      if( *Orientation == VERT ) {
        cursor_y = constrain(cursor_y-unit, 8, 128-size*unit);
        delay(100);
      }
      else {
        cursor_y = constrain(cursor_y-unit, 8, 116);
        delay(100);
      }
    }
  }
}   
