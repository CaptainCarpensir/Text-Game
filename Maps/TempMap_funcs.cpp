using namespace std;
#include "TempMap.h"
#include "Map.h"

//Constructor w/ size and starting coordinate
TempMap::TempMap(const int max_size, const Coord start, const Map& map)
{
	//Setting rectangle size
	w = 1;
	h = 1;

	//Player & corner pos
	p = start;
	base = start;

	//Total size
	size = max_size;

	//Creating base array
	grid = new Room * [size];
	explored = new bool * [size];
	for (int i = 0; i < size; i++)
	{
		grid[i] = new Room[size];
		explored[i] = new bool[size];
	}

	//Filling rooms w/ correct rooms
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			grid[y][x] = map.get_room(Coord(x,y));
			explored[y][x] = false;
		}
	}
	explored[p.y][p.x] = true;
}

//Copy Constructor, not needed yet, might delete
TempMap::TempMap(const TempMap& obj)
{
	//Deleting data
	for (int i = 0; i < h; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
	
	//Setting new rectangle size
	w = obj.w;
	h = obj.h;
	
	//Player & corner pos

	//Creating new grid
	grid = new Room*[h];
	for (int i = 0; i < h; i++)
	{
		grid[i] = new Room[w];
		for (int j = 0; j < w; j++)
		{
			grid[i][j] = obj.grid[i][j];
		}
	}
	
}

//Destructor
TempMap::~TempMap()
{
	for (int i = 0; i < h; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, TempMap& map)
{

	/*
	* I'M SORRY THIS FUNCTION IS A FUCKING MESS! IT WAS SUCH A PAIN, AND I JUST GAVE UP AND DID IF STATEMENT ARMAGGEDON
	*/
	
	//Creating variables to show/not show corridors
	bool prev_seen = false;

	//SHOWING TOP ROW CORRIDORS
	for (int x = map.base.x; x < map.base.x + map.w; x++)
	{
		if (map.explored[map.base.y][x])
		{
			if (map.grid[map.base.y][x].get_open(Map::NORTH))
			{
				os << "   | ";
			}
			else
			{
				os << "     ";
			}
		}
		else
		{
			os << "     ";
		}
	}
	os << "\n";
	
	for (int y = map.base.y; y < map.base.y + map.h; y++)
	{

		//SHOWING HORIZONTAL CORRIDORS AND ROOM GRIDS
		prev_seen = false;
		for (int x = map.base.x; x < map.base.x + map.w; x++)
		{
			if (!prev_seen && map.explored[y][x])
			{
				if (map.grid[y][x].get_open(Map::WEST))
				{
					if (x == map.p.x && y == map.p.y)
					{
						os << "--[H]";
					}
					else
					{
						os << "--[" << map.grid[y][x].get_id() << "]";
					}
				}
				else
				{
					if (x == map.p.x && y == map.p.y)
					{
						os << "  [H]";
					}
					else
					{
						os << "  [" << map.grid[y][x].get_id() << "]";
					}
				}
				if (map.grid[y][x].get_open(Map::EAST))
				{
					os << "--";
				}
				else
				{
					os << "  ";
				}
				prev_seen = true;
			}
			else
			{
				if (prev_seen && map.explored[y][x])
				{
					if (map.grid[y][x].get_open(Map::EAST))
					{
						if (x == map.p.x && y == map.p.y)
						{
							os << "[H]" << "--";
						}
						else
						{
							os << "[" << map.grid[y][x].get_id() << "]" << "--";
						}
					}
					else
					{
						if (x == map.p.x && y == map.p.y)
						{	
							os << "[H]" << "  ";
						}
						else
						{
							os << "[" << map.grid[y][x].get_id() << "]" << "  ";
						}
					}
				}
				if (!map.explored[y][x]) 
				{
					if(!prev_seen)
					{
						os << "  ";
					}
					os << "   ";
					prev_seen = false;
				}
			}
		}
		os << "\n";

		//SHOWING CORRIDORS BELOW
		for (int x = map.base.x; x < map.base.x + map.w; x++)
		{
			if (map.explored[y][x])
			{
				if (map.grid[y][x].get_open(Map::SOUTH))
				{
					os << "   | ";
				}
				else
				{
					os << "     ";
				}
			}
			else
			{
				if (y <= map.base.y + map.h)
				{
					if (map.explored[y + 1][x])
					{
						if (map.grid[y + 1][x].get_open(Map::NORTH))
						{
							os << "   | ";
						}
						else
						{
							os << "     ";
						}
					}
					else
					{
						os << "     ";
					}
				}
				else
				{
					os << "     ";
				}
			}
		}
		os << "\n";

	}

	return os;
}

//Moves player within the map, or opens new sections, based on the direction the player moves
void TempMap::move_player(const int dir)
{
	//Moving character in different directions
	switch (dir)
	{
		case Map::NORTH:
			p.y--;
			if (p.y < base.y)
			{
				base.y--;
				h++;
			}
			break;
		case Map::EAST:
			p.x++;
			if (p.x > base.x + w - 1)
			{
				w++;
			}
			break;
		case Map::SOUTH:
			p.y++;
			if (p.y > base.y + h - 1)
			{
				h++;
			}
			break;
		case Map::WEST:
			p.x--;
			if (p.x < base.x)
			{
				base.x--;
				w++;
			}
			break;
	}

	//Exploring new areas after moved
	if(!explored[p.y][p.x]) explored[p.y][p.x] = true;

	return;
}

