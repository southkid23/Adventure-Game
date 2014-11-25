#include "classes.h"
#include <iostream>
#include <string>
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

Room::Room(string n/*,Room** listr,int room*/,List* rIt/*,NPC* listn[],int NPC*/,string descr)//constructor
{
	//hasBeen = false;
	name = n;
	rItems = rIt;
	/*nDoors = room;
	listItems = listi;
	nItems = items;
	listNPC = listn;
	nNPC = NPC;*/
	description = descr;
	obst = new Obstacle*[4];
	setObstacleE(NULL);setObstacleN(NULL);setObstacleS(NULL);setObstacleW(NULL);
	hasBeen = false;
}

void Room::enter()
{
	if(!entered())
		cout << getDescription() << endl << endl;
	else
		cout << "YOU ARE BACK TO THE " << getName() << endl << endl;
	roomitems(cout);cout << "" << endl;
	roomNPC(cout);cout << "" << endl << endl;
	hasBeen = true;
}

ostream& Room::roomNPC(ostream& out)
{
	if(npc == NULL)
		out << "THERE IS NO-ONE IN THIS ROOM";
	else
	{
		out << "PEOPLE IN THIS AREA:\n" << npc->getName();
	}
	return out;
}

ostream& Room::roomitems(ostream& out)
{
	if(!rItems->isEmpty())
	{
		out << "ITEM(S) IN ROOM:\n";
		rItems->listAll(out);out << "";
	}
	else
		out << "THERE IS NOTHING IN THIS ROOM." << endl;
	return out;
}

void Player::doAction(string verb, string noun)
{
	//cout << "verb is " << verb << endl << "Noun is " << noun << endl;
	if(verb == "GO" || verb == "MOVE")
	{

		if(noun == "NORTH")//To Go North//Same for south,east and west
		{
			if(currentR()->getObstacleN() != NULL && currentR()->getObstacleN()->prevent() == "NORTH")
				cout << currentR()->getObstacleN()->getpInfo() << endl << endl;
			
			else if (currentR()->getNorth() != NULL)//Check if NULL
			{
				currentR(currentR()->getNorth());//Sets current player location to north location
				cout << "YOU MOVED NORTH.\n" << endl; currentR()->enter();// << endl << endl;
			}
			else//If no location!
				cout << "THERE'S NOTHING THERE." << endl << endl;
		}
		else if(noun == "SOUTH")
		{ 

			if(currentR()->getObstacleS() != NULL && currentR()->getObstacleS()->prevent() == "SOUTH")
				cout << currentR()->getObstacleS()->getpInfo() << endl << endl;

			else if (currentR()->getSouth() != NULL)
			{
				currentR(currentR()->getSouth());
				cout << "YOU MOVED SOUTH.\n" << endl; currentR()->enter();// << endl << endl;
			}
			else
				cout << "THERE'S NOTHING THERE." << endl << endl;
		}
		else if(noun == "EAST")
		{
			if(currentR()->getObstacleE() != NULL && currentR()->getObstacleE()->prevent() == "EAST")
				cout << currentR()->getObstacleE()->getpInfo() << endl << endl;
			else if (currentR()->getEast() != NULL)
			{
				currentR(currentR()->getEast());
				cout << "YOU MOVED EAST.\n" << endl; currentR()->enter();
			}
			else
				cout << "THERE'S NOTHING THERE." << endl << endl;
		}
		else
		{
			if(currentR()->getObstacleW() != NULL && currentR()->getObstacleW()->prevent() == "WEST")
				cout << currentR()->getObstacleW()->getpInfo() << endl << endl;
			else if (currentR()->getWest() != NULL)
			{
				currentR(currentR()->getWest()); 
				cout << "YOU MOVED WEST.\n" << endl; currentR()->enter();
			}
			else
				cout << "THERE'S NOTHING THERE." << endl << endl;
		}
	
	}
	else if(verb == "EXAMINE")//Examine returns an item description
	{
		if(getInventory()->findName(noun) != NULL)
		{	
			Item* it = getInventory()->findName(noun);
			cout << it->getInfo() << endl << endl;
		}
		else
			cout << "Cannot examine " << noun << "." << endl;
	}
	/*else if(verb == "READ")//Read reads an item if it is a "book"
	{
		Item* it = getInventory()->findName(noun);
		cout << it->read();
	}*/
	else if(verb == "USE")//Used to carry out actions on targets
	{
		if(getInventory()->findName(noun) != NULL)
		{	
			if(getInventory()->findName(noun)->getTarget() != NULL)
			{
				cout << "USE " << noun << " ON WHAT? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
	
				if(currentR()->getObstacleN() != NULL && (currentR()->getObstacleN()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
				{
					cout << currentR()->getObstacleN()->getOccur() << endl;
					delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
				}
				else if(currentR()->getObstacleE() != NULL && (currentR()->getObstacleE()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
				{
					cout << currentR()->getObstacleE()->getOccur() << endl;
					delete currentR()->getObstacleE(); currentR()->setObstacleE(NULL);
				}
				else if(currentR()->getObstacleS() != NULL && (currentR()->getObstacleS()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
				{
					cout << currentR()->getObstacleS()->getOccur() << endl;
					delete currentR()->getObstacleS(); currentR()->setObstacleS(NULL);
				}

				else if(currentR()->getObstacleW() != NULL && (currentR()->getObstacleW()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
				{
					cout << currentR()->getObstacleW()->getOccur() << endl;
					delete currentR()->getObstacleW(); currentR()->setObstacleW(NULL);
				}		

				else
				{
					cout << "Cannot use " << noun << " on " << target << ".\n\n";
				}

			}
			else if(getInventory()->findName(noun)->getiTarget() != NULL)
			{
				cout << "USE " << noun << " ON WHAT? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
				if(getInventory()->find(target) == 0 && currentR()->getrItems()->find(target) == 0)
					cout << target << " IS NOT IN YOUR INVENTORY OR ROOM" << endl << endl;
				else
				{
					if(getInventory()->find(target) != 0)
					{
						cout << "YOU USE " << noun << " ON " << target << ".";
						cout << "YOU NOW HAVE " << getInventory()->findName(noun)->getProduct()->getName() << ".\n";
						getInventory()->add(getInventory()->findName(noun)->getProduct());
						if(getInventory()->findName(target) != NULL)
							{getInventory()->removeItem(noun);getInventory()->removeItem(target);}
						else
							{getInventory()->removeItem(noun);currentR()->getrItems()->removeItem(target);}
					}
					if(currentR()->getrItems()->find(target) != 0)
					{
						cout << "YOU USE " << noun << " ON " << target << ".";
						cout << "YOU NOW HAVE " << getInventory()->findName(noun)->getProduct()->getName() << ".\n";
						getInventory()->add(getInventory()->findName(noun)->getProduct());
						getInventory()->removeItem(noun);currentR()->getrItems()->removeItem(target);
					}
					else
						cout << "YOU CAN'T USE " << noun << " ON " << target << endl;
				}
			}
			else
				cout << noun << " cannot be used." << ".\n\n";
		}
		else
			cout << "YOU DON'T HAVE A " << noun << " TO USE.\n\n";
	}
	else if(verb == "TAKE") // takes an item
	{

		if(noun == "")
		{
			cout << "TAKE WHAT?\n\n";cin >> noun;toUpper(noun);
		}
		if(currentR()->getrItems()->findName(noun) == NULL || !currentR()->getrItems()->findName(noun)->isTak())
		{
			cout << "THERE IS NO SUCH ITEM IN THE ROOM OR CANNOT BE TAKEN." << endl;currentR()->roomitems(cout);cout << "" << endl << endl;
		}
		else
		{	
			getInventory()->add(currentR()->getrItems()->findName(noun));
			currentR()->getrItems()->removeItem(noun);
			cout << noun << " is now in your Inventory." << endl << endl;
		}
	}
	else if(verb == "TALK")
	{
		if(noun == "")
		{
			cout << "TALK TO WHO?\n\n";cin >> noun;toUpper(noun);
		}
		if(currentR()->getNPC() != NULL)
		{
			if(currentR()->getNPC()->getName() == noun)
			{
				cout << currentR()->getNPC()->talk() << endl << endl;
			}
			else
			{
				cout << "There is no one by the name of " << noun << " in here.\n\n";
			}
		}
		else
		{
			cout << "There is no one to speak to.\n\n";
		}
	}
	else if(verb == "GIVE")
	{
		if(getInventory()->find(noun) != 0)
		{
			if(getInventory()->findName(noun)->getnTarget() != NULL)
			{
				cout << "To? ";
				string target = ""; cin >> target;
				toUpper(target);
				if(getInventory()->findName(noun)->getnTarget()->getName() == target && currentR()->getNPC()->getName() == target)
				{
					cout << endl << currentR()->getNPC()->getOccur();
					getInventory()->removeItem(noun);
					getInventory()->add(currentR()->getNPC()->getHas());
				}
				else
				cout << "Cannot give " << noun << " to " << target << ".\n\n";
			}
			else
				cout << noun << " cannot be given.\n\n";
		}
		else
			cout << "You do not have a " << noun << " to give.\n\n";
	}
	else if (verb == "HELP")//Gives extremely useful advice
	{
		cout << "COMMAND LIST: \n- GO (NORTH,SOUTH,EAST,WEST)\n- TAKE\n- DROP\n- USE\n- EXAMINE\n- READ\n- TALK\n- GIVE\n\n";
		/*cout << "There will be items in the room that you will be able to pick up or drop them. Type \'take\' \'drop\' followed by the name of the item. "; 
		cout << "To interact an item with and object just type \'use\' and then followed by the name of the item. ";
		cout << "\n\nHere are a list of some extra commands: " << endl << "Examine" << endl << "Read" << endl << endl;
	*/}
	else if(verb == "LIST" || "INVENTORY")
	{
		if(getInventory()->isEmpty())
			cout << "THERE IS NOTHING IN YOUR INVENTORY.\n\n";
		else
			listAllItems();
	}
	else
		cout << "Sorry but I don't understand.\n" << endl;
}


List::List()//Constructor
{
	head = NULL;
}

List::~List()//Deconstructor
{
	Node* walker = head;
    while(walker!=NULL){
        head=walker;
        walker=walker->next;
        delete head;
    }
    walker=NULL;
    head=NULL;
}

bool List::isEmpty()//Checks if List is empty
{
	return (head == NULL);
}

void List::add(Item* item)//Adds item to List
{
    Node* walker=head;
    Node* n=new Node;
    n->data=item;
    if (head==NULL) {
        head=n;
        head->next=NULL;
    }
    else{
        while (walker->next!=NULL) {
            walker=walker->next;
        }
        walker->next=n;
        n->next=NULL;
    }
}

int List::find(Item* value)
{
	int count=0;
    Node* walker=head;
    if (head==NULL) 
	{
        return 0;
    }
    while (walker!=NULL) 
	{
        if (walker->data==value) 
		{
            break;
        }
        if (walker->next==NULL) 
		{
            return 0;
        }
        walker=walker->next;
    }
    return 1;
}

int List::find(string value)
{
	int count=0;
    Node* walker=head;
    if (head==NULL) 
	{
        return 0;
    }
    while (walker!=NULL) 
	{
		if (walker->data->getName() == value) 
		{
            break;
        }
        if (walker->next==NULL) 
		{
            return 0;
        }
        walker=walker->next;
    }
    return 1;
}

Item* List::findName(string value)
{
    Node* walker=head;
    if (head==NULL) {
        return NULL;
    }
    while (walker!=NULL) {
        if (walker->data->getName()==value) {
            break;
        }
        if (walker->next==NULL) {
            return NULL;
        }
        walker=walker->next;
    }
    return walker->data;
}


std::ostream& List::listAll(std::ostream& out)//Lists all item in list
{
	Node* walker = head;
	while(walker != NULL)
	{
		if(head == NULL)
		{
			out << "THIS ROOM IS EMPTY.\n";
			break;
		}
		out << "- " << walker->data->getName() << endl;
		walker = walker->next;
	}
	return out;
}

void List::removeItem(string item)
{    // maybe works?
    Node* walker = head;
	Node* walker2 = head;
	if(head->data->getName() == item)
	{
		Node* walker3 = head;
		head = head->next;
		delete walker3;
		walker3 = NULL;
	}
	else
	{
		while(true)
		{
			if(walker->data->getName() == item)
			{
				Node* walker3 = walker;
				walker = walker->next;
				while(true)
				{
					if(walker2->next == walker3)
					{
						walker2->next = walker;
						break;
					}
					walker2 = walker2->next;
				}
				delete walker3;
				walker3 = NULL;
				break;
			}
			walker = walker->next;
		}
	}
}

string NPC::talk()
{
	if(talked == false)
	{
		talked=true;
		return firstT;
	}
	else
		return afterT;
}
