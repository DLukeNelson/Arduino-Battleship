/* Draws the screen represented by Array onto the LCD screen. Checks to
 * see if the screen already has some of the needed images (ie. When
 * changing turns, will only redraw the things that are different
 * between the two "oceans".
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "Draw_Screen.h"
#include "lcd_image.h"
#include "Images.h"

void Draw_Screen(int8_t* Arraytodraw, int8_t* Arraytocheck) {

  for( int j=0; j<10; j++ ) { // scans through each row.
    for( int i=0; i<10; i++ ) { // scans through each column.
      int location = (10*j)+i;
      // checks if it would redraw the image that is already there.
      if( Arraytodraw[location] == Arraytocheck[location] ) {
        continue;
      }
      else {
        // Because the two images are different a redraw is required.
        lcd_image_draw(&Images[Arraytodraw[location]%10], &tft, 0, 0,
                        (12*i)+8, (12*j)+8, 12, 12);
      }
    }
  }
}
