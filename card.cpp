#include <iostream>
#include <string>
#include <cstdlib> // For random
#include <time.h>
#include "card.h"
using namespace std;

Card::Card() {
	int randomSuit;
	int randomNumber;

	// Assign one of four possible suits
	randomSuit = rand() % 4 + 1;  // random values 1-4
	switch(randomSuit) {
		case 1:
			suit = "club";
			break;
		case 2:
			suit = "diamond";
			break;
		case 3:
			suit = "heart";
			break;
		case 4:
			suit = "spade";
			break;
	}

	// Assign one of thirteen possible numbers
	randomNumber = rand() % 13 + 1; // random values 1-13
	if (randomNumber < 10) {
        number = randomNumber+48;
	}
	else if (randomNumber == 10)
        number = "10";
	else if (randomNumber == 11)
		number = "jack";
	else if (randomNumber == 12)
		number = "queen";
	else
		number = "king";

	// Assign the image location
	// Image files follow the format of [c,h,d,s][1-10,j,q,k].png
	image = "cards_png\\" + suit.substr(0,1);
	if (number == "10")
		image.append("10");
	else
		image.append(number.substr(0,1));
	image.append(".png");
}

Card::Card(string newSuit, string newNumber) {
	suit = newSuit;
	number = newNumber;

	// Assign the image location
	// Image files follow the format of [c,h,d,s][1-10,j,q,k].png
	image = "cards_png/" + suit.substr(0,1);
	if (number == "10")
		image.append("10");
	else
		image.append(number.substr(0,1));
	image.append(".png");
}

string Card::getSuit() {
	return suit;
}

string Card::getNumber() {
	return number;
}

string Card::getImage() {
	return image;
}

