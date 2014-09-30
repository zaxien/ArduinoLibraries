/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/28/2014
* Date Modified:	08/28/2014
* Program Name:		shift_register.cpp
*
* Overview:
*		Implementation file for the shift_register class.  
*		See shift_register.h for details.
*
* Updates:
*
******************************************************************************/

#include "shift_register.h"

/******************************************************************************
 * shift_register()
 * Default constructor
 *****************************************************************************/
shift_register :: shift_register() {
	/* No arguments, so set up a basic 8 bit register */
	this->_data = 13; /* To be determined! */
	this->_latch = 8; /* To be determined! */
	this->_clock = 7; /* To be determined! */
	this->_mclear = 3; /* To be determined! */
	this->_size = 8;
	
	/* Setup the pins for use */
	initialize_pins();
}

/******************************************************************************
 * shift_register(int, int, int, int, int)
 * Overloaded constructor.  Size is an optional parameter, defaulting to 8.
 *****************************************************************************/
shift_register :: shift_register(int data, int latch, int clock, 
							     int mclear, int size) {
	/* No arguments, so set up a basic 8 bit register */
	this->_data = data; 
	this->_latch = latch;
	this->_clock = clock; 
	this->_mclear = mclear;
	this->_size = size;
	
	/* Setup the pins for use */
	initialize_pins();
}

/*************************************************************************
 * ~shift_register()
 * ~Destructor (left blank)
 ************************************************************************/
shift_register :: ~shift_register()
{
    /* Intentionally left blank */
}

/******************************************************************************
 * void initialize_pins()
 * Initializes the shift register for use
 *****************************************************************************/
void shift_register :: initialize_pins() {
	/* Set the pinout */
	pinMode(this->_data, OUTPUT);
	pinMode(this->_latch, OUTPUT);
	pinMode(this->_clock, OUTPUT);

	/* Clear the register */
	clear_register();	
	
	/* Setup the Clear pin */
	pinMode(this->_mclear, OUTPUT);
	digitalWrite(this->_mclear, HIGH);
}

/******************************************************************************
 * int get_size()
 * Retrieves the shift register size
 *****************************************************************************/
int shift_register :: get_size() {
	/* Return the size of the register */
	return this->_size;
}

/******************************************************************************
 * void turn_on(int)
 * Turns on a specific pin.
 *****************************************************************************/
void shift_register :: turn_on(int pin) {
	/* Shift all of the bits within the register */
	for (int i = 0; i < this->_size; ++i) {
		/* Check if 'i' is the pin to turn on */	
		if (i == pin) {
			shift_out(1);
		}
		else {
			shift_out(0);
		}
	}
	
	/* Commit the register changes: Open the latch! */
	digitalWrite(this->_latch, HIGH);
}

/******************************************************************************
 * void shift_out(int)
 * Shifts out the bit
 *****************************************************************************/
void shift_register :: shift_out(int data) {
	/* Ensure the clock and latch are set to low in order to add the bit */
	digitalWrite(this->_clock, LOW);
	digitalWrite(this->_latch, LOW);
	
	/* Check if data should be set high or low */
	if (data == 1) {
		digitalWrite(this->_data, HIGH);
	}
	else {
		digitalWrite(this->_data, LOW);
	}
	
	/* Enable and disable the clock, to shift the data bit */
	digitalWrite(this->_clock, HIGH);
	digitalWrite(this->_clock, LOW);
}

/******************************************************************************
 * void clear_register(int)
 * Clears the entire shift register.
 *****************************************************************************/
void shift_register :: clear_register() {
	/* Clear all of the bits within the register */
	for (int i = 0; i < this->_size; ++i) {
			shift_out(0);
	}
	
	/* Commit the register changes: Open the latch! */
	digitalWrite(this->_latch, HIGH);
}

/******************************************************************************
 * void all_on(int)
 * Turns on the entire shift register.
 *****************************************************************************/
void shift_register :: all_on() {
	/* Clear all of the bits within the register */
	for (int i = 0; i < this->_size; ++i) {
			shift_out(1);
	}
	
	/* Commit the register changes: Open the latch! */
	digitalWrite(this->_latch, HIGH);
}	