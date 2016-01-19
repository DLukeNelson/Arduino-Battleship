/* Sound effects for hit and miss scenarios.
 * An error sound for if a player tries to place their ship in an
 * illegal position.
 * A victory fanfare for the winning player.
 */

#include <Arduino.h>

#ifndef __SOUND_H__
#define __SOUND_H__

void Sound_Miss();
void Sound_Hit();
void Sound_Error();
void Sound_Victory();

#endif
