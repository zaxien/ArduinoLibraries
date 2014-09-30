/******************************************************************************
* Author:			Rich Gagliano
* Date Created:		08/29/2014
* Date Modified:	09/08/2014
* Program Name:		LED_list.cpp
*
* Overview:
*		Implementation file for the LED_list class.  
*	    See LED_list.h for details.
*
* Updates:
*    (09-08-2014) - Rich Gagliano
*        Added in piezo functionality for victory and failure sounds.
*
******************************************************************************/

#include "LED_list.h"

/******************************************************************************
 * LED_list()
 * Default constructor
 *****************************************************************************/
LED_list :: LED_list() {
	/* Set up generic 8 pin LED_list */
	this->_wincon = 8;
	
	/* Replace the initial sr with the correct shift register object */
	shift_register tmpRegister(11, 8, 12, 8);
	this->_sr = tmpRegister;
	
	/* Initialize the circular doubly linked list of LED nodes */
	_initialize_ll();
}

/******************************************************************************
 * LED_list(int, int)
 * Overloaded constructor
 *****************************************************************************/
LED_list :: LED_list(int size, int wincon) {
	/* Set up generic 8 pin LED_list */
	this->_wincon = wincon;
	
	/* Replace the default sr with a new shift register object */
	shift_register tmpRegister(11, 8, 12, size);
	this->_sr = tmpRegister;
	
	/* Initialize the circular doubly linked list of LED nodes */
	_initialize_ll();
}

/******************************************************************************
 * LED_list(int, int, int, int, int, int, int)
 * Overloaded constructor
 *****************************************************************************/
LED_list :: LED_list(int size, int wincon, int data, int latch, 
					 int clock, int mclear, int piezo) {
	/* Set up generic 8 pin LED_list */
	this->_wincon = wincon;
	
	/* Replace the default sr with a new shift register object */
	shift_register tmpRegister(data, latch, clock, mclear, size);
	this->_sr = tmpRegister;
	
	/* Replace the defaul vs with a new victory sounds object */
	victory_sounds tmpPiezo(piezo);
	this->_vs = tmpPiezo;
	
	/* Initialize the circular doubly linked list of LED nodes */
	_initialize_ll();
}

/*************************************************************************
 * ~LED_list()
 * ~Destructor (left blank)
 ************************************************************************/
LED_list :: ~LED_list()
{
    /* Clean up memory used */
	LED_node *tmp = this->_head;
	
	/* Delete all nodes up to the tail */
	do {
		LED_node *discard = tmp;
		tmp = tmp->next;
		delete discard;
	} while (tmp != this->_tail);
	
	/* Finish up by deleting the tail */
	delete tmp;
}

/*************************************************************************
 * void _initialize_ll(int)
 * Initializes the circular doubly linked list of LED_nodes
 ************************************************************************/
void LED_list :: _initialize_ll()
{
    /* Create all nodes in pattern: 
      8 7 6 5 4 3 2 1 - 16 15 14 13 12 11 10 9 - etc... */

    /* Loop through all shift registers */
    for (int i = 1; i <= (_sr.get_size() / 8); ++i) {
		/* Now create each node for the shift register */
		for (int j = (8 * i)-1; j >= (8 * (i-1)); --j) {	
			_add_node(j);
		}	
   }
}

/*************************************************************************
 * int get_wincon()
 * Returns the current win condition pin
 ************************************************************************/
int LED_list :: get_wincon()
{
    /* Return the win condition pin */
	return this->_wincon;
}

/*************************************************************************
 * int get_size()
 * Returns the size of the circular doubly linked list
 ************************************************************************/
int LED_list :: get_size()
{
    /* Return the win condition pin */
	return this->_sr.get_size();
}

/*************************************************************************
 * void _add_node(int)
 * Adds an LED_node to the circular linked list
 ************************************************************************/
void LED_list :: _add_node(int id)
{
    /* Create the new node */
	LED_node *new_node = new LED_node;
	new_node->id = id;
	
	/* Link the new node to the circular list */
	if (this->_head == NULL) {
		new_node->next = new_node; 		// link the new node to itself
		new_node->prev = new_node; 		// link the new node to itself
		this->_tail = new_node;		   	// setup the tail node
	}
	else {
		new_node->next = this->_head;	// set the new node's next to the head
		this->_head->prev = new_node;	// set the head's prev to new node
	}
	this->_head = new_node;				// the new node is the new head
	this->_tail->next = this->_head;	// point the tail to the head
	this->_head->prev =this-> _tail;	// point the new head to the tail
}

/*************************************************************************
 * void turn_on_next()
 * Shuts off the current LED_node, and turns on the next LED_node
 ************************************************************************/
void LED_list :: turn_on_next()
{
    /* Check if this is the first call to turn on an LED  */
	if (this->_cur == NULL) {
		/* First call, so set the current node as the head */
		this->_cur = this->_head;
	}
	else {
		/* Track the state as off, and set current node to next node */
		this->_cur->state = 0;
		this->_cur = this->_cur->next;
	}
	
	/* Turn on the LED */
	this->_cur->state = 1;
	this->_sr.turn_on(this->_cur->id);
}

/*************************************************************************
 * void turn_on_prev()
 * Shuts off the current LED_node, and turns on the previous LED_node
 ************************************************************************/
void LED_list :: turn_on_prev()
{
    /* Check if this is the first call to turn on an LED  */
	if (this->_cur == NULL) {
		/* First call, so set the current node as the head */
		this->_cur = this->_head;
	}
	else {
		/* Track the state as off, and set current node to next node */
		this->_cur->state = 0;
		this->_cur = this->_cur->prev;
	}
	
	/* Turn on the LED */
	Serial.print("Turning on LED: ");
	Serial.print(_cur->id);
	Serial.print("\n");
	this->_cur->state = 1;
	this->_sr.turn_on(this->_cur->id);
}

/*************************************************************************
 * void end_game()
 * Runs the end game sequence
 ************************************************************************/
void LED_list :: end_game()
{
    /* Check if we have a winner  */
	if (this->_cur->id == this->_wincon) {
		/* We have a winner - play victory sound */	
		this->_vs.play_FFVictory();
		delay(500);
		for (int i = 0; i < 5; ++i) {
			this->_sr.clear_register();
			delay(50);
			this->_sr.turn_on(this->_cur->id);
		}
	}
	else {
		/* We have a loser - play faile buzzer */
		this->_vs.play_failbuzzer();
	}
	delay(2000);
}