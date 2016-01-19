/* This function controls the cursor movement for placing ships,
 * and returns the selected location.
 * It has its own function so that it can account for the size and
 * orientation of the ships that are being placed.
 */

#include "lcd_image.h"
#include "Images.h"

#ifndef __CURSOR__H
#define __CURSOR__H

// Joystick pins:
#define VERT    0 // Analog input A0 - vertical
#define HORIZ   1 // Analog input A1 - horizontal
#define SEL     9 // Digital input pin 9 for the joystick button
#define Button1 3 // Digital input pin 3 for the button

void Initialize_Cursor();

extern Adafruit_ST7735 tft;
extern lcd_image_t Images[];

void HorizontalRedraw(int size, int8_t* Array, int loc);
void VerticalRedraw(int size, int8_t* Array, int loc);

int Cursor(int size, bool* Orientation, int8_t* Array);
#define unit 12  // This is because one block on board is going to be
                 // 12x12 pixels

#endif
