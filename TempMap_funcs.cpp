using namespace std;
#include "TempMap.h"
#include "Map.h"

//Constructor w/ size and starting coordinate
TempMap::TempMap(const int size, const Coord start, const Map& map)
{
	//Setting rectangle size
	m_w = 1;
	m_h = 1;

	//Player & corner pos
	m_p = start;
	m_base = start;

	//Total size
	m_size = size;

	//Creating base array
	m_grid = new Room * [m_size];
	m_explored = new bool * [m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_grid[i] = new Room[m_size];
		m_explored[i] = new bool[m_size];
	}

	//Filling rooms w/ correct rooms
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			m_grid[y][x] = map.get_room(Coord(x,y));
			m_explored[y][x] = false;
		}
	}
	m_explored[m_p.m_y][m_p.m_x] = true;
}

//Copy Constructor, not needed yet, might delete
TempMap::TempMap(const TempMap& obj)
{
	//Deleting data
	for (int i = 0; i < m_h; i++)
	{
		delete[] m_grid[i];
	}
	delete[] m_grid;
	
	//Setting new rectangle size
	m_w = obj.m_w;
	m_h = obj.m_h;
	
	//Player & corner pos

	//Creating new grid
	m_grid = new Room*[m_h];
	for (int i = 0; i < m_h; i++)
	{
		m_grid[i] = new Room[m_w];
		for (int j = 0; j < m_w; j++)
		{
			m_grid[i][j] = obj.m_grid[i][j];
		}
	}
	
}

//Destructor
TempMap::~TempMap()
{
	for (int i = 0; i < m_h; i++)
	{
		delete[] m_grid[i];
	}
	delete[] m_grid;
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
	for (int x = map.m_base.m_x; x < map.m_base.m_x + map.m_w; x++)
	{
		if (map.m_explored[map.m_base.m_y][x])
		{
			if (map.m_grid[map.m_base.m_y][x].get_open(Map::NORTH))
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
	
	for (int y = map.m_base.m_y; y < map.m_base.m_y + map.m_h; y++)
	{

		//SHOWING HORIZONTAL CORRIDORS AND ROOM GRIDS
		prev_seen = false;
		for (int x = map.m_base.m_x; x < map.m_base.m_x + map.m_w; x++)
		{
			if (!prev_seen && map.m_explored[y][x])
			{
				if (map.m_grid[y][x].get_open(Map::WEST))
				{
					if (x == map.m_p.m_x && y == map.m_p.m_y)
					{
						os << "--[H]";
					}
					else
					{
						os << "--[" << map.m_grid[y][x].get_id() << "]";
					}
				}
				else
				{
					if (x == map.m_p.m_x && y == map.m_p.m_y)
					{
						os << "  [H]";
					}
					else
					{
						os << "  [" << map.m_grid[y][x].get_id() << "]";
					}
				}
				if (map.m_grid[y][x].get_open(Map::EAST))
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
				if (prev_seen && map.m_explored[y][x])
				{
					if (map.m_grid[y][x].get_open(Map::EAST))
					{
						if (x == map.m_p.m_x && y == map.m_p.m_y)
						{
							os << "[H]" << "--";
						}
						else
						{
							os << "[" << map.m_grid[y][x].get_id() << "]" << "--";
						}
					}
					else
					{
						if (x == map.m_p.m_x && y == map.m_p.m_y)
						{	
							os << "[H]" << "  ";
						}
						else
						{
							os << "[" << map.m_grid[y][x].get_id() << "]" << "  ";
						}
					}
				}
				if (!map.m_explored[y][x]) 
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
		for (int x = map.m_base.m_x; x < map.m_base.m_x + map.m_w; x++)
		{
			if (map.m_explored[y][x])
			{
				if (map.m_grid[y][x].get_open(Map::SOUTH))
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
				if (y <= map.m_base.m_y + map.m_h)
				{
					if (map.m_explored[y + 1][x])
					{
						if (map.m_grid[y + 1][x].get_open(Map::NORTH))
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
			m_p.m_y--;
			if (m_p.m_y < m_base.m_y)
			{
				m_base.m_y--;
				m_h++;
			}
			break;
		case Map::EAST:
			m_p.m_x++;
			if (m_p.m_x > m_base.m_x + m_w - 1)
			{
				m_w++;
			}
			break;
		case Map::SOUTH:
			m_p.m_y++;
			if (m_p.m_y > m_base.m_y + m_h - 1)
			{
				m_h++;
			}
			break;
		case Map::WEST:
			m_p.m_x--;
			if (m_p.m_x < m_base.m_x)
			{
				m_base.m_x--;
				m_w++;
			}
			break;
	}

	//Exploring new areas after moved
	if(!m_explored[m_p.m_y][m_p.m_x]) m_explored[m_p.m_y][m_p.m_x] = true;

	return;
}

