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
		cout << "YOU ARE BACK TO " << getName() << endl;
	roomitems(cout);cout << "" << endl << endl;
	hasBeen = true;
}

ostream& Room::roomitems(ostream& out)
{
	out << "ITEMS IN ROOM:\n";
	rItems->listAll(out);out << "";
	return out;
}
/*
ostream& Room::roomNPC(ostream& out)
{
	out << "People in the room:";
	for(int i = 0;i < nItems;i++)
	{
		listNPC[i]->render(out);out<<"";
		out << "(" << i << ")" << endl;
	}
}

*/

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
		Item* it = getInventory()->findName(noun);
		cout << it->getInfo() << endl << endl;
	}
	else if(verb == "READ")//Read reads an item if it is a "book"
	{
		Item* it = getInventory()->findName(noun);
		cout << it->read();
	}
	else if(verb == "USE")//Used to carry out actions on targets
	{
		if(getInventory()->findName(noun) != NULL)
		{	
			if(getInventory()->findName(noun)->getTarget() != NULL)
			{
				cout << "USE " << noun << " ON WHAT? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
				if(getInventory()->findName(noun)->getTarget()->getName() == currentR()->getObstacleN()->getName())
				{
					cout << currentR()->getObstacleN()->getOccur() << endl;
					delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
				}
				else if(getInventory()->findName(noun)->getTarget()->getName() == currentR()->getObstacleE()->getName())
				{
					cout << currentR()->getObstacleE()->getOccur() << endl;
					currentR()->getObstacleE()->prevent("nothing");
				}
				else if(getInventory()->findName(noun)->getTarget()->getName() == currentR()->getObstacleS()->getName())
				{
					cout << currentR()->getObstacleS()->getOccur() << endl;
					currentR()->getObstacleS()->prevent("nothing");
				}
				else if(getInventory()->findName(noun)->getTarget()->getName() == currentR()->getObstacleW()->getName())
				{
					cout << currentR()->getObstacleW()->getOccur() << endl;
					currentR()->getObstacleW()->prevent("nothing");
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
				if(getInventory()->find(target) == 0)
					cout << target << " IS NOT IN YOUR INVENTORY" << endl << endl;
				else
				{
					if(target == getInventory()->findName(noun)->getiTarget()->getName())
					{
						cout << "YOU USE " << noun << " ON " << target << ".";
						cout << "YOU NOW HAVE " << getInventory()->findName(noun)->getProduct()->getName() << ".";
						getInventory()->add(getInventory()->findName(noun)->getProduct());
						getInventory()->removeItem(noun);getInventory()->removeItem(target);
					}
					else
						cout << "YOU CAN'T USE " << noun << " ON " << target << endl;
				}
				//if(getInventory()->find(getInventory()->findName(noun)->getiTarget()) == 0
				//if(getInventory()->findName(noun)->getiTarget()->getName() == 
			}
			else
				cout << noun << " cannot be used." << ".\n\n";
		}
		else
			cout << "You do not have a " << noun << " to use.\n\n";
	}
	else if(verb == "TAKE" || verb == "GET") // takes an item
	{
		if(currentR()->getrItems()->findName(noun) == NULL /*|| currentR()->getrItems()->findName(noun)->isTak()*/)
		{
			cout << "There is no such item in the room or cannot be taken." << endl << endl;
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
	else if (verb == "HELP")//Gives extremely useful advice
	{
		cout << "To move from one room/place to the other, type \'go\' or \'move\' and followed by a direction. Ex. \'Go North\' or \'Move South\'. ";
		cout << "There will be items in the room that you will be able to pick up or drop them. Type \'take\' or \'get\' or \'drop\' followed by the name of the item. "; 
		cout << "To interact an item with and object just type \'use\' and then followed by the name of the item. ";
		cout << "\n\nHere are a list of some extra commands: " << endl << "Examine" << endl << "Read" << endl << endl;
	}
	else
		cout << "Sorry but I don't understand." << endl;
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
		out << walker->data->getName() << endl;
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
		return firstT;
		talked=true;
	}
	else
		return afterT;
}
