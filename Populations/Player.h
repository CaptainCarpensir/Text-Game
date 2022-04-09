#ifndef PLAYER
#define PLAYER
using namespace std;
#include "Loot.h"
#include "../Maps/Map.h"
#include <iostream>

class Player
{
  public:
    //Constants
    const int START_HP = 10;
  private:
    int hp;
    Loot *inv;
    Coord pos;
  public:
    //Default Constructor
    Player();
    
    //Constructor w/ parameter
    Player(const Coord start);

    //Destructor
    ~Player();

    //Insertion Operator Overload
    friend ostream& operator<<(ostream& os, Player& player);

    /*
    * Member Functions
    */

    //Moves the player, returns whether a move was successful or not
    bool move(const int dir, const Map& map);

    //Returns the current position of the player on the scale of the full map
    Coord get_pos() const;
};

#endif