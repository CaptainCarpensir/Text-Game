#ifndef TEMPMAP
#define TEMPMAP
using namespace std;
#include <string>
#include "Room.h"
#include "Map.h"

class TempMap
{
	private:
		//Variables
		Room** grid;
		bool** explored;

		//Size of full map
		int size;

		//Width of shown map
		int w;
		int h;

		//Position of the top left corner of shown map
		Coord base;

		//Player position w/n the map
		Coord p;

	public:
		//Constructor w/ size and starting pos
		TempMap(const int max_size, const Coord start, const Map& map);

		//Copy Constructor
		TempMap(const TempMap& map);

		//Destructor
		~TempMap();

		//Insertion Operator Overload
		friend ostream& operator<<(ostream& os, TempMap& map);

		/*
		* Member Functions
		*/

		//Moves player within the map, or opens new sections, based on the direction the player moves
		void move_player(const int dir);
};

#endif