/* Made to ease the burden on those viewing the code. The main function
 * defines:
 * lcd_image_t Images[10] = {
 *  { "Water.lcd",  12, 12 },
 *  { "Miss.lcd",   12, 12 },
 *  { "Hit.lcd",    12, 12 },
 *  { "Shipm.lcd",  12, 12 },
 *  { "Shipl.lcd",  12, 12 },
 *  { "Shipr.lcd",  12, 12 },
 *  { "Shipt.lcd",  12, 12 },
 *  { "Shipb.lcd",  12, 12 },
 *  { "Border.lcd", 128, 128 },
 *  { "title.lcd",  128, 160 }
 * };
 * This header file simply defines a number to each image name so that
 * other functions can say lcd_image_draw(&Images[water], .....).
 * This makes it easier to follow what is being drawn where.
 */
 
 #include "lcd_image.h"
 
 #ifndef __IMAGES__H
 #define __IMAGES__H
 
 #define water    0
 #define miss     1
 #define hit      2
 #define shipm    3
 #define shipl    4
 #define shipr    5
 #define shipt    6
 #define shipb    7
 #define border   8
 #define title    9

 #endif
