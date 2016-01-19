/* Function for a player to place his ships at the start of the game.
 * Includes collision checks so a player cannot overlap ships.
 * Returns the full array of each ship's information.
 */

#include "Images.h"
#include "lcd_image.h"

#ifndef _PLACE_SHIPS_H
#define _PLACE_SHIPS_H

#define Carrier     4
#define Battleship  3
#define Cruiser     2
#define Submarine   1
#define Destroyer   0

// This structure stores all the necessary info about ships.
typedef struct {
  char* name;
  bool orientation; // Horizontal or vertical
  //Size doubles as a "countdown" for the number of times a ship is hit.
  int size;
  int location; // Tracks the upper (for vertical) or leftmost (for
                // horizontal) grid square of the ship's placement.
} Ship;

extern lcd_image_t Images[];
extern Adafruit_ST7735 tft;

Ship* Place_Ships(int8_t* Array, int8_t* ArraytoCheck);

#endif
