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
	

	/*Obstacle* door = new Obstacle("DOOR"); 
	door->prevent("NORTH"); door->setpInfo("DOOR IS LOCKED.");
	door->setOccur("DOOR GETS BROKEN DOWN.");*/


	Obstacle* window = new Obstacle("WINDOW");
	window->prevent("NORTH");
	window->setpInfo("THERE ARE SEVERAL PLANKS OF WOOD NAILED TO THE DOOR. THE WINDOW NEXT TO THE DOOR IS A LITTLE CRACKED."); 
	window->setOccur("THE WINDOW BREAKS.");
	
	Obstacle* gate = new Obstacle("GATE");
	gate->prevent("EAST");
	gate->setpInfo("THE GATE TO THE GRAVEYARD IS FIRMLY LOCKED."); 
	gate->setOccur("THE GATE MAKES A CREAKING SOUND AS IT OPENS.");

	Obstacle* tomb = new Obstacle("TOMB");
	tomb->prevent("SOUTH");
	tomb->setpInfo("THERE IS AN OLD AND ANCIENT TOMB. THE TOP OF THE TOMB SEEMS TO BE SHIFTED A LITLE. YOU TRY LIFTING THE TOP BUT IT IS TOO HEAVY.");

	//Items
	Item* crowbar = new Item("CROWBAR", "A RUSTY, OLD CROWBAR. SEEMS STURDY.", true); 
	crowbar->setTarget(gate);
	
	Item* bananaskin = new Item("BANANA_SKIN", "USELESS...", true);

	Item* pStone = new Item("PHILOSOPHER'S_STONE", "YOU FEEL A STRANGE POWERFUL AURA.", true);
	pStone->setiTarget(bananaskin); pStone->setProduct(crowbar);

	Item* key = new Item("KEY","I WONDER WHAT THIS UNLOCKS...",true);
	key->setTarget(gate);

	Item* fbook = new Item("FOREIGN_BOOK", "SEEMS LIKE IT IS A BOOK FROM ANOTHER COUNTRY.", true);

	Item* lchest = new Item("LIGHT_CHEST", "WONDER WHAT'S INSIDE...", true);
	
	Item* ckey = new Item("CHEST_KEY", "LOOKS LIKE A KEY TO A CHEST...", true);
	ckey->setiTarget(lchest);ckey->setProduct(fbook);

	Item* apple = new Item("APPLE", "A SHINY JUICY APPLE.", true);

	
	sItems->add(apple);
	sItems->add(ckey);
	sItems->add(bananaskin);
	sItems->add(lchest);


	//Defining Rooms
	Shack = new Room("SHACK", sItems,"YOU ARE IN AN OLD AND DUSTY SHACK. THERE IS A LITTLE GIRL STRANGELY LOOKING AT YOU. EVERYTHING SEEMS TO BE WORN OUT FROM AGE OR\nOVERUSED. THE DOOR TO THE NORTH LEADS TO OUTSIDE.");
	VillageCent = new Room("VILLAGE CENTER", vItems, "YOU ARE IN THE CENTER OF THE VILLAGE THERE IS A SMALL WELL. NEXT TO THE WELL IS AN OLD MAN WITH A LONG BEARD AND A LONG STAFF. HE APPEARS TO BE VERY WISE, YET VERY CONFUSED. YOU TRY TALKING TO HIM BUT ALL HE DOES IS MUMBLE. TO THE SOUTH OF THE CENTER IS THE SHACK. TO THE EAST IS A FENCED GRAVEYARD. TO THE WEST IS A BANK. TO THE NORTH IS A MANSION.");
	Bank = new Room("BANK", bItems, "THE BANK SEEMS TO BE UNDER CONSTRUCTION DUE TO SOME UNUSUAL DAMAGES.IN THE BANK THERE IS A LOT OF STUFF THAT WAS BURNT FROM THE FIRE. WEIRDLY ENOUGH, THERE IS A WALL THAT SEEMED TO NOT BE AFFECTED BY THE FIRE.");
	Graveyard = new Room("GRAVEYARD", gItems, "YOU JUST HAD A WEIRD VISION ABOUT THE VILLAGE BEING ON FIRE.\nTHE VILLAGERS WERE TREMBLING IN FEAR, SHOUTING AND TRYING TO GET AWAY FROM SOMETHING.\nI WONDER WHAT...\nTHE GRAVEYARD IS MISTY. SOME TOMBS SEEMS TO BE BUILT RECENTLY.");
	LargeHouse = new Room("MANSION", lItems, "THE HOUSE LOOKS REALLY FANCY. WOULD LOOK BETTER IF NOT FOR THE DUST THAT HAD COLLECTED OVER THE MONTHS. THERE'S A BEAUTIFUL BACKYARD AT THE BACK OF THE HOUSE. THE LIVING ROOM SEEMS TO HAVE A WEIRD SYMBOL.ONE OF THE WINDOWS SEEMS TO BE UNLOCKED.");


	Shack->setNorth(VillageCent);
	Shack->setSouth(NULL);
	Shack->setEast(NULL); 
	Shack->setWest(NULL);
	//Shack->setObstacleN(door);

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
	NPC* lilgirl = new NPC(Shack, "LITTLE_GIRL", "KEY");
	lilgirl->setFT("'HELLO MISTER. IT LOOKS YOU ARE FINALLY AWAKE. SORRY IF YOU ARE HURT BUT I HAD TO DRAG YOU INSIDE THIS SHACK. I'VE BEEN LIVING FOR A COUPLE DAYS IN THIS ABANDONED PLACE. THERE WAS A FIRE LAST NIGHT AND I FOUND YOU WITH YOUR CLOTHES HALF-BURNT. PULLING YOU SURE MADE ME HUNGRY.'");
	lilgirl->setAT("'I'M HUNGRY'");
	Shack->setNPC(lilgirl);
	apple->setnTarget(lilgirl);
	lilgirl->getInventory()->add(key);
	lilgirl->setOccur("'THANK YOU FOR THE APPLE! SORRY, I DON'T HAVE ANYTHING TO GIVE IN RETURN... OH WAIT! I FOUND THIS USELESS KEY THE OTHER DAY!\n\nSHE GIVES YOU A KEY.\n\n");

	NPC* oldman = new NPC(VillageCent, "OLD_MAN", "PHILOSOPHER'S_STONE");
	oldman->setFT("'WHY, HELLO THERE YOUNG LAD. I'M TRAVELING FAR AND WIDE IN SEARCH OF KNOWLDEGE AND EXPERIENCE. I WONDER WHAT KIND OF INTERESTING THINGS I CAN FIND IN THIS VILLAGE.'");
	oldman->setAT("'KNOWLEDGE IS POWER AND POWER IS FREEDOM!'");
	VillageCent->setNPC(oldman);
	fbook->setnTarget(oldman);
	oldman->getInventory()->add(pStone);
	oldman->setOccur("'MY GOD! THIS BOOK IS... NOTHING YOU SHOULD BE CONCERNED ABOUT. THIS BOOK WILL BE VERY USEFUL HOWEVER. FOR YOUR TROUBLE, HERE IS SMALL STONE.'\n\nHE GIVES YOU A PHILOSOPHER'S_STONE.\n\n");
	
	// placing the player in the Shack
	Player* player = new Player(Shack);

	cout << "WELCOME TO THE ISA AVENTURE GAME. IF YOU EVER NEED ANY HELP, JUST TYPE \"HELP\"" << endl;
	cout << "(PLAYER INPUT IS NOT CASE SENSITIVE)" << endl << endl << endl << endl << endl;

	cout << "YOU WAKE UP IN A SHACK. YOU FEEL A LITTLE DIZZY AND CAN'T REMEMBER ANYTHING ABOUT YOUR PAST. YOU LOOK AROUND.\n\n";
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
