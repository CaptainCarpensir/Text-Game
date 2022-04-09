using namespace std;
#include "Map.h"
#include <iostream>
#include <random>

//Default Constructor
Map::Map()
{
	//Variables
	int exits = NUM_EXITS;
	int start = STARTING_ROOMS;
	int basic_rooms = (GRID_SIZE * GRID_SIZE) - exits - start;
	start_pos = Coord();

	//Creating grid
	grid = new Room*[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i] = new Room[GRID_SIZE];
	}

	//Assigning rooms
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			//Randomly selects a room to be an exit, start, or default
			int i = (rand() % (basic_rooms + exits + start)) + 1;
			bool curr_exit = (i > basic_rooms) && (i <= basic_rooms + exits);
			bool curr_start = (i > basic_rooms + exits);
			
			if(curr_exit)
			{
				grid[y][x] = Room(EXIT);
				exits--;
			}
			if(curr_start)
			{
				start--;
				grid[y][x] = Room(START);
				start_pos.x = x;
				start_pos.y = y;
			}
			if (!curr_exit && !curr_start)
			{
				basic_rooms--;
				grid[y][x] = Room(select_room());
			}

			//Randomly generate room movement
			if (!curr_exit && !curr_start)
			{
				//Basic rooms generate hallways randomly
				for (int d = 0; d < 4; d++)
				{
					bool if_open = (rand() % 100) < (OPEN_CHANCE * 100);
					grid[y][x].set_open(d,if_open);
				}
			}
			else
			{
				for (int d = 0; d < 4; d++)
				{
					grid[y][x].set_open(d,true);
				}
			}
		}
	}

	//Rooms are assigned with id's and corresponding open hallways, 
	//now need to make it so that both hallways need to be open for a hallway to exist there
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			for (int d = 0; d < 4; d++)
			{
				switch (d)
				{
					//Check north adjacency
				case 0:
					if (y == 0)
					{
						grid[y][x].set_open(d, false);
						break;
					}
					if (!grid[y - 1][x].get_open(SOUTH)) grid[y][x].set_open(NORTH, false);
					break;
					//Check east adjacency
				case 1:
					if (x ==  GRID_SIZE - 1)
					{
						grid[y][x].set_open(d, false);
						break;
					}
					if (!grid[y][x + 1].get_open(WEST)) grid[y][x].set_open(EAST, false);
					break;
					//Check south adjacency
				case 2:
					if (y == GRID_SIZE - 1)
					{
						grid[y][x].set_open(d, false);
						break;
					}
					if (!grid[y + 1][x].get_open(NORTH)) grid[y][x].set_open(SOUTH, false);
					break;
					//Check west adjacency
				case 3:
					if (x == 0)
					{
						grid[y][x].set_open(d, false);
						break;
					}
					if (!grid[y][x - 1].get_open(EAST)) grid[y][x].set_open(WEST, false);
					break;
				}
			}
		}
	}
}

//Destructor
Map::~Map()
{
	//Deleting grid rows
	for (int i = 0; i < GRID_SIZE; i++)
	{
		delete[] grid[i];
	}
	//Deleting final grid
	delete[] grid;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, Map& map)
{
	for (int y = 0; y < map.GRID_SIZE; y++)
	{
		//Display rows
		for (int x = 0; x < map.GRID_SIZE; x++)
		{
			bool is_open = false;
			for (int d = 0; d < Map::NUM_DIR; d++)
			{
				if(map.grid[y][x].get_open(d)) is_open = true;
			}
			if (!is_open)
			{
				os << "   ";
			}
			else
			{
				os << "[" << map.grid[y][x] << "]";
			}
			if(map.grid[y][x].get_open(1)) 
			{
				 os << "--";
			}
			else
			{
				os << "  ";
			}
		}
		os << "\n";
		//Display adjacency to bottom
		for (int x = 0; x < map.GRID_SIZE; x++)
		{
			if (map.grid[y][x].get_open(2))
			{
				if (x == 0)
				{
					cout << " |  ";
				}
				else
				{
					cout << "  |  ";
				}
			}
			else
			{
				if (x == 0)
				{
					cout << "    ";
				}
				else
				{
					cout << "     ";
				}
			}
		}
		os << "\n";
	}
	return os;
}

//Get function for the starting position
Coord Map::get_start() const
{
	return start_pos;
}

//Get function for a room at a specified value
Room& Map::get_room(const Coord coor) const
{
	return grid[coor.y][coor.x];
}

//Returns a random room type with weighted chance
char Map::select_room() const
{
	//Variables
	int total_weight = 0;
	int selector;
	int index = 0;
	int curr_sum = 0;
	char output;

	//Getting total weighted value of rooms
	for (int i = 0; i < NUM_ROOM_TYPES; i++)
	{
		total_weight += room_weight[i];
	}

	//Getting random integer value to assign room type
	selector = rand() % total_weight;

	//Getting integer value of index to correspond to weighted room chance
	for (int i = 0; i < total_weight; i++)
	{
		if (i >= room_weight[index] + curr_sum && room_weight[index] + curr_sum <= selector)
		{
			curr_sum += room_weight[index];
			index++;
		}
	}

	switch (index)
	{
		case barracks:
			output = BARRACKS;
			break;
		default:
			output = BASIC;
			break;
	}

	return output;
}