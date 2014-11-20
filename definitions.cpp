#include "classes.h"
#include <iostream>
#include <string>
using namespace std;

Room::Room(string n/*,Room** listr,int room*/,List* rIt/*,NPC* listn[],int NPC*/,string descr)
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
	if(verb == "GO")
	{
		if(noun == "NORTH")
		{
			if (currentR()->getNorth() != NULL)
			{
				currentR(currentR()->getNorth());
				cout << "You moved North.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else if(noun == "SOUTH")
		{
			if (currentR()->getSouth() != NULL)
			{
				currentR(currentR()->getSouth());
				cout << "You moved South.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else if(noun == "EAST")
		{
			if (currentR()->getEast() != NULL)
			{
				currentR(currentR()->getEast());
				cout << "You moved East.\n" << endl << currentR()->getDescription() << endl << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
		else
		{
			if (currentR()->getWest() != NULL)
			{
				currentR(currentR()->getWest()); 
				cout << "You moved West.\n" << endl << currentR()->getDescription() << endl;
			}
			else
				cout << "You can't go there." << endl << endl;
		}
	
	}
	else if(verb == "EXAMINE")
	{
		Item* it = getInventory()->findName(noun);
		cout << it->getInfo() << endl << endl;
	}
	else if(verb == "READ")
	{
		Item* it = getInventory()->findName(noun);
		cout << it->read();
	}
	else if(verb == "USE")
	{
		if(getInventory()->findName(noun)->getTarget() != NULL)
		{
			cout << endl << endl << "On?" << endl << endl;
			string target; cin >> target;
			if(getInventory()->findName(noun)->getTarget() == currentR()->getrItems()->findName(target))
			{
				cout << currentR()->getrItems()->findName(target)->getOccur() << endl << endl;
			}

		}
	}
	else if (verb == "HELP")
	{
		cout << "You don't get any help. Help yourself."  << endl;
	}
	else
		cout << "Sorry but I don't understand." << endl;
}


bool Item::worksOn(Item* t)
{
	return t == target;
}


List::List(){
	head = NULL;
}

List::~List(){
	Node* walker = head;
    while(walker!=NULL){
        head=walker;
        walker=walker->next;
        delete head;
    }
    walker=NULL;
    head=NULL;
}

bool List::isEmpty(){
	return (head == NULL);
}

void List::add(Item* item){
    Node* walker=head;
    Node* n=new Node;
    n->data=item;
    if (head==NULL) {
        head=n;
        head->prev=NULL;
        head->next=NULL;
    }
    else{
        while (walker->next!=NULL) {
            walker=walker->next;
        }
        walker->next=n;
        n->prev=walker;
        n->next=NULL;
    }
}

int List::find(Item* value){
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

Item* List::findName(string value){
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


std::string List::listAll(){
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
}

void List::removeItem(Item* item){    // needs work
    Node* walker = head;
    while(walker->data != item)
    {
    	walker = walker->next;
    }
    Node* del = walker;
    walker->next->prev = walker->prev;
    walker->prev->next = walker->next;
    delete del;
}
