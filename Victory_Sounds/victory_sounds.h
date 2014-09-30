/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		09/08/2014
* Date Modified:	09/08/2014
* Program Name:		victory_sounds.h
*
* Overview:
* Updates:
*
******************************************************************************/

#ifndef ARDUINO_VICTORY_SOUNDS_H
#define ARDUINO_VICTORY_SOUNDS_H

#include "Arduino.h"

class victory_sounds {
	public:
		/* Constructors */
		victory_sounds();
		victory_sounds(int pin);
		
		/* Destructor */
		~victory_sounds();
		
		/* Accessor */
		int get_pin();
	
		/* Functions */
		void play_FFVictory();
		void play_mariovictory();
		void play_failbuzzer();
		
	
	private:
		/* Private member variable */
		int _pin;
		
		/* Private functions */
		void _play_note(int frequency, int interval, int divisor);
};
#endif