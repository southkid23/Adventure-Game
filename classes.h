#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

class Room
{
private:
	Room* North; Room* South; Room* West; Room* East;//int nDoors;//rooms adjoining with current
	string name,inHouse,description;//description & name of building
	//Item** listItems;int nItems;//list of uncollected/unusable items
	//NPC** listNPC;int nNPC;//list of live/unkillable NPC in room
	//bool hasBeen;
public:
	Room(string n/*,Room** listr,int room,Item* listi[],int items,NPC* listn[],int NPC*/,string descr);//Room constructor. Should Create room
	//ostream& roomitems(ostream&);//List of items contained in room Eg. Furniture
	//ostream& roomNPC(ostream&);//List of non-playable characters in room
	//bool entered();//Check if room has been discovered
	//virtual void enter();//When player enters the room
	string getDescription(){return description;}
	//Room** getDoors(){return doors;}
	string getName(){return name;}
	void setNorth(Room* room){North=room;}
	void setSouth(Room* room){South=room;}
	void setEast(Room* room){East=room;}
	void setWest(Room* room){West=room;}
	Room* getNorth(){return North;}
	Room* getSouth(){return South;}
	Room* getEast(){return East;}
	Room* getWest(){return West;}
};

class Item{
private:
	string itemName;
	string itemInfo;
	Item* target;
	bool isEnvItem;
	string book;

public:
	Item(){}
	Item(string thing, string info, Item* t, bool isE){itemName = thing; itemInfo = info; target = t; isEnvItem = isE;}
	virtual ~Item(){};
	string getName(){return itemName;} 
	string getInfo(){return itemInfo;} 
	void setName(string thing){itemName = thing;}
	void setInfo(string info){itemInfo = info;}
	virtual bool itemCondition(){return 0;}
	bool worksOn(Item* t);
	string read(){return book;}
	Item* getTarget(){return target;}
};


struct Node{
	Item* data;
	Node* next;
	Node* prev;
};

class List{
	private:
		Node* head;
	public:
		List();
		~List();
		Node* getHead(){return head;};
		bool isEmpty();
		void add (Item* value);
		void removeItem(Item* item);
		string listAll();
		int find (Item* value);
		Item* findName(string value);
		int getSize();
};

class Player {

private:
		Room* r;
		List* inventory;

public:
		Player(Room* lo){r=lo;}
		~Player(){}
		//List* inventory(){return invItems;}
		//void inventory(List* items){invItems=items;}
		Room* currentR(){return r;}
		List* getInventory(){return inventory;}
		void currentR(Room* nw){r=nw;}
		void doAction(string verb, string noun);
		void listAllItems();
};



