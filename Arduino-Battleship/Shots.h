/* Fire is used to target a square in the other player's ocean and
 * communicate your attack via serial3. It also reads back the result
 * of the shot.
 * Get_Shot_At does the opposite. ie. it waits to receive an "attack"
 * from Serial3, then calculates the result and writes it back to the
 * other arduino.
 */ 

#include "Place_Ships.h"

#ifndef __FIRE__H
#define __FIRE__H

extern Adafruit_ST7735 tft;
extern lcd_image_t Images[];
bool Fire(int8_t* Array);
bool Get_Shot_At(int8_t* Array, Ship* Ships);

#endif
