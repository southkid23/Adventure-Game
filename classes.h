#include <cstddef>
#include <iostream>
#include <string>
using namespace std;


class NPC;

class Obstacle{
private:
	string name;
	string occur;//When Item has been unlocked
	string prevents;
	string pInfo;

public:
	Obstacle(string n){name=n;}
	~Obstacle(){}
	void setName(string n){name=n;}
	void prevent(string s){prevents = s;}
	void setpInfo(string s){pInfo=s;}
	void setOccur(string occ){occur = occ;}
	string getName()const{return name;}
	string prevent()const{return prevents;}
	string getpInfo()const{return pInfo;}
	string getOccur()const{return occur;}//outputs when item has been unlocked
};

class Item{
private:
	string itemName;//Item name
	string itemInfo;//Item Description
	Obstacle* target;//what Item can be used on
	bool isTakeable;//If an item is pickable
	string book;//When item is read(if book)
	//new stuff
	Item* iTarget;Item* product;
	NPC* nTarget;

public:
	Item(){}
	Item(string thing, string info, bool isT){itemName = thing; itemInfo = info; isT = isTakeable;target = NULL;iTarget = NULL;product = NULL;nTarget = NULL;}//Item Constructor
	virtual ~Item(){};
	void setName(string thing){itemName = thing;}//Sets item name
	void setInfo(string info){itemInfo = info;}//Sets item description
	void setTarget(Obstacle* o){target = o;}
	void setnTarget(NPC* t){nTarget = t;}
	void setiTarget(Item* targ){iTarget = targ;}//If to be used on another item
	void setProduct(Item* prod){product = prod;}
	string getName()const{return itemName;}//Gets name of item
	string getInfo()const{return itemInfo;}//Gets item description
	string read()const{return book;}//outputs when item is to be read
	Obstacle* getTarget()const{return target;}//Gets what item current can be used on
	NPC* getnTarget()const{return nTarget;}
	Item* getiTarget()const{return iTarget;}
	Item* getProduct()const{return product;}
	virtual bool isTak()const{return isTakeable;}// returns if takeable or not
	bool worksOn(Obstacle* t)const{return t == target;}//check if item is used on another item
};

struct Node{
	Item* data;
	Node* next;
};

class List{
	private:
		Node* head;
	public:
		List();
		~List();
		Node* getHead(){return head;};
		bool isEmpty();
		void add (Item* item);
		void removeItem(string item);
		std::ostream& listAll(std::ostream& out);
		int find (Item* value);
		int find (string value);
		Item* findName(string value);
		int getSize();
};



class Room
{
private:
	Room* North; Room* South; Room* West; Room* East;//rooms adjoining with current
	string name,inHouse,description;//description & name of building
	List* rItems;//list of uncollected/unusable items
	Obstacle** obst;
	NPC* npc;//list of live/unkillable NPC in room
	bool hasBeen;
public:
	Room(string n,List* rIt,string descr);//Room constructor. Should Create room
	~Room(){delete [] obst;}
	ostream& roomitems(ostream&);//List of items contained in room Eg. Furniture
	ostream& roomNPC(ostream&);//List of non-playable characters in room
	bool entered(){return hasBeen;};//Check if room has been discovered
	void enter();//When player enters the room
	string getDescription()const{return description;}//Get room description
	string getName()const{return name;}//Get room name
	List* getrItems()const{return rItems;}//Get room items
	Room* getNorth()const{return North;}//Get North location
	Room* getSouth()const{return South;}//Get South Location
	Room* getEast()const{return East;}//Get East location
	Room* getWest()const{return West;}//Get west location
	Obstacle* getObstacleN()const{return obst[0];}
	Obstacle* getObstacleE()const{return obst[1];}
	Obstacle* getObstacleS()const{return obst[2];}
	Obstacle* getObstacleW()const{return obst[3];}
	NPC* getNPC()const{return npc;}
	void setNorth(Room* room){North=room;}//Set North Location
	void setSouth(Room* room){South=room;}//Set South location
	void setEast(Room* room){East=room;}//Set East Location
	void setWest(Room* room){West=room;}//Set West Location
	void setObstacleN(Obstacle* obs){obst[0]=obs;}
	void setObstacleE(Obstacle* obs){obst[1]=obs;}
	void setObstacleS(Obstacle* obs){obst[2]=obs;}
	void setObstacleW(Obstacle* obs){obst[3]=obs;}
	void setNPC(NPC* n){npc=n;}
};


class Player {

protected:
		Room* r;//Current room
		List* inventory;//List of items in inventory

public:
		Player(Room* lo){r=lo; inventory = new List();}//Constructor with starting room
		virtual ~Player(){delete inventory;}
		//List* inventory(){return invItems;}
		//void inventory(List* items){invItems=items;}
		Room* currentR()const{return r;}//Get current room
		List* getInventory()const{return inventory;}//Returns List of inventory items
		void currentR(Room* nw){r=nw;}//Changes current room
		void doAction(string verb, string noun);//Carries out specified action
		void listAllItems(){inventory->listAll(cout);cout << "\n";}//Lists all items
};

class NPC:public Player{

private:
	string name;
	string firstT;
	string afterT;
	string occur;
	string has;
	bool talked;

public:
	NPC(Room* r, string n, string h):Player(r){name=n; has=h; talked=false;}
	~NPC(){delete inventory;}
	string talk();
	string getName()const{return name;}
	string getFT()const{return firstT;}
	string getAT()const{return afterT;}
	string getOccur()const{return occur;}
	Item* getHas()const{return getInventory()->findName(has);}
	void setFT(string s){firstT=s;}
	void setAT(string s){afterT=s;}
	void setOccur(string s){occur=s;}
};
