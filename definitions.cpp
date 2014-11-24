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
	hasBeen = false;
}

void Room::enter()
{
	if(!entered())
		cout << getDescription() << endl << endl;
	cout << "This room contains:\n"; 
	rItems->listAll(cout);cout << "" << endl << endl;
	hasBeen = true;
}

/*ostream& Room::roomitems(ostream& out)
{
	out << "Items in the room:";
	for(int i = 0;i < nItems;i++)
	{
		listItems[i]->render(out);out<<"";
		out << "(" << i << ")" << endl;
	}
}

ostream& Room::roomNPC(ostream& out)
{
	out << "People in the room:";
	for(int i = 0;i < nItems;i++)
	{
		listNPC[i]->render(out);out<<"";
		out << "(" << i << ")" << endl;
	}
}

bool Room::entered()
{
	return hasBeen;
}

void Room::enter()
{
	if(!entered)
	{
		cout << "You are in " << name << ". " << description << endl << roomNPC(cout) << roomitems(cout);
		hasBeen = true;
	}
	else
		cout << "You are back in " << name << "." << endl << roomNPC(cout) << roomitems(cout);
}
*/

void Player::doAction(string verb, string noun)
{
	//cout << "verb is " << verb << endl << "Noun is " << noun << endl;
	if(verb == "GO" || verb == "MOVE")
	{

		if(noun == "NORTH")//To Go North//Same for south,east and west
		{
			if(currentR()->getObstacleN() != NULL)
			{	
				if(currentR()->getObstacleN()->prevent() == "NORTH")
					cout << currentR()->getObstacleN()->getpInfo() << endl << endl;
			}	
			else if (currentR()->getNorth() != NULL)//Check if NULL
			{
				currentR(currentR()->getNorth());//Sets current player location to north location
				cout << "You moved North.\n" << endl; currentR()->enter();// << endl << endl;
			}
			else//If no location!
				cout << "There's nothing there." << endl << endl;
		}
		else if(noun == "SOUTH")
		{
			if(currentR()->getObstacleS() != NULL)
			{	
				if(currentR()->getObstacleS()->prevent() == "SOUTH")
					cout << currentR()->getObstacleS()->getpInfo() << endl << endl;
			}	
			else if (currentR()->getSouth() != NULL)
			{
				currentR(currentR()->getSouth());
				cout << "You moved South.\n" << endl; currentR()->enter();// << endl << endl;
			}
			else
				cout << "There's nothing there." << endl << endl;
		}
		else if(noun == "EAST")
		{
			if(currentR()->getObstacleE()->prevent() == "EAST")
				cout << currentR()->getObstacleE()->getpInfo() << endl << endl;
			else if (currentR()->getEast() != NULL)
			{
				currentR(currentR()->getEast());
				cout << "You moved East.\n" << endl; currentR()->enter();
			}
			else
				cout << "There's nothing there." << endl << endl;
		}
		else
		{
			if(currentR()->getObstacleW()->prevent() == "WEST")
				cout << currentR()->getObstacleW()->getpInfo() << endl << endl;
			else if (currentR()->getWest() != NULL)
			{
				currentR(currentR()->getWest()); 
				cout << "You moved West.\n" << endl; currentR()->enter();
			}
			else
				cout << "There's nothing there." << endl << endl;
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
			cout << "No " << noun << " to examine.\n";
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
				cout << "On? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
				if(currentR()->getObstacleN() != NULL)
				{	
					if(currentR()->getObstacleN()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target)
					{
						cout << currentR()->getObstacleN()->getOccur() << endl;
						delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
					}
					else
						cout << "Cannot use " << noun << " on " << target << ".\n";
				}
				else if(currentR()->getObstacleE() != NULL)	
				{
					if(currentR()->getObstacleE()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target)
					{
						cout << currentR()->getObstacleE()->getOccur() << endl;
						delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
					}
					else
						cout << "Cannot use " << noun << " on " << target << ".\n";
				}
				else if(currentR()->getObstacleS() != NULL)
				{	
					if(currentR()->getObstacleS()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target)
					{
						cout << currentR()->getObstacleS()->getOccur() << endl;
						delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
					}
					else
							cout << "Cannot use " << noun << " on " << target << ".\n";
				}
				else if(currentR()->getObstacleW() != NULL)
				{	
					if(currentR()->getObstacleW()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target)
					{
						cout << currentR()->getObstacleW()->getOccur() << endl;
						delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
					}
					else
							cout << "Cannot use " << noun << " on " << target << ".\n";
				}
				else
				{
					cout << "Cannot use " << noun << " on " << target << ".\n\n";
				}

			}
			else
				cout << noun << " cannot be used.\n\n";
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
			currentR()->getrItems()->removeItem(currentR()->getrItems()->findName(noun));
			cout << noun << " is now in your Inventory." << endl << endl;
		}
	}
	else if(verb == "GIVE")
	{
		if(getInventory()->findName(noun) != NULL)
		{
			if(getInventory()->findName(noun)->getnTarget() != NULL)
			{
				cout << "To? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
				if(getInventory()->findName(noun)->getnTarget()->getName() == target && currentR()->getNPC()->getName() == target)
				{
					cout << currentR()->getNPC()->getOccur(); cout << noun;
					getInventory()->removeItem(getInventory()->findName(noun));
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
    if (head==NULL) {
        return 0;
    }
    while (walker!=NULL) {
        count++;
        if (walker->data==value) {
            break;
        }
        if (walker->next==NULL) {
            return 0;
        }
        walker=walker->next;
    }
    return count;
}

Item* List::findName(string value)
{
    Node* walker=head;
    if (walker==NULL) {
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
		out << walker->data->getName() << endl;
		walker = walker->next;
	}
	return out;
}

void List::removeItem(Item* item)
{    // maybe works?
    Node* walker = head;
    Node* walker2 = head;
    if(walker->data == item)
    {
    	Node* del = walker;
    	head = walker->next;
    	delete del;
    }
    else
    {
	    walker = walker->next;
	    while(walker->data != item)
	    {
	    	walker2 = walker;
	    	walker = walker->next;
	    	
	    }
	    Node* del = walker;
	    walker2->next = walker->next;
	    delete del;
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
