/* This function controls the cursor movement targeting the opponent,
 * and returns the selected location.
 * A separate function is used because it no longer needs to account
 * for the size or orientation of the ships.
 */

#include "lcd_image.h"
#include "Images.h"

#ifndef __CURSORT__H
#define __CURSORT__H

// Joystick pins:
#define VERT    0 // Analog input A0 - vertical
#define HORIZ   1 // Analog input A1 - horizontal
#define SEL     9 // Digital input pin 9 for the joystick button

extern Adafruit_ST7735 tft;
extern lcd_image_t Images[];
int CursorT(int8_t* Array);
#define unit 12  // This is because one block on board is going to be
                 // 12x12 pixels

#endif
