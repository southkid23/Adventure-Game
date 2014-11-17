#include <string>
#include <iostream>
using namespace std;

class Item{
	protected:
		string itemName;
		string itemInfo;
	public:
		Item(){}
		Item(string thing, string info){getName(thing);}
		virtual ~Item(){};

		string getName(){return itemName;}
		void getName(string thing){itemName = thing;}
		virtual bool itemCondition(){return 0;}
};