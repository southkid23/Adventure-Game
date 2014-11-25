#include "definitions.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

int main()
{
	system("color 2");
	Room* Shack;Room* VillageCent;Room* Graveyard;Room* Bank;Room* LargeHouse; Room* uTomb; Room* bRoom; Room* backyard; Room* storage;
	
	List* vItems = new List(); List* sItems = new List(); List* bItems = new List(); List* gItems = new List(); List* lItems = new List();
	List* uItems = new List(); List* brItems = new List(); List* byItems = new List(); List* stItems = new List();
	
	//Setting Obstacles
	Obstacle* guard = new Obstacle("GUARD"); 
	guard->prevent("WEST"); 

	guard->setpInfo("A GUARD IS PREVENTING YOU FROM ENTERING THE BANK.");
	guard->setOccur("THE GUARD SMILES. HE THEN LIES DOWN AND TAKES A NAP.");	

	Obstacle* door = new Obstacle("DOOR"); 
	door->prevent("NORTH"); 
	door->setpInfo("DOOR IS LOCKED."); 
	door->setOccur("THROWN TO THE DOOR. DOOR GETS BROKEN DOWN.");

	Obstacle* backDoor = new Obstacle("BACKDOOR"); 
	backDoor->prevent("NORTH");
	backDoor->setpInfo("HEAVENLY FORTIFIED BACKDOOR OF THE BANK. ONLY HERCULES COULD MOVE THIS.");
	backDoor->setOccur("\'CLICK\' THE DOOR IS UNLOCKED.");

	Obstacle* window = new Obstacle("WINDOW");
	window->prevent("NORTH");

	window->setpInfo("THERE ARE SEVERAL PLANKS OF WOOD NAILED TO THE DOOR. THE WINDOW NEXT TO THE DOOR IS A LITTLE CRACKED AND SEEMS EASILY BREAKABLE."); 
	window->setOccur("GLASSBALL WAS THROWN AT THE WINDOW. THE WINDOW BREAKS. YOU HEAR THE SOUND OF THE \nENERGY OF THE UNIVERSE UNLEASED FROM THE GLASSBALL. NOTHING HAPPENED. THE WORLD\nSEEMS TO BE STILL INTACT.");

	Obstacle* gate = new Obstacle("GATE");
	gate->prevent("EAST");
	gate->setpInfo("THE GATE TO THE GRAVEYARD IS FIRMLY LOCKED.");
	gate->setOccur("THE GATE MAKES A CREAKING SOUND AS IT OPENS.");

	Obstacle* tomb = new Obstacle("TOMB");
	tomb->prevent("SOUTH");
	tomb->setpInfo("THERE IS AN OLD AND ANCIENT TOMB. THE TOP OF THE TOMB SEEMS TO BE SHIFTED A \nLITLE. YOU TRY LIFTING THE TOP BUT IT IS TOO HEAVY.");
	tomb->setOccur("YOU USE THE CROWBAR TO LIFT THE TOP OF THE TOMB. IT MAKES A LOUD SOUND AS IT\nHITS THE GROUND. YOU NOTICE THAT THERE IS A STAIRWAY THAT LEADS DOWN.");

	//Items
	
	Item* crowbar = new Item("CROWBAR", "A RUSTY, OLD CROWBAR. SEEMS STURDY.", true); 
	crowbar->setTarget(tomb);

	Item* Monkey = new Item("MONKEY", "AN ACTIVE MONKEY THAT SEEMS A LITTLE LOST. IT HAS A TAG AROUND ITS NECK. LOOKING CLOSELY, IT SAYS \'DING THE MONKEY\'", true);
	
	Item* bedFrame = new Item("BED_FRAME","A STURDY METAL BED FRAME WITHOUT A MATTRESS ON IT. SEEMS LIGHTWEIGHT...", true);
	bedFrame->setTarget(door);

	Item* glassBall = new Item("GLASSBALL", "THIS GLASSBALL SEEMS TO HOLD ALL THE ENERGY OF THE UNIVERSE. \nBEWARE...\n THE REST OF THE WARNING IS TORNED OFF", true);
	glassBall->setTarget(window);

	Item* aTable = new Item("TABLE", "THE TABLE HAS SOME WEIRD LOOKING SYMBOLS. IT LOOKS LIKE IT MIGHT HAVE BEEN USED FOR WITCHCRAFT OR ALCHEMY.", false);

	Item* bananaskin = new Item("SKIN", "USELESS PIECE OF SKIN...", true);

	Item* lockpick = new Item("LOCKPICK", "OLD AND RUSTY BUT SEEMS STEADY ENOUGH TO USE IT FOR ONE LAST TIME.", true);
	lockpick->setTarget(backDoor); 

	Item* gold = new Item("GOLD", "PURE GOLD. CAN CORRUPT EVEN THE MOST INNOCENT.", true);
	gold->setTarget(guard);

	Item* pStone = new Item("PHILOSOPHER'S_STONE", "YOU FEEL A STRANGE POWERFUL AURA.", true);

	pStone->setiTarget(aTable); pStone->setProduct(gold);

	Item* key = new Item("KEY","I WONDER WHAT THIS UNLOCKS...",true);
	key->setTarget(gate);

	Item* fbook = new Item("BOOK", "SEEMS LIKE IT IS A BOOK FROM ANOTHER COUNTRY.", true);

	Item* lchest = new Item("CHEST", "WONDER WHAT'S INSIDE...", false);
	
	Item* ckey = new Item("CHEST_KEY", "LOOKS LIKE A KEY TO A CHEST...", true);
	ckey->setiTarget(lchest); ckey->setProduct(fbook);

	Item* apple = new Item("APPLE", "A SHINY JUICY APPLE.", true);

	Item* gNote = new Item("NOTE", "THE MESSAGE ON THE NOTE MADE YOU MAD AND YOU FEEL LIKE BREAKING THE TOMB RIGHT \nBEHIND YOU.", true);

	Item* desk = new Item("DESK", "A FANCY DESK. IT MIGHT HAVE BEEN USED TO COUNT THE MONEY.", false);

	Item* explosive = new Item("EXPLOSIVE", "THE SMELL OF GUNPOWDER IS INTOXICATING.", true);
	explosive->setiTarget(desk); explosive->setProduct(glassBall);

	Item* dirt = new Item("DIRT", "A FRESH PATCH OF DIRT.", false);

	Item* blacknote = new Item("BLACKNOTE", "A DIRTY BLACKNOTE WITH WHITE WORDS ON IT. IT MAY BE IMPORTANT TO READ.", true);

	Item* shovel = new Item("SHOVEL", "A STURDY SHOVEL. SEEMS LIKE IT WAS RECENTLY USED BEFORE.", true);
	shovel->setiTarget(dirt); shovel->setProduct(blacknote);
	
	// Items in Shack
	sItems->add(apple);
	sItems->add(ckey);
	sItems->add(bananaskin);
	sItems->add(lchest);
	sItems->add(bedFrame);

	// Items in VillageCenter
	vItems->add(crowbar);
	// Items in Graveyard 
	gItems->add(gNote);
	gItems->add(Monkey);
	
	// Items in Undertomb
	uItems->add(aTable);
	
	// Items in the Bank
	bItems->add(explosive);
	
	// Items in the Backroom of the Bank
	brItems->add(desk);
	
	// Items in the Backyard of the Large House
	byItems->add(dirt);
	
	// Items in the Storage
	stItems->add(shovel); 


	//Defining Rooms

	Shack = new Room("SHACK", sItems,"YOU ARE IN AN OLD AND DUSTY SHACK. THERE IS A LITTLE GIRL STRANGELY LOOKING AT \nYOU. EVERYTHING SEEMS TO BE WORN OUT FROM AGE OR OVERUSED.\nTHE DOOR TO THE NORTH LEADS TO OUTSIDE.");
	VillageCent = new Room("VILLAGE CENTER", vItems, "YOU ARE IN THE CENTER OF THE VILLAGE THERE IS A SMALL WELL. NEXT TO THE WELL IS AN OLD MAN WITH A LONG BEARD AND A LONG STAFF. HE APPEARS TO BE VERY WISE, YET \nVERY CONFUSED. TO THE SOUTH OF \nTHE CENTER IS THE SHACK. TO THE EAST IS A FENCED GRAVEYARD. TO THE WEST IS A \nBANK. TO THE NORTH IS A MANSION.");
	Bank = new Room("BANK", bItems, "THE BANK SEEMS TO BE UNDER CONSTRUCTION DUE TO SOME UNUSUAL DAMAGE DUE TO FIRE. IN THE BANK \nTHERE IS A LOT OF STUFF THAT WAS BURNT FROM THE FIRE. THE WALLS ARE MOSTLY BLACK. WEIRDLY ENOUGH, THE \nBACKDOOR TO THE NORTH OF THE BANK IS STILL LOOKING GOOD.");
	Graveyard = new Room("GRAVEYARD", gItems, "YOU JUST HAD A WEIRD VISION ABOUT THE VILLAGE ON FIRE. \nTHE VILLAGERS WERE TREMBLING IN FEAR, SHOUTING AND TRYING TO GET AWAY FROM SOMETHING. \nI WONDER WHAT...\nTHE GRAVEYARD IS MISTY. SOME TOMBS SEEMS TO BE BUILT RECENTLY. THE TOMB TO THE SOUTH \nLOOKS DIFFERENT. HMmM...");
	LargeHouse = new Room("MANSION", lItems, "THE HOUSE LOOKS REALLY FANCY. WOULD LOOK BETTER IF NOT FOR THE DUST THAT HAD \nCOLLECTED OVER THE MONTHS. THERE'S A BEAUTIFUL BACKYARD AT THE BACK OF THE HOUSE.\nTHE LIVING ROOM SEEMS TO HAVE A WEIRD SYMBOL THAT COMBINES A CIRCLE AND A TRIANGLE.");
	uTomb = new Room("TOMB", uItems, "YOU ENCOUNTER A LOT OF COBWEB AS YOU GO DOWN THE STAIRWAY. IT GETS DARKER THE DEEPER YOU GO. AT THE END, HOWEVER, YOU SEE A LIGHT. YOU ENTER A SMALL, LIT-UP CAVE. THE CANDLES ILLUMANTING THE CAVE ARE ABOUT TO GO OUT. IT LOOKS LIKE SOMEBODY OCCUPIED THIS PLACE FOR A COUPLE DAYS. THERE ARE SEVERAL ANIMAL SKINS HUNG ON THE WALLS AND LAID ON THE FLOOR.");
	bRoom = new Room("BACKROOM", brItems, "YOU ENTER A ROOM FILLED WITH SHELVES OF BOOKS. IT DOESN'T SEEM LIKE THIS PART OF \nTHE BUILDING WAS AFFECTED BY FIRE. THERE IS A FANCY DESK AT THE BACK OF THE \nROOM. YOU TRY TO OPEN THE DESK DRAWERS BUT THEY ARE SEEM TO BE FIRMLY LOCKED.");
	backyard = new Room("BACKYARD", byItems, "THE BACKYARD WAS A GREEN AND FLOURISHING WORK OF NATURE. PLANTS OF ALL COLOR AND \nVARIATION WERE PLANTED ALL OVER THE AREA. THERE IS A HUGE OAK TREE STUMP IN THE \nMIDDLE OF THE GARDEN. NEAR THE TREE STUMP YOU SEE A PATCH OF FRESHLY MOVED DIRT.");
	storage = new Room("STORAGE", stItems, "A SMALL STORAGE CONTAINER. SEEMS LIKE IT MIGHT CONTAIN A LOT OF USEFUL TOOLS.");


	// Setting movable direction and obstacles for the room 'Shack'
	Shack->setNorth(VillageCent);
	Shack->setSouth(NULL);
	Shack->setEast(NULL); 
	Shack->setWest(NULL);
	Shack->setObstacleN(door);

	// Setting movable direction and obstacles for the room 'Village Center'
	VillageCent->setNorth(LargeHouse);
	VillageCent->setSouth(Shack);
	VillageCent->setEast(Graveyard);
	VillageCent->setWest(Bank);
	VillageCent->setObstacleN(window); 
	VillageCent->setObstacleW(guard); 
	VillageCent->setObstacleE(gate);
	VillageCent->setObstacleS(NULL);
	
	// Setting movable direction and obstacles for the room 'Graveyard'
	Graveyard->setNorth(NULL);
	Graveyard->setSouth(uTomb); 
	Graveyard->setEast(NULL); 
	Graveyard->setWest(VillageCent);
	Graveyard->setObstacleS(tomb);

	// Setting movable direction and obstacles for the room 'Shack'
	uTomb->setNorth(Graveyard);
	uTomb->setSouth(NULL);
	uTomb->setEast(NULL);
	uTomb->setWest(NULL);
	
	// Setting moveable directions and obstacles for the room 'Bank'
	Bank->setNorth(bRoom); 
	Bank->setSouth(NULL); 
	Bank->setEast(VillageCent); 
	Bank->setWest(NULL);
	Bank->setObstacleN(backDoor);

	// Settting moveable directions for the room 'Bank'
	bRoom->setNorth(NULL); 
	bRoom->setSouth(Bank); 
	bRoom->setEast(NULL); 
	bRoom->setWest(NULL);
	
	// Setting moveable directions and obstacles for the room 'Large House'
	LargeHouse->setNorth(backyard); 
	LargeHouse->setSouth(VillageCent);
	LargeHouse->setEast(NULL); 
	LargeHouse->setWest(NULL);

	backyard->setNorth(NULL);
	backyard->setSouth(LargeHouse);
	backyard->setEast(storage);
	backyard->setWest(NULL);

	storage->setNorth(NULL);
	storage->setSouth(NULL);
	storage->setEast(NULL);
	storage->setWest(backyard);

	// Place NPCs into different rooms
	NPC* lilgirl = new NPC(Shack, "LITTLE_GIRL", "KEY");
	lilgirl->setFT("\"HELLO MISTER. IT LOOKS YOU ARE FINALLY AWAKE. SORRY IF YOU ARE HURT BUT I HAD\nTO DRAG YOU INSIDE THIS SHACK. I'VE BEEN LIVING FOR A COUPLE DAYS IN THIS\nABANDONED PLACE. THERE WAS A FIRE LAST NIGHT AND I FOUND YOU WITH YOUR CLOTHES\nHALF-BURNT.\n\nDRAGGING YOU SURE MADE ME HUNGRY...\"");
	lilgirl->setAT("\"I'M HUNGRY\"");
	Shack->setNPC(lilgirl);
	apple->setnTarget(lilgirl);
	lilgirl->getInventory()->add(key);
	lilgirl->setOccur("\"THANK YOU FOR THE APPLE! SORRY, I DON'T HAVE ANYTHING TO GIVE IN RETURN...\nOH WAIT! I FOUND THIS USELESS KEY THE OTHER DAY!\"\n\nSHE GIVES YOU A KEY.\n");

	NPC* begger = new NPC(Bank, "BEGGER", "LOCKPICK");
	begger->setFT("\"HEY THERE YOUNG LAD, DID YOU HAPPEN TO SEE MY DING RUNNING AROUND THE AREA? YOU WILL BE REWARDED IF YOU HELP ME FIND HIM\"\n");
	begger->setAT("\"DING! WHERE ARE YOU. . . DING!\"");
	Bank->setNPC(begger);
	Monkey->setnTarget(begger);
	begger->getInventory()->add(lockpick);
	begger->setOccur("\"OH DING! THERE YOU ARE! NOW, LET US CONTINUE OUR JOURNEY TO THE WEST. TO SHOW MY APPRECIATION, TAKE THIS MY YOUNG LAD.\"\n\nHE GAVE YOU A LOCKPICK.\n\n");

	NPC* oldman = new NPC(VillageCent, "OLD_MAN", "STONE");
	oldman->setFT("\"WHY, HELLO THERE YOUNG LAD. I'M TRAVELING FAR AND WIDE IN SEARCH OF KNOWLDEGE\nAND EXPERIENCE. I WONDER WHAT KIND OF INTERESTING THINGS I CAN FIND IN THIS VILLAGE...\"");
	oldman->setAT("\"KNOWLEDGE IS POWER AND POWER IS FREEDOM!\"");
	VillageCent->setNPC(oldman);
	fbook->setnTarget(oldman);
	oldman->getInventory()->add(pStone);
	oldman->setOccur("\"MY GOD! THIS BOOK IS... NOTHING YOU SHOULD BE CONCERNED ABOUT. THIS BOOK WILL BE VERY USEFUL HOWEVER. FOR YOUR TROUBLE, TAKE THIS.\"\n\nHE GIVES YOU A PHILOSOPHER'S_STONE.\n\n");
	
	// placing the player in the Shack
	Player* player = new Player(Shack);
	
	cout << " \n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
	cout << "WELCOME TO THE I.S.A. AVENTURE GAME." << endl;
	cout << "(PLAYER INPUT IS NOT CASE SENSITIVE)\n";//FOR COMMAND LIST TYPE \"HELP\"" << endl;
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl << endl << endl;
	cout << "WOULD YOU LIKE A BRIEF OVERVIEW?(YES/NO)\n";string reply = "";
	cin >> reply;toUpper(reply); cout << endl << endl;
	if(reply == "YES"){
		player->doAction("HELP","");
	}
	cout << "\nYOU ARE READY TO BEGIN!!\n";PressEnterToContinue();

	cout << "\n\n\nYOU WAKE UP. YOU FEEL A LITTLE DIZZY AND CAN'T REMEMBER ANYTHING\nABOUT YOUR PAST. YOU LOOK AROUND AND THERE'S NOTHING YOU RECOGNIZE.\n\n";
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
			cout << "PLEASE ENTER NOT MORE THAN 2 WORDS." << endl;
			noun = ""; // Clears the variables
			verb = "";
		}
		
		else if((verb == "READ" && noun == "BLACKNOTE") && (player->getInventory()->find(noun) != 0))
		{
			cout << "AS YOU READ, LITTLE FRAGMENTS OF YOUR PAST START COMING BACK TO YOU. YOU REALIZE\nTHAT YOU ARE A SERIAL KILLER AND THAT YOU CAUSED THE FIRE IN THE VILLAGE. YOU\nFRANTICALLY LOOK AROUND AND REALIZED THAT THIS IS YOUR BACKYARD. YOU REMEMBER\nTHAT DEEPER IN THE HOLE YOU JUST DUG, YOU BURIED SOMEBODY...\n";
			break;
		}
		else
			player->doAction(verb, noun);
	}
	cout << "/nCONGRATULATIONS!!!!!!!!! YOU BEAT THE GAME!!";
<<<<<<< HEAD
	
	delete shovel;delete blacknote;delete dirt;
	delete explosive, desk, gNote, apple, ckey, lchest, fbook, key, pStone, gold, lockpick, bananaskin, aTable, glassBall, bedFrame, Monkey,crowbar;
=======

	delete shovel;delete blacknote;delete dirt;delete explosive,desk,gNote,apple,ckey,lchest,fbook,key,pStone,gold,lockpick,bananaskin,aTable,glassBall,bedFrame,Monkey,crowbar;



>>>>>>> 46eb3a58ab67d5e9c8ecdce4b47b4dc2e7641ba3
	// Rooms Deallocations	
	delete Shack; delete VillageCent; delete Graveyard; delete Bank; delete LargeHouse;
	delete uTomb; delete bRoom; delete backyard; delete storage;
	// Items Deallocations
	delete vItems;delete sItems;delete bItems;delete gItems;delete lItems;
	delete uItems;delete byItems;delete stItems;delete brItems;
	// NPCs Deallocation
<<<<<<< HEAD
	delete player;delete lilgirl;
	delete oldman;delete begger;
=======
	delete player;
	delete lilgirl;
	delete oldman;
	delete begger;
>>>>>>> 46eb3a58ab67d5e9c8ecdce4b47b4dc2e7641ba3

	system("PAUSE");

}

