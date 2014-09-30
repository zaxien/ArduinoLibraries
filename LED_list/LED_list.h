/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/29/2014
* Date Modified:	09/08/2014
* Program Name:		LED_list.h
*
* Overview:
*		Header file for the LED_list object.  LED_lists
*		contain the following attributes:
*			- turn_on_next
*			- turn_on_prev
*			- end_game
*			- get_wincon
*			- get_size
*			- _initialize_ll
*			- _add_node
*
* Updates:
*    (09-08-2014) - Rich Gagliano
*        Added in piezo functionality for victory and failure sounds.
*
******************************************************************************/

#ifndef ARDUINO_LEDLIST_H
#define ARDUINO_LEDLIST_H

#include "Arduino.h"
#include <shift_register.h>
#include <victory_sounds.h>

/*************************************************************************
 * LED_node (struct)
 * The node of the LED circular doubly linked list
 ************************************************************************/
struct LED_node {
    int id;
	int state;
	LED_node *next;
	LED_node *prev;
};

class LED_list {
	public:
		/* Constructors */
		LED_list();
		LED_list(int size, int wincon);
		LED_list(int size, int wincon, int data, int latch, 
				 int clock, int mclear, int piezo);
		
		/* Destructor */
		~LED_list();
		
		/* Accessor */
		int get_wincon();
		int get_size();
	
		/* Functions */
		void turn_on_next();
		void turn_on_prev();
		void end_game();
		void _initialize_ll();
		void _add_node(int id);
	
	private:
		/* Private member variable */
		int _wincon;
		shift_register _sr;
		victory_sounds _vs;
		LED_node *_head;
		LED_node *_tail;
		LED_node *_cur;
};
#endif