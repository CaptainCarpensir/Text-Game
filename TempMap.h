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
		Room** m_grid;
		bool** m_explored;

		//Size of full map
		int m_size;

		//Width of shown map
		int m_w;
		int m_h;

		//Position of the top left corner of shown map
		Coord m_base;

		//Player position w/n the map
		Coord m_p;

	public:
		//Constructor w/ size and starting pos
		TempMap(const int size, const Coord start, const Map& map);

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