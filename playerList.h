#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include "player.h"
#include <iostream>
using namespace std;
struct PlayerNode {
	Player* thePlayer;
	PlayerNode* next;
};
class PlayerList {
private:
	PlayerNode* head;
public:
	PlayerList();
	~PlayerList();
	void append(Player *);
	PlayerNode* getHead();
};

PlayerList::PlayerList() {
	head = nullptr;
}

PlayerList::~PlayerList() {
	PlayerNode *nodePtr;
	PlayerNode *next;
	
	nodePtr = head;
	
	while (nodePtr != nullptr) {
		next = nodePtr->next;
		delete nodePtr;
		nodePtr = next;
	}
}

void PlayerList::append(Player *newPlayer) {
	// Adds num to the end of the list
	PlayerNode *newNode;
	PlayerNode *nodePtr;
	
	newNode = new PlayerNode;
	newNode->thePlayer = newPlayer;
	newNode->next = nullptr;
	
	if(!head)
		head = newNode;
	else {
		nodePtr = head;
		while (nodePtr->next)
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
	}
}

PlayerNode* PlayerList::getHead() {
	return head;
}
#endif