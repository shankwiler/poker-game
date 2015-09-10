#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include "player.h"
#include <iostream>
using namespace std;

struct PlayerNode { 	// new data type for storing Player info and pointer to another node
   	Player* thePlayer;
   	PlayerNode* next;
};
class PlayerList {
private:
   	PlayerNode* head;   // indicates the beginning of the linked list
   	int numPlayer;  	// stores the number of nodes in the linked list
public:
   	PlayerList();           	// constructor
   	~PlayerList();          	// destructor
   	void append(Player *);  	// add a player
   	void deleteNode(char*); 	// unlink a player
   	void dropPlayer();      	// delete a player
   	PlayerNode* getHead();  	// return the pointer to the beginning of the list
   	void setHead(PlayerNode*);  // set the head to a list
   	void showPlayer() const;	// show information of each player in the list
   	void clearInRound();    	// reset the check status of every player
   	void clearCheckMoney(); 	// reset the amount of money checked
   	bool allCheck() const;  	// checks if every player in the round checked or not
   	void copyList(PlayerList*); // copies all the nodes into another list
   	void makeRingList();    	// make a list circular so that the last node points to the first node
   	int getNumPlayer() const	// return the number of player in the list
   	{
   	    return numPlayer;
   	}
   	void setNumPlayer(int n)	// setting the number of player in the list
   	{
   	    numPlayer = n;
   	}
};


PlayerList::PlayerList() // when a list is created, the head should point to null pointer because there is zero node
{
   	head = nullptr;
   	numPlayer = 0;
}

PlayerList::~PlayerList() { // delete each player left in the list
   	PlayerNode *nodePtr;
   	PlayerNode *nextNode;

   	nodePtr = head; // starting from the head

	//deleting a node for each iteration
   	for(int i = 0; i< numPlayer; i++) {
         	nextNode = nodePtr->next;
         	delete nodePtr;
         	nodePtr = nextNode;
   	}
}

void PlayerList::append(Player *newPlayer) {
   	// Add player to the end of the list
   	PlayerNode *newNode;
   	PlayerNode *nodePtr;

   	newNode = new PlayerNode; // new player node to add to the list
   	newNode->thePlayer = newPlayer;
   	newNode->next = nullptr; // because this is the last node, it is pointing to nothing

   	if(!head)       	// if there was nothing at the first place,
         	head = newNode; // head is pointing to that node
   	else {          	// otherwise
         	nodePtr = head;
         	while (nodePtr->next)   // traverse through the list to get the end of the list
                	nodePtr = nodePtr->next;
         	nodePtr->next = newNode;	// and link the newNode
   	}
   	numPlayer++;	// a player is added to the list and the number of player in the list is incremented by 1
}

void PlayerList::dropPlayer() // drops a player from the game if the player has no money
{
	PlayerNode* nodePtr = nullptr;
	PlayerNode* previousNode = nullptr;
	bool good = false;  // checks if every player has any money

	do
	{
    	nodePtr = head;
    	if(head->thePlayer->getMoney() == 0) // if the first player in the list has no money
    	{
        	cout << "Player "<< nodePtr->thePlayer->getID() << " is dropped." << endl;
        	nodePtr = nodePtr->next;
        	delete head;        	// delete the node from the list
        	head = nodePtr;
        	numPlayer--;        	// number of player is decremented by 1.
    	}
    	else // if the player other than the first player has no money
    	{
    	    while(nodePtr && nodePtr->thePlayer->getMoney() != 0)   // traverse through the list until there is a player with 0 money
        	{
            	previousNode = nodePtr;
            	nodePtr = nodePtr->next;	// go to next node
        	}
        	if(nodePtr) // if there is a player with 0 money
        	{
            	cout << "Player "<< nodePtr->thePlayer->getID() << " is dropped." << endl;
            	previousNode->next = nodePtr->next;
            	delete nodePtr; 	// delete from the list
            	numPlayer--;    	// number of player decremented by 1
        	}
        	else
            	good = true;    	// if every player has enought money to move on,
   	 }
	}while(!good);              	// exit the function
	cout << endl;
}

void PlayerList::deleteNode(char* id)   // instead of dropping player from the list, this function temporarily unlink the player from the list
{
	PlayerNode* nodePtr = head;
	PlayerNode* previousNode = nullptr;

	if(head->thePlayer->getID() == id)
	{
    	nodePtr = nodePtr->next;
    	head = nodePtr;
	}
	else
	{
    	while(nodePtr && nodePtr->thePlayer->getID() != id)     //find the player with the id passed as a parameter
    	{
        	previousNode = nodePtr;
        	nodePtr = nodePtr->next;
    	}
    	if(nodePtr) 	// if there is a player whose id is identical, unlink the player from the list
    	{
        	previousNode->next = nodePtr->next;
    	}
	}
	numPlayer--;    	// number of player decremented by 1
}

PlayerNode* PlayerList::getHead() {
   	return head;
}

void PlayerList::setHead(PlayerNode* n)
{
	head = n;
}

void PlayerList::showPlayer() const 	// accesses to each player node to get the info of each player
{
	PlayerNode* nodePtr = head;
	for(int i = 0; i < numPlayer; i++)
	{
    	nodePtr->thePlayer->status(); // show status
    	nodePtr = nodePtr->next;
	}
}

void PlayerList::clearInRound()
{
	PlayerNode* nodePtr = head;
	for(int i = 0; i < numPlayer; i++)
	{
        nodePtr->thePlayer->setInRound(false); // every player in the list is not in the round
    	nodePtr = nodePtr->next;
	}
}

void PlayerList::clearCheckMoney()
{
	PlayerNode* nodePtr = head;
	for(int i = 0; i < numPlayer; i++)
	{
        nodePtr->thePlayer->setMoneyChecked(0); 	//sets every player's money checked 0.
    	nodePtr = nodePtr->next;
	}
}

bool PlayerList::allCheck() const
{
	PlayerNode* nodePtr = head;
	for(int i = 0; i < numPlayer; i++)
	{
        if(!nodePtr->thePlayer->getInRound())   //if one player is not in the round, not everyone in the game has checked.
        	return false;	                   // so it returns false
    	nodePtr = nodePtr->next;
	}
	return true;
}

void PlayerList::copyList(PlayerList* list)
{
	PlayerNode* nodePtr = head;
	while(nodePtr)
	{
        list->append(nodePtr->thePlayer);   	//add the nodes in the original list into the new list.
    	nodePtr = nodePtr->next;
	}
}

void PlayerList::makeRingList()
{
	PlayerNode* nodePtr = head;
	while(nodePtr->next)        	//traverse to the last node
    	nodePtr = nodePtr->next;
	nodePtr->next = head;       	// link the last node to the head
}

#endif
