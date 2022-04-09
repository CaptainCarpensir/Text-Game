using namespace std;
#include "Player.h"

//Default Constructor
Player::Player()
{
	hp = START_HP;
	inv = new Loot[0];
	pos = Coord(0,0);
}

Player::Player(const Coord start)
{
	hp = START_HP;
	inv = new Loot[0];
	pos = start;
}

//Destructor
Player::~Player()
{
	delete[] inv;
}

//Insertion Operator Overload
ostream& operator<<(ostream& os, Player& player)
{
	os << player.pos;
	return os;
}

/*
* Member Functions
*/
bool Player::move(const int dir, const Map& map)
{
	bool move = map.get_room(pos).get_open(dir);
	if (move)
	{
		switch (dir)
		{
			//North
		case 0:
			pos.y--;
			break;
			//East
		case 1:
			pos.x++;
			break;
			//South
		case 2:
			pos.y++;
			break;
			//West
		case 3:
			pos.x--;
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
	return pos;
}