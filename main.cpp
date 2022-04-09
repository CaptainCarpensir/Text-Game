using namespace std;
#include "Maps/Map.h"
#include "Populations/Player.h"
#include "Maps/TempMap.h"
#include <iostream>
#include <random>

//Separates string of command into a dynamic array of commands separated by whitspaces
//returns pointer to this array
string* parse_command(string command);

//Gets the direction needed to move in based off of the second line of the ptr command
int get_dir(string command);

int main()
{
	//Seeding random
	//Temporary
	srand(0);

	//Constants & Enums
	const int NUM_COMMANDS = 4;
	const string commands[NUM_COMMANDS] = 
	{
		"move", "exit", "empty", "help"
	};

	enum Command
	{
		move, exit, empty, help
	};

	//Variables
	Map board;
	Player player(board.get_start());
	TempMap map(board.GRID_SIZE, player.get_pos(), board);
	string input;
	bool playing = true;
	int command;

	//Just for me to see rn
	cout << board << endl;

	//Game loop
	while (playing)
	{
		cout << map << endl;
		//Getting and parsing input
		cout << "What will you do: ";
		getline(cin, input);
		string* ptr = parse_command(input);

		//Reading first command input
		for (int i = 0; i < NUM_COMMANDS; i++)
		{
			if (ptr[0] == commands[i])
			{
				command = i;
				i = NUM_COMMANDS;
			}
			else
			{
				command = -1;
			}
		}

		//Clear terminal outputs and reset cursor
		cout << "\033[H" << endl;
		cout << "\033[2J" << endl;

		//Enacting upon commands
		switch (command)
		{
			case move:
				short dir;
				if (player.move(dir = get_dir(ptr[1]), board))
				{
					map.move_player(dir);
				}
				break;
			case exit:
				playing = false;
				break;
			case empty:
				cout << "You need to actually enter a command lmao" << endl;
				break;
			case help:
				/*
				*  
				*/
				cout << "NOT IMPLEMENTED YET" << endl;
				break;
			default:
				cout << "Sorry bumhead, that command doesn't exist" << endl;
				break;
		}

		//Check if win condition met (Player is in an exit)
		if (board.get_room(player.get_pos()).get_id() == 'E')
		{
			cout << "Congratulations! You made it to an exit!" << endl;
			playing = false;
		}
		
		//Cleaning created command
		delete[] ptr;
	}

	cout << "\tThank you for playing!" << endl;

	return 0;
}

/*
* Helper Functions
*/
string* parse_command(string command)
{
	//Variables
	string temp = command;
	int i;
	int num_words = 1;
	string* ptr;
	
	if (command != "")
	{
		//Getting the size of the array
		while (temp.find(" ") != string::npos)
		{
			i = temp.find(" ");
			temp = temp.substr(i + 1);
			num_words++;
		}

		//Creating array and separating into individual words
		ptr = new string[num_words];

		for (int j = 0; j < num_words; j++)
		{
			i = command.find(" ");
			ptr[j] = command.substr(0, i);
			command = command.substr(i + 1);
		}
	}
	else
	{
		ptr = new string[1];
		ptr[0] = "empty";
	}
	
	return ptr;
}

int get_dir(string command)
{
	//Constants & Enum
	const int NUM_DIR = 4;
	const string dir_names[NUM_DIR] =
	{
		"north", "east", "south", "west"
	};

	enum Directions
	{
		north, east, south, west
	};

	//Variables
	int dir;

	//Check if equal
	for (int i = 0; i < NUM_DIR; i++)
	{
		if (command == dir_names[i])
		{
			dir = i;
			i = NUM_DIR;
		}
		else
		{
			dir = -1;
		}
	}

	return dir;
}
