#include<iostream>
#ifndef CARD_H
#define CARD_H
using namespace std;

class Card {
private:
	string suit;
	string number; // Needs to be string for Jack, Queen, etc.
	string image;
public:
	Card();
	Card(string, string); // For a specific card
	//~Card(); Deconstructor currently unnecessary, as nothing is allocated dynamically
  string getSuit();
  string getNumber();
  string getImage();
};
#endif // CARD_H

