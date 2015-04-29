#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include "card.h"
using namespace std;

class Player{
private:
	Card *card1;
	Card *card2;
	double money;
	bool inRound; // Keeps track of if the player has folded or is in the round
public:
	Player();
	void setCard1( Card *);
	void setCard2( Card *);
	void setMoney(double);
	Card * getCard1();
	Card * getCard2();
	double getMoney();
};

Player::Player()
{
	//card1 = new Card;
	//card2 = new Card;
	money = 100;
	inRound = true;
}

void Player::setCard1( Card * newCard)
{
	card1 = newCard;
}

void Player::setCard2( Card * newCard)
{
	card2 = newCard;
}

void Player::setMoney(double mon)
{
	money = mon;
}

Card* Player::getCard1(){
	return card1;
}
Card* Player::getCard2(){
	return card2;
}
#endif

