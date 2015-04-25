
#include<iostream>
#include <allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include "card.h"
using namespace std;

class Player{

private:

    Card *card1;

    Card *card2;

    double money;

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
card1 = new Card;
card2 = new Card;
money = 100;
}

void Player::setCard1( Card * card)
{
card1 = card;
}

void Player::setCard2( Card * card)
{
card2 = card;
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


