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
			
			if(currentR()->getObstacle()->prevent() == "NORTH")
				cout << currentR()->getObstacle()->getpInfo() << endl << endl;
			else if (currentR()->getNorth() != NULL)//Check if NULL
			{
				currentR(currentR()->getNorth());//Sets current player location to north location
				cout << "You moved North.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else//If no location!
				cout << "There's nothing there." << endl << endl;
		}
		else if(noun == "SOUTH")
		{
			if (currentR()->getSouth() != NULL)
			{
				currentR(currentR()->getSouth());
				cout << "You moved South.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "There's nothing there." << endl << endl;
		}
		else if(noun == "EAST")
		{
			if (currentR()->getEast() != NULL)
			{
				currentR(currentR()->getEast());
				cout << "You moved East.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else
				cout << "There's nothing there." << endl << endl;
		}
		else
		{
			if (currentR()->getWest() != NULL)
			{
				currentR(currentR()->getWest()); 
				cout << "You moved West.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "There's nothing there." << endl << endl;
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
				cout << "On? ";
				string target = ""; cin >> target; cout << endl; 
				toUpper(target);
				if(getInventory()->findName(noun)->getTarget()->getName() == target)
				{
					cout << currentR()->getObstacle()->getOccur() << endl;
					currentR()->getObstacle()->prevent("nothing");
				}
				else
				{
					cout << "Cannot use " << noun << " on " << target << ".\n\n";
				}

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
			currentR()->getrItems()->removeItem(currentR()->getrItems()->findName(noun));
			cout << noun << " is now in your Inventory." << endl << endl;
		}
	}
	else if (verb == "HELP")//Gives extremely useful advice
	{
		cout << "You don't get any help. Help yourself."  << endl;
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


/*std::string List::listAll()//Lists all item in list
{
	std::string all ="";
	Node* walker = head;
    while (walker!=NULL) {
		
		if(walker->next==NULL){
			if(walker->prev==NULL){
					all += walker->data->getName();
			}
			else if(all == "")
				all += walker->data->getName();
			else
				all += "and " + walker->data->getName();
		}
		else
			all += walker->data->getName() + ", ";
		
		
		walker=walker->next;
	}
    return all;
}*/

void List::removeItem(Item* item){    // maybe works?
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
