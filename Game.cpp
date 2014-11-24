#include "definitions.cpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int main()
{
	Room* Shack;Room* VillageCent;Room* Graveyard;Room* Bank;Room* LargeHouse;
	
	List* vItems = new List(); List* sItems = new List(); List* bItems = new List(); List* gItems = new List(); List* lItems = new List();
	 

	//Setting Obstacles
	Obstacle* guard = new Obstacle("GUARD"); 
	guard->prevent("WEST"); 
	guard->setpInfo("A Guard is preventing you from entering the Bank.");
	guard->setOccur("The Guard smiles. He then lies down and takes a nap.");
	
	Obstacle* door = new Obstacle("DOOR"); 
	door->prevent("NORTH"); door->setpInfo("Door is locked.");
	door->setOccur("Door gets broken down.");

	Obstacle* window = new Obstacle("WINDOW");
	window->prevent("NORTH");
	window->setpInfo("There are several planks of wood nailed to the door. The Window next to the door is a little cracked."); 
	window->setOccur("The Window breaks.");
	
	Obstacle* gate = new Obstacle("GATE");
	gate->prevent("EAST");
	gate->setpInfo("The gate to the graveyard is firmly locked."); 
	gate->setOccur("The gate makes a creaking sound as it opens.");

	//Items
	Item* crowbar = new Item("CROWBAR", "A rusty, old crowbar. Seems sturdy.", true); 
	crowbar->setTarget(door);
	
	Item* key = new Item("KEY","I wonder what this unlocks...",true);
	key->setTarget(gate);

	Item* map = new Item("MAP", "Looks overused.", true);

	Item* chest = new Item("CHEST", "Looks fancy", true);
	
	Item* ckey = new Item("CHESTKEY", "Looks like a key for chest.", true);
	ckey->setiTarget(chest);ckey->setProduct(map);

	Item* apple = new Item("APPLE", "A shiny juicy looking apple.", true);

	
	sItems->add(crowbar);
	sItems->add(apple);
	sItems->add(ckey);
	sItems->add(chest);


	//Defining Rooms
	Shack = new Room("SHACK", sItems,"YOU ARE IN AN OLD AND DUSTY SHACK. EVERYTHING SEEMS TO BE WORN OUT FROM AGE OR\nOVERUSED. THE DOOR TO THE NORTH LEADS TO OUTSIDE.");
	VillageCent = new Room("VILLAGE CENTER", vItems, "YOU ARE IN THE CENTER OF THE VILLAGE THERE IS A SMALL WELL. NEXT TO THE WELL IS AN OLD MAN WITH A LONG BEARD AND A LONG STAFF. HE APPEARS TO BE VERY WISE, YET VERY CONFUSED. YOU TRY TALKING TO HIM BUT ALL HE DOES IS MUMBLE. TO THE SOUTH OF THE CENTER IS THE SHACK. TO THE EAST IS A FENCED GRAVEYARD. TO THE WEST IS A BANK. TO THE NORTH IS A MANSION.");
	Bank = new Room("BANK", bItems, "THE BANK SEEMS TO BE UNDER CONSTRUCTION DUE TO SOME UNUSUAL DAMAGES.IN THE BANK THERE IS A LOT OF STUFF THAT WAS BURNT FROM THE FIRE. WEIRDLY ENOUGH, THERE IS A WALL THAT SEEMED TO NOT BE AFFECTED BY THE FIRE.");
	Graveyard = new Room("GRAVEYARD", gItems, "YOU JUST HAD A WEIRD VISION ABOUT THE VILLAGE BEING ON FIRE.\nTHE VILLAGERS WERE TREMBLING IN FEAR, SHOUTING AND TRYING TO GET AWAY FROM SOMETHING.\nI WONDER WHAT...\nTHE GRAVEYARD IS MISTY. SOME TOMBS SEEMS TO BE BUILT RECENTLY.");
	LargeHouse = new Room("MANSION", lItems, "THE HOUSE LOOKS REALLY FANCY. WOULD LOOK BETTER IF NOT FOR THE DUST THAT HAD COLLECTED OVER THE MONTHS. THERE'S A BEAUTIFUL BACKYARD AT THE BACK OF THE HOUSE. THE LIVING ROOM SEEMS TO HAVE A WEIRD SYMBOL.ONE OF THE WINDOWS SEEMS TO BE UNLOCKED.");


	Shack->setNorth(VillageCent);
	Shack->setSouth(NULL);
	Shack->setEast(NULL); 
	Shack->setWest(NULL);
	Shack->setObstacleN(door);

	VillageCent->setNorth(LargeHouse);
	VillageCent->setSouth(Shack);
	VillageCent->setEast(Graveyard);
	VillageCent->setWest(Bank);
	VillageCent->setObstacleN(window); 
	VillageCent->setObstacleW(guard); 
	VillageCent->setObstacleE(gate);
	VillageCent->setObstacleS(NULL);
	
	Graveyard->setNorth(NULL);
	Graveyard->setSouth(NULL); 
	Graveyard->setEast(NULL); 
	Graveyard->setWest(VillageCent);
	
	Bank->setNorth(NULL); 
	Bank->setSouth(NULL); 
	Bank->setEast(VillageCent); 
	Bank->setWest(NULL);
	
	LargeHouse->setNorth(NULL); 
	LargeHouse->setSouth(VillageCent);
	LargeHouse->setEast(NULL); 
	LargeHouse->setWest(NULL);

	
	// placing NPCs
	NPC* lilgirl = new NPC(Shack, "LITTLEGIRL", "KEY");
	lilgirl->setFT("Hello mister. It looks you are finally awake. Sorry if you are hurt but I had to drag you inside this Shack. I've been living for a couple days in this abandoned place. There was a fire last night and I found you with your clothes half-burnt. I'm pretty hungry.");
	lilgirl->setAT("I'm hungry.");
	Shack->setNPC(lilgirl);
	apple->setnTarget(lilgirl);
	lilgirl->getInventory()->add(key);
	lilgirl->setOccur("Thank you for the apple! Sorry, I don't have anything to give in return... Oh wait! I found this useless key the other day!\n\nShe gives you a key.\n\n");
	
	// placing the player in the Shack
	Player* player = new Player(Shack);

	cout << "WELCOME TO THE ISA AVENTURE GAME. IF YOU EVER NEED ANY HELP, JUST TYPE \"HELP\"" << endl;
	cout << "(PLAYER INPUT IS NOT CASE SENSITIVE)" << endl << endl << endl << endl << endl;

	cout << "YOU WAKE UP IN A SHACK. A LITTLE GIRL THAT TELLS YOU HOW SHE DRAGGED YOU FROM\nOUTSIDE. SHE TELLS YOU THAT THERE WAS A RECENT FIRE IN THE VILLAGE AND THAT SHE MANAGED TO SAVE YOU.\n\n";
	Shack->enter();
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
		
		if(verb == "" && noun == "") // necessary condition for USE
			;
		else if (ss.rdbuf()->in_avail() != 0) // Check if there're any words left in buffer, if there are, then user input was more than 2 words.
		{
			cout << "Please only enter up to 2 words only." << endl;
			noun = ""; // Clears the variables
			verb = "";
		}
		else
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
