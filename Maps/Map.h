#ifndef MAP
#define MAP
using namespace std;
#include "Room.h"
#include <iostream>

struct Coord
{
	int x;
	int y;

	//Default constructor sets coordinates to 0
	Coord()
	{
		x = 0;
		y = 0;
	}

	//Set coordinates to parameters
	Coord(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}

	//Insertion operator for coordinates
	friend ostream& operator<<(ostream& os, Coord& coor)
	{
		os << "(" << coor.x << "," << coor.y << ")";
		return os;
	}
};

class Map
{
	public:
		//Room Types and enum
		const static int NUM_ROOM_TYPES = 10;
		const string room_types[NUM_ROOM_TYPES] =
		{
				"Barracks", "Kitchen", "Armory", "Secret Stash", "Garden", "Observatory", "Cryo Chamber", "Engine Room", "Fishery", "Long Hallway"
		};

		enum RoomTypes
		{
			barracks, kitchen, armory, stash, garden, observatory, cryo_chamber, engine, fishery, long_hallway
		};

		const int room_weight[NUM_ROOM_TYPES] =
		{
			4, 5, 4, 1, 6, 2, 2, 1, 4, 8
		};

		//Public Constants
		const static char EXIT = 'E';
		const static char START = 'S';
		const static char BASIC = ' ';
		const static char BARRACKS = 'B';

		//Direction constants
		const static short NUM_DIR = 4;
		const static int NORTH = 0;
		const static int EAST = 1;
		const static int SOUTH = 2;
		const static int WEST = 3;
		
		//One side length of square map grid size
		const int GRID_SIZE = 20;

		//Number of exits and starting rooms, starting rooms should always stay at 1
		const int NUM_EXITS = 4;
		const int STARTING_ROOMS = 1;

		//Dictates the likelihood of hallways being generated
		const double OPEN_CHANCE = 0.85;
	private:
		//Variables
		Room **grid;
		Coord start_pos;
	public:
		/*
		* NO REQUIRED COPY CONSTRUCTOR OR COPY ASSIGNMENT AS ONLY 1 MAP WILL BE CREATED PER PROGRAM RUN
		*/

		//Default constructor
		Map();

		//Desctructor
		~Map();

		//Insertion Operator Overload
		friend ostream& operator<<(ostream& os, Map& map);

		//Gets starting position
		Coord get_start() const;

		//Passes in the room in the grid array
		Room& get_room(const Coord coor) const;
	private:
		//Private Member Functions
		char select_room() const;
};
#endif