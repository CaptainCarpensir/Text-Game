#ifndef ROOM
#define ROOM
using namespace std;
#include "Enemy.h"
#include "Loot.h"
#include <string>

class Room
{
	private:
		//Constant
		const static int NUM_DIR = 4;

		//Variables
		char m_id;

		/*
		* Direction open means that the bool dictates whether the adjacent room can be traveled to in this form
		*     N(0)        N   E   S   W
		*  W(3) - E(1)   [0] [1] [2] [3]
		*     S(2)       T/F T/F T/F T/F
		*/
		bool m_dir_open[NUM_DIR];
	public:

		/*
		* CONSTRUCTORS & OPERATOR OVERLOADS
		*/

		//Default Constructor
		Room();

		//Constructor w/ room type specified
		Room(char room_type);

		//Constructor w/ room type and directions specified
		Room(char room_type, int dir_open[NUM_DIR]);

		//Copy Assignment Operator Overload
		void operator=(const Room& room);

		//Insertion Operator Overload
		friend ostream& operator<<(ostream& os, Room& room);

		/*
		* GETTERS & SETTERS
		*/

		//Gets room id
		char get_id() const;

		/*
		* CLASS FUNCTIONS
		*/

		//Sets whether the direction is open
		//Pre: integer direction, and bool, in order to set a specific direction to open/closed
		//Post: no return
		void set_open(const int dir, const bool open);

		//Gets whether the direction is open
		//Pre: integer direction based off of those found in Map.h
		//Post: returns a bool on whether the direction is open 
		bool get_open(const int dir) const;

		//Initializes room as player enters. Should control random spawns etc.
		//Pre: requires the player level in order to set rough difficulty guidelines of the room
		//Post: no return, makes the room interactable
		void init_room();
};


#endif