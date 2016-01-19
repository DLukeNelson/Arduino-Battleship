/* This function controls the cursor movement targeting the opponent,
 * and returns the selected location.
 * A separate function is used because it no longer needs to account
 * for the size or orientation of the ships.
 */
 
#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "lcd_image.h"
#include "Images.h"
#include "CursorT.h"
#include "Cursor.h"

// Joystick info
int verticalT, horizontalT, selectT;
int cursor_xT, cursor_yT, old_cursor_xT, old_cursor_yT;
extern int init_vert, init_horiz;
int delta_vertT, delta_horizT;

int CursorT(int8_t* Array) {  
  
  cursor_xT = 68;
  cursor_yT = 68; // initial cursor position
  old_cursor_xT = cursor_xT;
  old_cursor_yT = cursor_yT;
  tft.drawRect(cursor_xT, cursor_yT, unit, unit, 0xFFFF);  
  
  
  while (true) {
    // read inputs from joystick
    selectT = digitalRead(SEL);
    verticalT = analogRead(VERT);        
    horizontalT = analogRead(HORIZ);
    
    // exits the function, returning the selected location, upon
    // detecting a joystick button press.
    if( selectT == LOW ) {
      int location = (cursor_xT/unit)+(10*(cursor_yT/unit));
      return location;
    }
    
    // If the joystick has moved, this if-statement will update the
    // position of the cursor and redraw the map inplace of the
    // old cursor.
    if (old_cursor_xT != cursor_xT || old_cursor_yT != cursor_yT) {
      int location = (old_cursor_xT/unit)+(10*(old_cursor_yT/unit));
      
      lcd_image_draw(&Images[Array[location]%10], &tft, 0, 0,
                    old_cursor_xT, old_cursor_yT, unit, unit);
                    
      tft.drawRect(cursor_xT, cursor_yT, unit, unit, 0xFFFF);  
    }
    // standardizes the joystick change to either a one, or a zero
    // (because the cursor should be moving in fixed "unit" distances).
    delta_vertT = (verticalT - init_vert)/300;
    delta_horizT = (horizontalT - init_horiz)/300;
    
    // Sets the old position of the cursor
    old_cursor_xT = cursor_xT;
    old_cursor_yT = cursor_yT;
    
    // Makes sure the cursor cannot leave the edge of the playing area.
    if (delta_horizT < 0) {
      cursor_xT = constrain(cursor_xT+unit, 8, 116);
      delay(150);
    }
    if (delta_horizT > 0) {
      cursor_xT = constrain(cursor_xT-unit, 8, 116);
      delay(150);
    }
    if (delta_vertT < 0) {
      cursor_yT = constrain(cursor_yT+unit, 8, 116);
      delay(150);
    }
    if (delta_vertT > 0) {
      cursor_yT = constrain(cursor_yT-unit, 8, 116);
      delay(150);
    }
  }
}
