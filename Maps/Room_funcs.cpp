using namespace std;
#include "Room.h"
#include <iostream>
#include "Map.h"

//Default Constructor
Room::Room()
{
	id = Map::BASIC;
	for (int i = 0; i < NUM_DIR; i++)
	{
		dir_open[i] = true;
	}
}

//Constructor w/ room type specified
Room::Room(char room_type)
{
	id = room_type;
	for (int i = 0; i < NUM_DIR; i++)
	{
		dir_open[i] = true;
	}
}

//Constructor w/ room type and directions specified
Room::Room(char room_type, int dir_open[NUM_DIR])
{
	id = room_type;
	for (int i = 0; i < NUM_DIR; i++)
	{
		dir_open[i] = dir_open[i];
	}
}

//Copy Assignment Operator Overload
void Room::operator=(const Room& room)
{
	id = room.id;
	for (int i = 0; i < NUM_DIR; i++)
	{
		dir_open[i] = room.dir_open[i];
	}
	return;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, Room& room)
{
	os << room.id;
	return os;
}

/*
* Public Member Functions
*/

void Room::set_open(const int dir, const bool open)
{
	dir_open[dir] = open;
	return;
}

bool Room::get_open(const int dir) const
{
	return dir_open[dir];
}

char Room::get_id() const
{
	return id;
}