/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/28/2014
* Date Modified:	08/28/2014
* Program Name:		button.h
*
* Overview:
*		Header file for the button object.  Buttons
*		contain the following attributes:
*			- is_pressed
*			- current_state
*			- any lighting requirements?	
*
* Updates:
*
******************************************************************************/
#ifndef ARDUINO_BUTTON_H
#define ARDUINO_BUTTON_H

#include "Arduino.h"

class button {
	public:
		/* Constructors */
		button();
		button(int pin);
		
		/* Destructor */
		~button();
		
		/* Accessor */
		int get_pin();
	
		/* Functions */
		bool is_pressed();
		int current_state();
	
	private:
		/* Private member variable */
		int _pin;
};
#endif