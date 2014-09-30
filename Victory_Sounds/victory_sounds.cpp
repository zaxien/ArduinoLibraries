/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		09/08/2014
* Date Modified:	09/08/2014
* Program Name:		victory_sounds.cpp
*
* Overview:
*		Implementation file for the victory_sounds class.  
*       See victory_sounds.h for details
*
* Updates:
*
******************************************************************************/

#include "victory_sounds.h"

/******************************************************************************
 * victory_sounds()
 * Default constructor
 *****************************************************************************/
victory_sounds :: victory_sounds() {
	/* Set up the piezo pin */
	this->_pin = 12;
}

/******************************************************************************
 * victory_sounds(int)
 * Overloaded constructor
 *****************************************************************************/
victory_sounds :: victory_sounds(int pin) {
	/* Set up the piezo pin */
	this->_pin = pin;
}

/*************************************************************************
 * ~victory_sounds()
 * ~Destructor (left blank)
 ************************************************************************/
victory_sounds :: ~victory_sounds()
{
    /* Intentionally left blank */
}

/*************************************************************************
 * int get_pin()
 * Returns the current pin of the piezo
 ************************************************************************/
int victory_sounds :: get_pin()
{
    /* Return the piezo's pin */
	return this->_pin;
}

/*************************************************************************
 * void _play_note()
 * Plays a given note
 ************************************************************************/
void victory_sounds :: _play_note(int frequency, int interval, int divisor) {
  tone(this->_pin, frequency);
  delay(interval / divisor);
  noTone(this->_pin); 
}

/*************************************************************************
 * void play_FFVictory()
 * Plays the Final Fantasy victory song
 ************************************************************************/
void victory_sounds :: play_FFVictory() {
	int interval = 500; // 500ms (interval of a quarter note)
	
	_play_note(440, interval, 3);
	_play_note(440, interval, 3);
	_play_note(440, interval, 3);
	_play_note(440, interval, 1);

	_play_note(349, interval, 1);
	_play_note(392, interval, 1);
  
	_play_note(440, interval, 4);
	delay(interval / 4);
	delay(interval / 4);
	_play_note(392, interval, 4);  
	_play_note(440, interval * 2, 1);  
}

/*************************************************************************
 * void play_mariovictory()
 * Plays the Mario Bros victory song
 ************************************************************************/
void victory_sounds :: play_mariovictory() {
	int interval = 500; // 500ms (interval of a quarter note)
	
	_play_note(196, interval, 3);
	_play_note(261, interval, 3);
	_play_note(329, interval, 3);
	_play_note(392, interval, 3);
	_play_note(523, interval, 3);
	_play_note(659, interval, 3);
	_play_note(783, interval, 1);
	_play_note(659, interval, 1);

	
	_play_note(207, interval, 3);
	_play_note(261, interval, 3);
	_play_note(311, interval, 3);
	_play_note(415, interval, 3);
	_play_note(523, interval, 3);
	_play_note(622, interval, 3);
	_play_note(830, interval, 1);
	_play_note(622, interval, 1);
	
	_play_note(233, interval, 3);
	_play_note(293, interval, 3);
	_play_note(349, interval, 3);
	_play_note(466, interval, 3);
	_play_note(587, interval, 3);
	_play_note(698, interval, 3);
	_play_note(932, interval, 1);
	
	_play_note(987, interval, 3);
	_play_note(987, interval, 3);
	_play_note(987, interval, 3);
	
	_play_note(1046, interval * 3, 1);
	
}

/*************************************************************************
 * void play_failbuzzer()
 * Plays the fail buzzer
 ************************************************************************/
void victory_sounds :: play_failbuzzer() {
	_play_note(261, 1000, 1);	
}