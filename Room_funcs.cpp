using namespace std;
#include "Room.h"
#include <iostream>
#include "Map.h"

//Default Constructor
Room::Room()
{
	m_id = Map::BASIC;
	for (int i = 0; i < NUM_DIR; i++)
	{
		m_dir_open[i] = true;
	}
}

//Constructor w/ room type specified
Room::Room(char room_type)
{
	m_id = room_type;
	for (int i = 0; i < NUM_DIR; i++)
	{
		m_dir_open[i] = true;
	}
}

//Constructor w/ room type and directions specified
Room::Room(char room_type, int dir_open[NUM_DIR])
{
	m_id = room_type;
	for (int i = 0; i < NUM_DIR; i++)
	{
		m_dir_open[i] = dir_open[i];
	}
}

//Copy Assignment Operator Overload
void Room::operator=(const Room& room)
{
	m_id = room.m_id;
	for (int i = 0; i < NUM_DIR; i++)
	{
		m_dir_open[i] = room.m_dir_open[i];
	}
	return;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, Room& room)
{
	os << room.m_id;
	return os;
}

/*
* Public Member Functions
*/

void Room::set_open(const int dir, const bool open)
{
	m_dir_open[dir] = open;
	return;
}

bool Room::get_open(const int dir) const
{
	return m_dir_open[dir];
}

char Room::get_id() const
{
	return m_id;
}