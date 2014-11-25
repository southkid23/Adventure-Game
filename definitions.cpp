#include "classes.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void PressEnterToContinue()
  {
	cout << "\nPRESS ENTER TO CONTINUE... ";
	cin.sync();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

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
	roomNPC(cout);cout << "" << endl;
	hasBeen = true;
}

ostream& Room::roomNPC(ostream& out)
{
	if(npc == NULL)
		out << "THERE IS NO-ONE IN THIS AREA.\n";
	else
	{
		out << "PEOPLE IN THIS AREA:\n" << "- " << npc->getName() << endl;
	}
	return out;
}

ostream& Room::roomitems(ostream& out)
{
	if(!rItems->isEmpty())
	{
		out << "ITEM(S) IN AREA:\n";
		rItems->listAll(out);out << "";
	}
	else
		out << "THERE IS NOTHING IN THIS AREA." << endl;
	return out;
}

void Player::doAction(string verb, string noun)
{
	//cout << "verb is " << verb << endl << "Noun is " << noun << endl;
	if(verb == "GO")
	{
		while(noun == "")
		{
			cout << "GO WHERE?\n";cin >> noun;toUpper(noun);
		}
		if(noun == "BACK")
			cout << "OKAY...\n\n";
		else if(noun == "NORTH")//To Go North//Same for south,east and west
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
		if(getInventory()->isEmpty())
			cout << "YOU DO NOT HAVE ANYTHING TO EXAMINE.\n\n";
		else
		{
			while(noun == "")
			{
				cout << "EXAMINE WHAT?\n";
				if(!getInventory()->isEmpty())
				{
					getInventory()->listAll(cout); cout << "";
				}
				if(!currentR()->getrItems()->isEmpty())
				{
					currentR()->getrItems()->listAll(cout); cout << "";
				}
				cout << endl;
				cin >> noun;toUpper(noun);cout << endl;
			}
			if(noun == "BACK")
				cout << "OKAY...\n\n";
			else if(getInventory()->find(noun) != 0)
				cout << getInventory()->findName(noun)->getInfo() << endl;
			else if(currentR()->getrItems()->find(noun) != 0)
				cout << currentR()->getrItems()->findName(noun)->getInfo() << endl;
			else
				cout << "NO SUCH ITEM EXISTS." << endl;
			if(currentR()->getrItems()->find(noun) != 0 || getInventory()->find(noun) != 0)
				cout << endl;
		}
	}
	else if(verb == "READ")//Read reads an item if it is a "book"
	{
		while(noun == "")
		{
			cout << "READ WHAT?\n";getInventory()->listAll(cout); cout << "\n";
			cin >> noun;toUpper(noun);
		}
		if(noun == "BACK")
			cout << "OKAY...\n\n";
		else if(getInventory()->find(noun) == 0)
			cout << "YOU DO NOT HAVE THIS ITEM.";
		if(!getInventory()->findName(noun)->isRead())
			cout << noun << " CANNOT BE READ.";
		else
		{
			Item* it = getInventory()->findName(noun);
			cout << it->read();
		}
	}
	else if(verb == "USE")//Used to carry out actions on targets
	{
		if(getInventory()->isEmpty())
			cout << "YOU DO NOT HAVE ANYTHING TO USE.\n\n";
		else
		{
			while(noun == "")
			{
				cout << "USE WHAT?\n";getInventory()->listAll(cout);cout << "\n";
				cin >> noun;toUpper(noun);
			}
			if(noun == "BACK")
				cout << "OKAY...\n\n";
			else if(getInventory()->find(noun) != 0)
			{	
				if(getInventory()->findName(noun)->getTarget() != NULL)
				{
					cout << "\nUSE " << noun << " ON WHAT?\n\n";
					string target = ""; cin >> target; cout << endl; 
					toUpper(target);
	
					if(currentR()->getObstacleN() != NULL && (currentR()->getObstacleN()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
					{
						cout << currentR()->getObstacleN()->getOccur() << endl; getInventory()->removeItem(noun);
						delete currentR()->getObstacleN(); currentR()->setObstacleN(NULL);
					}
					else if(currentR()->getObstacleE() != NULL && (currentR()->getObstacleE()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
					{
						cout << currentR()->getObstacleE()->getOccur() << endl; getInventory()->removeItem(noun);
						delete currentR()->getObstacleE(); currentR()->setObstacleE(NULL);
					}
					else if(currentR()->getObstacleS() != NULL && (currentR()->getObstacleS()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
					{
						cout << currentR()->getObstacleS()->getOccur() << endl; getInventory()->removeItem(noun);
						delete currentR()->getObstacleS(); currentR()->setObstacleS(NULL);
					}

					else if(currentR()->getObstacleW() != NULL && (currentR()->getObstacleW()->getName() == target && getInventory()->findName(noun)->getTarget()->getName() == target))
					{
						cout << currentR()->getObstacleW()->getOccur() << endl; getInventory()->removeItem(noun);
						delete currentR()->getObstacleW(); currentR()->setObstacleW(NULL);
					}		

					else
					{
						cout << "CANNOT USE " << noun << " ON " << target << ".\n";
					}

				}
				else if(getInventory()->findName(noun)->getiTarget() != NULL)
				{
					cout << "\nUSE " << noun << " ON WHAT?\n\n";
					if(!getInventory()->isEmpty())
					{
						getInventory()->listAll(cout); cout << "";
					}
					if(!currentR()->getrItems()->isEmpty())
					{
						currentR()->getrItems()->listAll(cout); cout << "";
					}
					cout << endl;
					string target = ""; cin >> target; cout << endl; 
					toUpper(target);
					if(getInventory()->find(target) == 0 && currentR()->getrItems()->find(target) == 0)
						cout << target << " IS NOT IN YOUR INVENTORY OR ROOM" << endl << endl;
					else if(target == noun)
						cout << "YOU CANNOT USE " << noun << " ON ITSELF.\n";
					else if(target == getInventory()->findName(noun)->getiTarget()->getName())
					{
						if(getInventory()->find(target) != 0)
						{
							cout << "YOU USE " << noun << " ON " << target << ".";
							cout << "YOU NOW HAVE " << getInventory()->findName(noun)->getProduct()->getName() << ".\n ";
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
					}
					else
						cout << "YOU CAN'T USE " << noun << " ON " << target << endl;
				}
				else
					cout << endl << noun << " CANNOT BE USED." << ".\n\n";
			}
			else
				cout << "\nYOU DON'T HAVE A(N) " << noun << " TO USE.\n";
		}
	}
	else if(verb == "TAKE") // takes an item
	{
		while(noun == "")
		{
			cout << "TAKE WHAT?\n"; currentR()->getrItems()->listAll(cout);cout << "\n";
			cin >> noun;cout << endl;toUpper(noun);
		}
		if(noun == "BACK")
			cout << "OKAY...\n\n";
		else if(currentR()->getrItems()->findName(noun) == NULL || !currentR()->getrItems()->findName(noun)->isTak())
		{
			cout << "THERE IS NO SUCH ITEM IN THE ROOM OR CANNOT BE TAKEN." << endl;currentR()->roomitems(cout);cout << "";
		}
		else
		{	
			getInventory()->add(currentR()->getrItems()->findName(noun));
			currentR()->getrItems()->removeItem(noun);
			cout << noun << " IS NOW IN YOUR INVENTORY." << endl;
		}
	}
	else if(verb == "TALK")
	{
		while(noun == "")
		{
			cout << "TALK TO WHO?\n- " << currentR()->getNPC()->getName() << endl << endl;
			cin >> noun;toUpper(noun);
		}
		if(noun == "BACK")
			cout << "OKAY...\n\n";
		else if(currentR()->getNPC() != NULL)
		{
			if(currentR()->getNPC()->getName() == noun)
			{
				cout << currentR()->getNPC()->talk() << endl;
			}
			else
			{
				cout << "THERE IS NO ONE BY THE NAME OF " << noun << " IN HERE.\n\n";
			}
		}
		else
		{
			cout << "THERE IS NO ONE TO SPEAK TO.\n\n";
		}
	}
	else if(verb == "GIVE")
	{
		if(getInventory()->isEmpty())
			cout << "YOU DO NOT HAVE ANYTHING TO GIVE.\n\n";
		else
		{
			while(noun == "")
			{
				cout << "GIVE WHAT?\n";getInventory()->listAll(cout);cout << "\n";
				cin >> noun;toUpper(noun);
			}	
			if(noun == "BACK")
				cout << "OKAY...\n\n";
			else if(getInventory()->find(noun) != 0)
			{
				if(getInventory()->findName(noun)->getnTarget() == NULL)
					cout << endl << noun << " CANNOT BE GIVEN.\n";
				else
				{
					cout << "\nGIVE " << noun << " TO?\n- " << currentR()->getNPC()->getName() << endl << endl;
					string target = ""; cin >> target;
					toUpper(target);
					if(target != currentR()->getNPC()->getName())
						cout << "\nTHER IS NO " << target << " IN THIS ROOM.\n";
					else if(getInventory()->findName(noun)->getnTarget()->getName() == target && currentR()->getNPC()->getName() == target)
					{
						cout << endl << currentR()->getNPC()->getOccur();
						getInventory()->removeItem(noun);
						getInventory()->add(currentR()->getNPC()->getHas());
					}
					else
						cout << "\nCANNOT GIVE " << noun << " TO " << target << ".\n";
				}
			}
			else
				cout << "\nYOU DO NOT HAVE A " << noun << " TO GIVE.\n";
		}
	}
	else if (verb == "HELP")//Gives extremely useful advice
	{
		cout << "THIS GAME ACCEPTS A MAX OF TWO WORD COMMANDS, FOR EXAMPLE \"TAKE ITEM\" OR \"GO\nSOUTH\". ONLY COMMANDS LISTED IN THE LIST BELLOW CAN BE USED.\n";
		cout << "COMMAND LIST: \n- GO (NORTH,SOUTH,EAST,WEST)\n- TAKE\n- DROP\n- USE\n- EXAMINE\n- TALK\n- GIVE\n- BACK\n\n";//PressEnterToContinue();
	}
	else if(verb == "LIST")
	{
		while(noun == "")
		{
			cout << "\nINVENTORY OR ROOM_ITEMS?\n\n";
			cin >> noun;toUpper(noun);cout << endl;
		}
		if(noun == "BACK")
			cout << "OKAY...\n\n";
		else if(noun == "INVENTORY")
		{
			getInventory()->listAll(cout);cout << "\n";
		}
		else if(noun == "ROOM_ITEMS")
		{
			currentR()->getrItems()->listAll(cout);cout << "\n";
		}
	}
	else if(verb == "DROP")
	{
		if(getInventory()->isEmpty())
			cout << "YOU DO NOT HAVE ANYTHING TO DROP.\n\n";
		else
		{
			while(noun == "")
			{
				cout << "DROP WHAT?\n";getInventory()->listAll(cout);cout << "\n";
				cin >> noun;toUpper(noun);
			}
			if(noun == "BACK")
				cout << "OKAY...\n\n";
			else if(getInventory()->find(noun) != 0)
			{
				cout << "YOU HAVE DROPPED " << noun << ".\n";
				currentR()->getrItems()->add(getInventory()->findName(noun));
				getInventory()->removeItem(noun);
			}
			else
				cout << "ITEM NOT IN INVENTORY.\n";
		}
	}
	else
		cout << "SORRY BUT I DO NOT UNDERSTAND.\n" << endl;
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
		if(head == NULL)
			out << "- NOTHING TO SHOW.\n";
	while(walker != NULL)
	{
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
