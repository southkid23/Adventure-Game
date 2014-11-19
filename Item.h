#include <string>
#include <iostream>
using namespace std;

class Item{
	protected:
		string itemName;
		string itemInfo;
	public:
		Item(){}
		Item(string item, string info){itemName = setName(thing); itemInfo = setInfo(info);}
		virtual ~Item(){};

		string getName(){return itemName;} void setName(string thing){itemName = thing;}
		string getInfo(){return itemInfo;} void setInfo(string info){itemInfo = info;}
		virtual bool itemCondition(){return 0;}
};

class inventItem:Item
{
	public:
		inventItem(){};
		inventItem(string thing, string info){getName(thing); getInfo(info);}
		~inventItem(){};

		bool take{};
		bool drop{};
		bool use{};
};

class envItem: public Item
{
	public:
		envItem(){};
		envItem(string thing, string info){getName(thing); getInfo(thing);}
		~envItem(){};
};
