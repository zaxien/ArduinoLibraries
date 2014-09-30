/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/28/2014
* Date Modified:	08/28/2014
* Program Name:		shift_register.h
*
* Overview:
*		Header file for the the shift_register object.  Shift
*		registers can perform the following functions:
*			- clear_register
*			- shift_out
*			- turn_on(pin)
*			- all_on
*			
*		The implementation also contains specific functionality for the 
*		start, victory, and loss sequences of the application.
*
* Updates:
*
******************************************************************************/

#ifndef ARDUINO_SHIFTREGISTER_H
#define ARDUINO_SHIFTREGISTER_H

#include "Arduino.h"

class shift_register {
	public:
		/* Constructors */
		shift_register();
		shift_register(int data, int latch, int clock, 
					   int mclear, int size = 8);
		
		/* Destructor */
		~shift_register();
		
		/* Accessors */
		int get_size();
		
		/* Functions */
		void initialize_pins();
		void turn_on(int pin);
		void shift_out(int data);
		void clear_register();
		void all_on();
	
	private:
		/* Private member variables */
		int _data, _latch, _clock, _mclear, _size;
};

#endif