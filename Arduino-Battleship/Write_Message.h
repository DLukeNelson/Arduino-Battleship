/* This function is used to write game messages to the space at the
 * bottom of the lcd screen.
 */ 

#include "lcd_image.h"

#ifndef __WRITE__H
#define __WRITE__H

extern Adafruit_ST7735 tft;

void Write_Message(char* message);

#endif
