#include <cstddef>
#include <iostream>
#include <string>
using namespace std;


class Item{
private:
	string itemName;//Item name
	string itemInfo;//Item Description
	Item* target;//what Item can be used on
	bool isEnvItem;//If an enviromental item
	string book;//When item is read(if book)
	string occur;//When Item has been unlocked

public:
	Item(){}
	Item(string thing, string info, Item* t, bool isE, string occ){itemName = thing; itemInfo = info; target = t; isEnvItem = isE; occur = occ;}//Item Constructor
	virtual ~Item(){};
	void setName(string thing){itemName = thing;}//Sets item name
	void setInfo(string info){itemInfo = info;}//Sets item description
	string getName()const{return itemName;}//Gets name of item
	string getInfo()const{return itemInfo;}//Gets item description
	string read()const{return book;}//outputs when item is to be read
	string getOccur()const{return occur;}//outputs when item has been unlocked
	Item* getTarget()const{return target;}//Gets what item current can be used on
	virtual bool itemCondition()const{return 0;}//
	bool worksOn(Item* t)const{return t == target;}//check if item is used on another item
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


class Room
{
private:
	Room* North; Room* South; Room* West; Room* East;//rooms adjoining with current
	string name,inHouse,description;//description & name of building
	List* rItems;//list of uncollected/unusable items
	//NPC** listNPC;int nNPC;//list of live/unkillable NPC in room
	//bool hasBeen;
public:
	Room(string n/*,Room** listr,int room*/,List* rIt/*,NPC* listn[],int NPC*/,string descr);//Room constructor. Should Create room
	//ostream& roomitems(ostream&);//List of items contained in room Eg. Furniture
	//ostream& roomNPC(ostream&);//List of non-playable characters in room
	//bool entered();//Check if room has been discovered
	//virtual void enter();//When player enters the room
	//Room** getDoors(){return doors;}
	string getDescription()const{return description;}//Get room description
	string getName()const{return name;}//Get room name
	List* getrItems()const{return rItems;}//Get room items
	Room* getNorth()const{return North;}//Get North location
	Room* getSouth()const{return South;}//Get South Location
	Room* getEast()const{return East;}//Get East location
	Room* getWest()const{return West;}//Get west location
	void setNorth(Room* room){North=room;}//Set North Location
	void setSouth(Room* room){South=room;}//Set South location
	void setEast(Room* room){East=room;}//Set East Location
	void setWest(Room* room){West=room;}//Set West Location
};

class Player {

private:
		Room* r;//Current room
		List* inventory;//List of items in inventory

public:
		Player(Room* lo){r=lo;}//Constructor with starting room
		~Player(){}
		//List* inventory(){return invItems;}
		//void inventory(List* items){invItems=items;}
		Room* currentR()const{return r;}//Get current room
		List* getInventory()const{return inventory;}//Returns List of inventory items
		void currentR(Room* nw){r=nw;}//Changes current room
		void doAction(string verb, string noun);//Carries out specified action
		void listAllItems();//Lists all items
};


