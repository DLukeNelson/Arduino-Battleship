/* Sound effects for hit and miss scenarios.
 * An error sound for if a player tries to place their ship in an
 * illegal position.
 * A victory fanfare for the winning player.
 */

#include "SoundFX.h"

void Sound_Miss() {
  // A "flying missile" noise.
  for( int i = 500; i > 250; i-- ) {
    tone(2, 5*i, 10);
    delay(9);
  }
  // A "miss" noise.
  for( int i = 310; i < 350; i++ ) {
    tone(2, 3*i, 7);
    delay(6);
  }
  for( int i = 360; i > 300; i-- ) {
    tone(2, 3*i, 7);
    delay(6);
  }
}

void Sound_Hit() {
  // A "flying missile" noise.
  for( int i = 500; i > 250; i-- ) {
    tone(2, 5*i, 10);
    delay(9);
  }
  // An "explosion" noise.
  for( int i = 11; i < 80; i++ ) {
    tone(2, 3*i, 7);
    delay(6);
  }
}

void Sound_Error() {
  // A short buzz, followed by a pause, and then a longer one.
  tone(2, 80, 300);
  delay(500);
  tone(2, 80, 300);
  delay(300);
}

void Sound_Victory() {
  // t represents a musical tempo; a "unit length" of sorts for each
  // note in the fanfare.
  int t = 50;
  // This is an array that has the frequency of each note to be played.
  // The 0's are there to create a small space between each note.
  int notes[20] = {698, 0, 698, 0, 698, 0, 698, 0, 698, 0,
                    587, 0, 659, 0, 698, 0, 659, 0, 698, 0};
  // This array stores the time (in milliseconds, relative to t) that
  // each note should be played.
  int timing[20] = {24*t, 7, 4*t, 7, 4*t, 7, 4*t, 7, 10*t, 7, 10*t, 7,
                    10*t, 7, 6*t, 7, 3*t, 7, 40*t, 7};
  // This loop plays through each note, associating each frequency with
  // its corresponding time.
  for( int i = 0; i<21; i++ ) {
    tone(2, notes[i], timing[i]);
    delay(timing[i]);
  }
  noTone(2);
}
