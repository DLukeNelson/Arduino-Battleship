/* Draws the screen represented by Array onto the LCD screen. Checks to
 * see if the screen already has some of the needed images (ie. When
 * changing turns, will only redraw the things that are different
 * between the two "oceans".
 */
 
#include "Images.h"

#ifndef _DRAW_TARGET_SCREEN_H
#define _DRAW_TARGET_SCREEN_H
 
extern lcd_image_t Images[];
extern Adafruit_ST7735 tft;

void Draw_Screen(int8_t* Arraytodraw, int8_t* Arraytocheck);

#endif
