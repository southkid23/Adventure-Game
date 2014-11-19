#include "definitions.cpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void toUpper(string& input)
{
	int j = 0; char c;
	while ( input[j] )
	{
		c = input[j];
		c = toupper(c);
		input[j] = c;
		j++;
	}
}

int main()
{
	Room* Shack;Room* VillageCent;Room* Graveyard;Room* Bank;Room* LargeHouse;

	VillageCent = new Room("Village Center"/*,VillageCentLocs*/,"In the center of the village there is a small well. Next to the well is an old man with a long beard and a long staff. He appears to be very wise and very lost. To the south of the center is the small shack from where the player came from. To the East is a fenced graveyard. To the West is a bank. To the North is a large house.");
	Shack = new Room("Shack"/*,ShackLocs*/,"You wake up in a shack. A little girl that tells you how she dragged you from outside. She tells you that there was a recent fire in the village and that she managed to save you. In this room there is an apple, a butter knife, and a journal. The door leads to outside.");
	Bank = new Room("Bank",/*BankLocs,*/"The Bank seems to be under construction due to some unusual damages.In the bank there is a lot of stuff that was burnt from the fire. Weirdly enough, there is a wall that seemed to not be affected by the fire.");
	Graveyard = new Room("Graveyard",/*GraveLocs,*/"You just had a weird vision about the village being on fire.\n The villagers were trembling in fear, shouting and trying to get away from something.\n I wonder what.\n The Graveyard is misty. Some tombs seems to be built recently.");
	LargeHouse = new Room("Mansion",/*MansionLocs,*/"I have no description yet");

	// Setting the room connections
	Shack->setNorth(VillageCent); Shack->setSouth(NULL); Shack->setEast(NULL); Shack->setWest(NULL);
	VillageCent->setNorth(LargeHouse); VillageCent->setSouth(Shack); VillageCent->setEast(Graveyard); VillageCent->setWest(Bank);
	Graveyard->setNorth(NULL); Graveyard->setSouth(NULL); Graveyard->setEast(VillageCent); Graveyard->setWest(NULL);
	Bank->setNorth(NULL); Bank->setSouth(NULL); Bank->setEast(VillageCent); Bank->setWest(NULL);
	LargeHouse->setNorth(NULL); LargeHouse->setSouth(VillageCent); LargeHouse->setEast(NULL); LargeHouse->setWest(NULL);
	
	// placing the player in the Shack
	Player* player = new Player(Shack);

	cout << "Welcome to the ISA Aventure Game." << endl << endl;

	while(true)
	{
		string line;
		string verb = "";
		string noun = "";
		getline(cin, line);
		stringstream ss(line);
		ss >> verb;
		ss >> noun;
		toUpper(verb); toUpper(noun);
		cout << endl;
		if (ss.rdbuf()->in_avail() != 0) // Check if there're any words left in buffer, if there are, then user input was more than 2 words.
		{
			cout << "Please only enter up to 2 words only." << endl;
			noun = ""; // Clears the variables
			verb = "";
		}
		player->doAction(verb, noun);
	}

}



/*
Village Center------------------------------------------------------------------
In the center of the village there is a small well. Next to the well is an old man with a long beard and a long staff. He
appears to be very wise and very lost. To the south of the center is the small shack from where the player came from. To the
East is a fenced graveyard. To the West is a bank. To the North is a large house.

Shack
The player will wake up in a room. In the room is a little girl that tells the player how she dragged him from the outside.
She tells him that there was a recent fire in the village and that she managed to save him. In this room there is an apple,
a butter knife, and a journal. The door leads to outside.

Bank----------------------------------------------------------------------------------------
The Bank seemed to be underconstruction due to some unusual damages. You can't go into the bank because the people constructing
the bank will not let you in. Once you give them the gold you found in the Graveyard, then they will allow you to enter. In the bank
there is a lot of stuff that was burnt from the fire. Weirdly enough, there is a wall that seemed to not be affected by the fire at all.
You do something to activate the wall. */
