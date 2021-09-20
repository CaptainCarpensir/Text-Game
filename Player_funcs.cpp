using namespace std;
#include "Player.h"

//Default Constructor
Player::Player()
{
	m_hp = START_HP;
	m_inv = new Loot[0];
	m_pos = Coord(0,0);
}

Player::Player(const Coord start)
{
	m_hp = START_HP;
	m_inv = new Loot[0];
	m_pos = start;
}

//Destructor
Player::~Player()
{
	delete[] m_inv;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, Player& player)
{
	os << player.m_pos;
	return os;
}

/*
* Member Functions
*/
bool Player::move(const int dir, const Map& map)
{
	bool move = map.get_room(m_pos).get_open(dir);
	if (move)
	{
		switch (dir)
		{
			//North
		case 0:
			m_pos.m_y--;
			break;
			//East
		case 1:
			m_pos.m_x++;
			break;
			//South
		case 2:
			m_pos.m_y++;
			break;
			//West
		case 3:
			m_pos.m_x--;
			break;
			//Player input doesn't have a direction
		default:
			break;
		}
	}
	return move;
}

Coord Player::get_pos() const
{
	return m_pos;
}