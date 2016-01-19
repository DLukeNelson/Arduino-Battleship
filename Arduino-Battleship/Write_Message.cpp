/* This function is used to write game messages to the space at the
 * bottom of the lcd screen.
 */
 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
 
#include "Write_Message.h"
 
void Write_Message(char* message) {
  // Cover with a black rectangle to replace any old messages.
  tft.fillRect(0, 129, 128, 31, 0);
  tft.setTextWrap(true); // Enable text wrapping for longer messages.
  tft.setTextColor(0xFFFF, 0); // white text on black bg.
  tft.setCursor(0, 129);
  tft.println(message); // print a string to the screen.
}
