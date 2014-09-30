/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/28/2014
* Date Modified:	08/28/2014
* Program Name:		button.cpp
*
* Overview:
*		Implementation file for the button class.  See button.h for details.
*
* Updates:
*
******************************************************************************/

#include "button.h"

/******************************************************************************
 * button()
 * Default constructor
 *****************************************************************************/
button :: button() {
	/* No pin supplied, so set to invalid option to check for */
	this->_pin = -1;
}

/******************************************************************************
 * button(int)
 * Overloaded constructor
 *****************************************************************************/
button :: button(int pin) {
	/* Set up the pin for input */
	this->_pin = pin;
	pinMode(this->_pin, INPUT);
}

/*************************************************************************
 * ~button()
 * ~Destructor (left blank)
 ************************************************************************/
button :: ~button()
{
    /* Intentionally left blank */
}

/******************************************************************************
 * int get_pin()
 * Retrieves the button's pin
 *****************************************************************************/
int button :: get_pin() {
	/* Return the button's pin */
	return this->_pin;
}

/******************************************************************************
 * bool is_pressed()
 * Checks to see if the button is pressed.  Returns true if pressed.
 *****************************************************************************/
bool button :: is_pressed() {
	/* Check if we have a valid button */
	if (this->_pin != -1) {
		/* Check if the button is being pressed */
		int button_state = digitalRead(this->_pin);
		if (button_state == HIGH) {
			/* The button is pressed */
			return true;
		}
		
		/* The button is not pressed */
		return false;
	}
	
	/* Invalid pin setup, default to return false */
	return false;
}

/******************************************************************************
 * bool current_state()
 * Returns the current state of the button.
 *****************************************************************************/
int button :: current_state() {
	/* Check if we have a valid button */
	if (this->_pin != -1) {
		/* Return the button's current state */
		return digitalRead(this->_pin);
	}
	
	/* Invalid pin setup, return the negative value */
	return -1;
}