#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <cstdlib>
#include "card.h"
using namespace std;

class Player{

private:
    char* id;   	// 4 digits id
    Card *card1;	// Card objects
    Card *card2;
    int money;  	// balance
    bool inRound;   // checks if the player is in the round or not
    double moneyChecked; // amount of money checked during betting

public:
    Player();   // constructor
    ~Player();  // destructor
    void setCard1( Card *); 	// assign a pointer to a Card object to card1
    void setCard2( Card *); 	// assign a pointer to a Card object to card2
    Card* getCard1();            	// get the card1 pointer
    Card* getCard2();            	// get the card 2 pointer
    void setMoney(int);     	// set balance to a specific number
    void addMoney(int);     	// add change in money
    int getMoneyChecked() const;	// return the amount of money checked during betting
    int getMoney() const;   	// return the amount of money the player has
    char* getID() const;    	// return player id
    bool getInRound() const 	// return player status
    {
    	return inRound;
    }
    void status() const;
    void setInRound(bool);
    void setMoneyChecked(int);
	void addMoneyChecked(int);
    void ShowCard(Card*) const;
};

Player::Player()
{
    id = new char[5]; //creating dynamically
    for(int i = 0; i < 4; i++)
    	id[i] = rand()%10+48; // id of 4-digits
    id[4] = '\0';       //null-terminated character array
    card1 = nullptr;
    card2 = nullptr;
    money = 100;    	// $100 is given to each player initially
    moneyChecked = 0;   // money put by the player to call the highest bet
    inRound = false;	// if the player is in the round or not
}

Player::~Player() //destructor
{
    delete[] id;	//free dynamically allocated memory resource
}

void Player::setCard1( Card * card)
{
    card1 = card;   // set the first card of the player
}

void Player::setCard2( Card * card)
{
    card2 = card;   // set the second card of the player
}

Card* Player::getCard1() {
   	return card1;   // return the pointer to the first card
}

Card* Player::getCard2() {
   	return card2;   // return the pointer to the second card
}

void Player::setMoney(int mon)
{
    money = mon;	// set the money at a specific value
}

void Player::setMoneyChecked(int mon)
{
    moneyChecked = mon; // set the money checked at a specific value
}

void Player::addMoneyChecked(int mon)
{
    moneyChecked += mon;	// add an amount of money checked
}

void Player::addMoney(int mon)
{
    money += mon;       	// add the change in money of the player
}

int Player::getMoneyChecked() const
{
    return moneyChecked;	// reutnr the amount of money checked
}

int Player::getMoney() const
{
    return money;       	// return the amount of money
}

char* Player::getID() const
{
    return id;          	// return the player's ID.
}

void Player::status() const 	// display a player's status
{
    cout << "id: " << id << endl;
    cout << "money: " << money << endl;
    cout << "\t\tCard1: "; ShowCard(card1);
    cout << "\t\tCard2: "; ShowCard(card2);
    cout << "Money Checked: " << moneyChecked << endl << endl;
}

void Player::setInRound(bool n) // set if the player is in the game or not
{
    inRound = n;
}

void Player::ShowCard(Card* c) const	// display the information of a specific card
{
    switch(c->number)   // display number
    {
    case 1:
    	cout << "Ace";
    	break;
    case 11:
    	cout << "Jack";
    	break;
    case 12:
    	cout << "Queen";
    	break;
    case 13:
    	cout << "King";
    	break;
    default:
    	cout << c->number;
    }
    cout << " ";

    switch(c->suit) 	//display suit
    {
    case 0:
    	cout << "Spade";
    	break;
    case 1:
    	cout << "Heart";
    	break;
    case 2:
    	cout << "Diamond";
    	break;
    case 3:
    	cout << "Club";
    	break;
    }
    cout <<endl;

}
#endif // PLAYER_H
