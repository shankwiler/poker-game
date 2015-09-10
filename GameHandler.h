#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include "card.h"
#include "playerList.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <sstream>
using namespace std;

class GameHandler
{
private:
	Card* usedCard[13];   // array of cards that can be drawn in a round. 4 Players max
	Card* tableCard[5];   // array of community cards
	int cnt;			  // counting the number of total cards drawn
	int tableCnt;		 // counting the number of community cards drawn
	double pot;			  // total money in the pot for a round
	PlayerList list;	  // list of the players throughout the game
	PlayerList roundList; // list of the players throughout one round
		Player* winners[4];	// list of the winners of the round
		int numWinners;
		int winningHand[6];	// array of the winning hand
public:
	GameHandler()
	{
		cnt = 0;
		tableCnt = 0;
		pot = 0;
				numWinners = 0;
	}
	~GameHandler()  // deletes dynamically allocated Card objectts
	{
		for(int i = 0 ; i < cnt; i++)
			delete usedCard[i];
	}
	PlayerList* getList()		   // return the pointer to the original Player list
	{
		return &list;
	}
	PlayerList* getRoundList()	  // return the pointer to the round Player list
	{
		return &roundList;
	}
	bool checkDeck() const;		 // checks if a randomly-generated card is already drawn or not
	Card* newCard();				// generates random card
	void appendPlayer(Player*);	 // adds a player to the linked list
	bool betting();				 // initiates betting
	void shuffleDeck();			 // resets the deck after each round
	void confirmRoundList();		// to make a circular list of Players
	void drawTableCard();		   // draws a community card
	void showTableCard();		   // shows all the community cards
	void showdown();				// checks the hands of the players in the round after betting
	void setDefault();			  // make every counter variables set to zero
	void giveMoney();			   // give money to the winner
		void sortCardNumber (Card* [], int); // sorts cards in an array of card pointers by their number
		void integerSort(int [], int); // sorts an array of integers
		void assignValue(Card* [], int, int []); // takes an array of card pointers, its size, and assign a value...
			// ...to an array passed to it
		void compareValues(PlayerNode*); // compare the values of the hands of each player, determine winner
		void clearWinners();
		void singleWinner(Player*);
		Player* getWinner(int); // get the winner at a specific index
		int getNumWinners(); // return the number of winners
		string cardToString(int); // return a string of the card "number" based on its integer
		void showHand(); // show the winning hand

};
Card* GameHandler::newCard() {
	Card *newCard = new Card;   // creates a Card object dynamically
	int randomSuit;			 // random number for suit
	int randomNumber;		   // random number for number
	bool used = false;		  // Keeps track of whether the card is used already or not

	do
	{
		newCard->suit = rand() % 4;		  // random values 0-3
		newCard->number = rand() % 13 + 1;   // random values 1-13

		// Check if that card has already been created
		// Traverse the linked list, checking each node if it's the same as the new random card
		for (int i = 0; i < cnt; i++) {
			if (usedCard[i]->suit == newCard->suit && usedCard[i]->number == newCard->number) {
				used = true;
				break;
			}
			else
				used = false;
		}
	}while(used);   // iterates until the card drawn has not been drawn before


	// creating a directory path to the image file
	newCard->image = "cards_png/";

	// add the character referring to the suit
	switch(newCard->suit) {
		case 0:
			newCard->image.append("s");
			break;
		case 1:
			newCard->image.append("h");
			break;
		case 2:
			newCard->image.append("d");
			break;
		case 3:
			newCard->image.append("c");
			break;
	}

	// add the number
	if (newCard->number < 11) // if it's less than 11, convert to string and append it
	{
		std::ostringstream ss;
		ss << newCard->number;
		newCard->image.append(ss.str());
	}
	else if(newCard->number == 11) // if it's jack
		newCard->image.append("j");
	else if(newCard->number == 12) // if it's queen
		newCard->image.append("q");
	else if(newCard->number == 13) // if it's king
		newCard->image.append("k");

	newCard->image.append(".png");

	usedCard[cnt] = newCard; // Append the newCard to the usedCard array
	cnt++;				   // Increase the count of the usedCard array
	return newCard;		  // return the pointer to the drawn card
}

void GameHandler::appendPlayer(Player* p)
{
	list.append(p);
}

bool GameHandler::betting()
{
	PlayerNode* nodePtr = roundList.getHead();
	int moneyBet = 0;   // highest bet during betting
	int userChoice;	 // for user input
	list.clearCheckMoney(); //when the betting starts, everyone has put $0
	list.clearInRound();	//when the betting starts, no one has checked yet, therefore not in the round until they make decision
	do
	{
OPTION: // option reference
		cout << "\t\tPlayer ID: " << nodePtr->thePlayer->getID() << endl;
		cout << "\t--------BETTING ACTION--------" << endl;
		cout << "\t1. CHECK(CALL)" << endl;
		cout << "\t2. BET(RAISE BY 5 DOLLARS)" << endl;
		cout << "\t3. FOLD" << endl;
		cout << "\t------------------------------" << endl;
		cout << "\tChoose an action: "; cin >> userChoice;

		switch(userChoice)
		{
		case 1: // check(call)
			if(moneyBet == nodePtr->thePlayer->getMoneyChecked()){
				cout << "player " << nodePtr->thePlayer->getID() << " is skipped" << endl;
			}
			else if(nodePtr->thePlayer->getMoney() < moneyBet - nodePtr->thePlayer->getMoneyChecked()) // when a player does not have $5 to call, the player must put all the money.
			{
				cout << "$" << nodePtr->thePlayer->getMoney() << " put into the pot." << endl << endl;
				pot += nodePtr->thePlayer->getMoney();  // money goes into the pot
				nodePtr->thePlayer->setMoney(0);		// now the player does not have any money
				nodePtr->thePlayer->addMoneyChecked(moneyBet - nodePtr->thePlayer->getMoneyChecked());	// the player still follows the bet

			}
			else if(nodePtr->thePlayer->getMoney() >= moneyBet - nodePtr->thePlayer->getMoneyChecked()) // when a player has more than $5 to call, the player must put an amount(difference between what the player has checked and what the player has to check) money
			{
				cout << "$" << moneyBet - nodePtr->thePlayer->getMoneyChecked() << " put into the pot." << endl << endl;
				pot += moneyBet - nodePtr->thePlayer->getMoneyChecked(); // money goes into the pot
				nodePtr->thePlayer->addMoney(-1*(moneyBet - nodePtr->thePlayer->getMoneyChecked())); // money from the player account
				nodePtr->thePlayer->addMoneyChecked(moneyBet - nodePtr->thePlayer->getMoneyChecked()); // the player has put enough money to call

			}
			cout << "Player " << nodePtr->thePlayer->getID() << " Checked" << endl << endl;
			nodePtr->thePlayer->setInRound(true); // when a player checks(or calls), the player is in the round
			break;
		case 2: //Raise
			if(nodePtr->thePlayer->getMoney() <= moneyBet - nodePtr->thePlayer->getMoneyChecked()) // if the player do not have enough money to raise
			{
				cout << "You do not have enough money to raise." << endl << endl;
				goto OPTION;
			}
			else
			{
				cout << "$5 raised and put into the pot." << endl << endl;

				moneyBet += 5; // a player can raise only by $5
				nodePtr->thePlayer->addMoney(-1*(moneyBet - nodePtr->thePlayer->getMoneyChecked())); // take money from the player
				pot += moneyBet - nodePtr->thePlayer->getMoneyChecked(); // money goes into the pot

				list.clearInRound(); // if a player raises, the rest should call in order to continue the game
				nodePtr->thePlayer->addMoneyChecked(moneyBet - nodePtr->thePlayer->getMoneyChecked()); //if a player raises, the player is also checking
				nodePtr->thePlayer->setInRound(true); // the player is in the round
			}
			break;
		case 3: //Fold
			cout << "Player " << nodePtr->thePlayer->getID() << " Folded" << endl << endl;
			roundList.deleteNode(nodePtr->thePlayer->getID()); // take the player out of the roundList
			break;
		default: //Invalid Input
			cout << "INVALID INPUT." << endl << endl;
			goto OPTION;
		}
		cout << endl;
		nodePtr = nodePtr->next; // turn goes to next player
		if(roundList.getNumPlayer() == 1) // if there is only one player left in the round, the one is the winner of the round
		{
			return true;
		}
		roundList.showPlayer(); // print status of every player
		cout << "Money on table: " << pot << endl; // print the amount money on the table

	}while(!roundList.allCheck()); // the betting continues until everyone checks and ready to move on
		return false;
}

void GameHandler::shuffleDeck() // shuffle cards after a round
{
	for(int i = 0; i < cnt; i++)
	{
		delete usedCard[i];	 // delete dynamically allocated Card objects
		usedCard[i] = nullptr;  // the array element is set to null pointer
	}
}

void GameHandler::confirmRoundList()
{
	list.copyList(&roundList); // copy the original Player list to the round list
	roundList.makeRingList();  // make round list circular
}

void GameHandler::drawTableCard()
{
	tableCard[tableCnt++] = newCard(); //draws a random card and put it into community cards
}

void GameHandler::showTableCard() // prints a community card info
{
	for(int i = 0; i < tableCnt; i++){
		cout << "\tCard #" << i+1 << " : ";
		switch(tableCard[i]->number)
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
		cout << tableCard[i]->number;
	}
	cout << " ";

	switch(tableCard[i]->suit)
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
	cout <<endl;}
	cout << endl << endl;
}

void GameHandler::setDefault()
{
	cnt = 0; // 0 cards drawn
	tableCnt = 0; // 0 cards on the table
	pot = 0; // no money in the pot
	list.setNumPlayer(0);
	roundList.setNumPlayer(0);
	list.clearCheckMoney(); // no one has checked money yet
	list.clearInRound(); // no one has joined the round
}

void GameHandler::giveMoney()
{
	double moneyToGive;
	moneyToGive = pot / numWinners; // split the pot between the winners
	cout << "$" << moneyToGive << " is given to Player ";
	for (int i = 0; i < numWinners; i++) {
		winners[i]->addMoney(moneyToGive); // give the money, and print that it was given
		cout << winners[i]->getID() << " ";
	}
	cout << endl;
  pot = 0; // now no money left in the pot
}

void GameHandler::sortCardNumber (Card* arr[], int size) {
	int startScan, minIndex;
	Card* minValue;
	// On each loop, start the search at one index greater than the last
	for (startScan = 0; startScan < (size - 1); startScan++) {
		minIndex = startScan;
		minValue = arr[startScan];
		for(int index = startScan + 1; index < size; index++) {
			// Find the smallest value
			if(arr[index]->number < minValue->number) {
				minValue = arr[index];
				minIndex = index;
			}
		}
		// Switch the smallest value with the value at the location of
		// the start of the most recent search
		arr[minIndex] = arr[startScan];
		arr[startScan] = minValue;
	}
}

void GameHandler::integerSort(int arr[], int size){
	int startScan, minIndex, minValue;
	// On each loop, start the search at one index greater than the last
	for (startScan = 0; startScan < (size - 1); startScan++) {
		minIndex = startScan;
		minValue = arr[startScan];
		for(int index = startScan + 1; index < size; index++) {
			// Find the smallest value
			if(arr[index] < minValue) {
				minValue = arr[index];
				minIndex = index;
			}
		}
		// Switch the smallest value with the value at the location of
		// the start of the most recent search
		arr[minIndex] = arr[startScan];
		arr[startScan] = minValue;
	}
}

void GameHandler::assignValue(Card* arr[], int size, int handValue[]) {
	sortCardNumber(arr, size); // sort the cards by their number

	// First find the possible straights
	int straights[3]; // three possible straights out of 7 cards, saves index of "top" of straight
	int straightsSize = 0;
	int inRow = 1; // how many cards are correctly in a row

	for (int i = 1; i < size; i++) {
		if (arr[i]->number == arr[i - 1]->number + 1) {
			inRow++;
			if (inRow >= 5) { // If there's been 5 in a row, there's a straight with the "top" being the current index
				straights[straightsSize] = i; // Save the top of the straight
				straightsSize++;
			}
		}
		// if the card's the same as the one before it, it may be the top of a possible straight
		// this is important because even if the number's the same, the isn't
		else if (i > 1 && (arr[i]->number == arr[i - 1]->number || arr[i]->number == arr[i - 2]->number)) {
			if (inRow >= 5) { // If there's been 5 in a row, there's a straight with the "top" being the current index
				straights[straightsSize] = i; // Save the top of the straight
				straightsSize++;
			}
		}
		else if (arr[i]->number != arr[i - 1]->number){
			// If the current card equals the one at the index after, don't reset the counter
			inRow = 1;
		}
		// if the current index is a king, check if there are aces, because aces can be the top of a straight after king
		// only do this if there are only 2 straights so far, otherwise if there's two kings it will add the same aces
		// twice to the straight list
		if (inRow >= 4 && arr[i]->number == 13 && straightsSize < 3) {
			for (int aceChecker = 0; aceChecker < 3; aceChecker++) {
				if (arr[aceChecker]->number == 1) {
					straights[straightsSize] = aceChecker;
					straightsSize++;
				}
			}
		}
	}

	// Get a count of each suit, used for finding striaght flushes, and regular flushes
	int cardsOfSuit[4][7]; // row 0 is spades, 1 is hearts, 2 is diamonds, 3 is clubs
	int suitsSizes[4] = {0}; // assume there are 0 of each suit at the start
	for (int currCard = 0; currCard < size; currCard++) { // for each card index
		for (int currSuit = 0; currSuit < 4; currSuit++) { // for each possible suit, check if the current card
			if (arr[currCard]->suit == currSuit) {
				cardsOfSuit[currSuit][suitsSizes[currSuit]] = arr[currCard]->number; // add the card to the array of those suits if it matches
				suitsSizes[currSuit]++;
			}
		}
	}

	// check for straight flushes
	int straightFlushVal = -1; // Saves the value of the top of the best straight flush
	bool straightFlush = true;
	bool cardIn;
	Card* currentCard;
	for (int currStraight = 0; currStraight < straightsSize; currStraight++) {
		int lookingFor = arr[straights[currStraight]]->suit; // look for the suit of the top of the straight
		straightFlush = true; // assume there is a straight flush
		currentCard= arr[straights[currStraight]]; // the current card, using the index from straights
		int straightCard;
		int lastToCheck;
		// The starting value should be king if the top of the straight is an ace.
		if (currentCard->number == 1) {
			straightCard = 13;
		}
		// Otherwise, the starting value should be one less than the top.
		else {
			straightCard = currentCard->number - 1;
		}
		lastToCheck = straightCard - 4; // check all cards from the top until 4 below
		for ( ; straightCard > lastToCheck; straightCard--) {
			cardIn = false; // checks if the card is in the list of the lookingFor suit
			for (int flushCard = 0; flushCard < suitsSizes[lookingFor]; flushCard++) {
				if (straightCard == cardsOfSuit[lookingFor][flushCard]) {
					cardIn = true; // if they match, the card is in
					break;
				}
			}
			if (cardIn == false) {
				straightFlush = false; // if the card doesn't match, then a straightFlush is no longer possible
				break;
			}
		}
		if(straightFlush == true) {
			// if the straight flush's top value is 1, that is the best possible straight flush, and set its value to 14 so it will
			// "beat" king's value of 13
			if (arr[straights[currStraight]]->number == 1) {
				straightFlushVal = 14;
				break;
			}
			// if the straight flush's top value is greater than the previous straight flush's top value, make the
			// straightFlushValue equal to that
			else if (arr[straights[currStraight]]->number > straightFlushVal) {
				straightFlushVal = arr[straights[currStraight]]->number;
			}
		}
	}

	// check the counts of each number
	int numberCounts[13] = {0};
	for (int currCard = 0; currCard < size; currCard++)
		numberCounts[arr[currCard]->number - 1]++; // increment the card's corresponding numberCount position ( - 1 b/c numberCount's is 0 indexed)
	// Get information about 4 of a kind, 3 of a kind, and pairs
	int fourKind = -1; // there's one possible four of a kind out of seven cards
	int threeKind[2]; // there's two possible three of a kinds out of seven cards
	int threeKindCount = 0;
	int pairs[3]; // there's three possible pairs
	int pairsCount = 0;
	for (int currCount = 0; currCount < 13; currCount++) {
		if (numberCounts[currCount] == 4) {
			fourKind = currCount + 1; // Four of a kind is equal to the numberCount index + 1 b/c numberCount is 0 indexed
		}
		else if (numberCounts[currCount] == 3) {
			threeKind[threeKindCount] = currCount + 1;
			threeKindCount++;
		}
		else if (numberCounts[currCount] == 2) {
			pairs[pairsCount] = currCount + 1;
			pairsCount++;
		}
	}

	/* Begin assigning the hand value, the first index is formatted in the following manner:
	8: straight flush
	7: four of a kind
	6: full house
	5: flush
	4: straight
	3: three of a kind
	2: two pairs
	1: one pair
	0: nothing (highest card wins)
	the rest of the handValue array is reserved for information about the top of the straights,
	flushes, remaining cards, etc. in their order of importance of determining value.
	*/

	//initialize the handValue with all 0's
	for (int i = 0; i < 6; i++)
		handValue[i] = 0;

	// if there's a straight flush, the first index is 8 (the best) and the second is the top of the straight flush
	if (straightFlushVal != -1) {
		handValue[0] = 8;
		handValue[1] = straightFlushVal;
		return;
	}

	// check for four of a kind
	if (fourKind != -1) {
		int otherCard = -1; // The greatest card not in the 4 of a kind
		for (int currCount = 0; currCount < 13; currCount++) { // for each of the indices in number count
			if (numberCounts[currCount] == 1 && currCount == 0) {
				// if the current index is 0, meaning there is an ace, make the other card equal to 14, so it will "beat" king's value of 13
				otherCard = 14;
				break;
			}
			if (numberCounts[currCount] == 1 && currCount + 1 > otherCard) {
				// if the number count is equal to 1, and it's bigger than the current other card value ( +1 b/c numberCount 0 indexed),
				// make the other card the current index + 1
				otherCard = currCount + 1;
			}
		}
		handValue[0] = 7;
		handValue[1] = fourKind;
		handValue[2] = otherCard;
		return;
	}

	// check for a full house
	if (threeKindCount != 0 && pairsCount != 0) {
		int maxPair;
		// assume the biggest pair is the first in the list
		if (pairs[0] == 1) // if it's an ace, change it to 14, as ace acts as the highest
			maxPair = 14;
		else
			maxPair = pairs[0];
		for (int currPair = 1; currPair < pairsCount; currPair++) {
			// check the others to see if they're bigger than the first
			if (currPair == 1) { // if it's an ace, then set it to 14 as ace is the hgighest
				maxPair = 14;
			}
			if (currPair > maxPair)
				maxPair = currPair;
		}
		handValue[0] = 6;
		handValue[1] = threeKind[0]; // the three of a kind is the first index, because there can't be a pair and multiple three of a kinds
		handValue[2] = maxPair;
		return;
	}

	// if there's a regular flush, assign the numbers in that flush, with the highest first
	for (int currSuit = 0; currSuit < 4; currSuit++) {
		if (suitsSizes[currSuit] >= 5) { // if there's 5 or more of as suit, so there's a flush
			handValue[0] = 5;

			// sort the numbers in the list of numbers in the suit, but first replace 1 with 14, because for in the case of a flush,
			// the ace always acts as the highest value
			for (int i = 0; i < suitsSizes[currSuit]; i++) {
				if (cardsOfSuit[currSuit][i] == 1) {
					cardsOfSuit[currSuit][i] = 14;
				}
			}
			integerSort(cardsOfSuit[currSuit], suitsSizes[currSuit]); // sort the cards of the suit to make it easy to find the biggest

			for (int i = 1; i <= 5; i++) {
				// starting from the end of the list of numbers in the suit, assign the values to handValue
				// essentially the end of the sorted suit list of numbers (the biggest) are assigned to the
				// beginning of handValue
				handValue[i] = cardsOfSuit[currSuit][suitsSizes[currSuit] - i];
			}

			return;
		}
	}

	// if there's a regular straight, return the number at the top
	if (straightsSize > 0) {
		int highestStraight = -1;
		// find the highest straight, but if it's ace, then the highest straight value is 14, as ace is the highest
		for (int i = 0; i < straightsSize; i++) {
			if (arr[straights[i]]->number == 1) {
				highestStraight = 14;
			}
			else if (arr[straights[i]]->number > highestStraight) {
				highestStraight = arr[straights[i]]->number;
			}
		}
		handValue[0] = 4;
		handValue[1] = highestStraight;
		return;
	}

	// if there's three of a kind, but not a full house (found earlier) return the three of a kind number, and the next two highest numbers
	if (threeKindCount > 0) {
		int threeKindVal;
		// sort threeKind, but first change aces to 14
		for (int i = 0; i < threeKindCount; i++) {
			if (threeKind[i] == 1) {
				threeKind[i] = 14;
			}
		}
		integerSort(threeKind, threeKindCount);
		threeKindVal = threeKind[threeKindCount - 1]; // the value of the highest three kind is at the end of the sorted list

		int currNumber, otherCard, secondOther;
		otherCard = -1;
		secondOther = -1;
		for (int currCard = 0; currCard < size; currCard++) {
			currNumber = arr[currCard]->number;
			if (currNumber != threeKindVal) { // if the current number is not one of the three of a kinds
				if (currNumber == 1) { // if it's an ace, make it 14 to be the highest
					otherCard = 14;
				}
				else if (currNumber > otherCard) { // otherwise if it's higher than the first otherCard,
					otherCard = currNumber; // set otherCard to that number
				}
				else if (currNumber > secondOther) { // same with the second other, but don't worry about checking for
					secondOther = currNumber; // aces again, because there can only be one ace since there's no pairs
				}
			}
		}
		handValue[0] = 3;
		handValue[1] = threeKindVal;
		handValue[2] = otherCard;
		handValue[3] = secondOther;

	}

	// if there's two or more pairs, the highest two will be added to handValue, along with the next highest card
	if (pairsCount >= 2) {
		int highest, second, otherCard;

		// sort the pair numbers, but first replace 1 with 14, because ace is worth the most
		for (int i = 0; i < pairsCount; i++) {
			if (pairs[i] == 1) {
				pairs[i] = 14;
			}
		}
		integerSort(pairs, pairsCount);

		highest = pairs[pairsCount - 1];
		second = pairs[pairsCount - 2];

		otherCard = -1;
		int currNumber;

		if (arr[0]->number == 1) {
			otherCard = 14;
		}
		else {
			for (int currCard = size - 1; currCard >= 0; currCard--) {
				currNumber = arr[currCard]->number;
				if (currNumber != highest && currNumber != second && otherCard == -1) {
					otherCard = currNumber;
				}
			}
		}
		handValue[0] = 2;
		handValue[1] = highest;
		handValue[2] = second;
		handValue[3] = otherCard;
		return;
	}

	// if there's a single pair, add it to handValue, along with the 3 next highest cards
	if (pairsCount == 1) {
		handValue[0] = 1;

		// set the first pair to the pair value, but if it's an ace set it to 14 since ace is the best
		if (pairs[0] == 1) {
			handValue[1] = 14;
		}
		else {
			handValue[1] = pairs[0];
		}

		// find the best of the other cards
		int otherCard = -1;
		int otherSecond = -1;
		int otherThird = -1;
		int currNumber;
		for (int i = size - 1; i >= 0; i--) {
			currNumber = arr[i]->number;
			if (currNumber != pairs[0]) {
				if (currNumber == 1) { // similar to finding the threeKind others, check for an ace
					otherCard = 14; // and set the first other card to 14 if there is
				}
				else if (currNumber > otherCard) { // othrewise if the current number is bigger
					otherCard = currNumber; // set the other card to the current number
				}
				else if (currNumber > otherSecond) { // don't worry about checking for multiple aces, because
					otherSecond = currNumber; // it would be a pair if there were multiple
				}
				else if (currNumber > otherThird) {
					otherThird = currNumber;
				}
			}
		}
		handValue[2] = otherCard;
		handValue[3] = otherSecond;
		handValue[4] = otherThird;
		return;
	}

	// the last thing to return is the highest value, return the 5 highest numbers
	handValue[0] = 0;
	// set the first to 14 if there's an ace, otherwise use the highest value in the sorted card numbers
	int start;
	if (arr[0]->number == 1) {
		handValue[1] = 14;
		start = size - 1; // the start of assigning the rest should be the end of the card list
	}
	else {
		handValue[1] = arr[size - 1]->number;
		start = size - 2; // the start of assigning the rest should be one before the end,
		// because the end was already used for the first hand value
	}
	// assign the rest of the cards, starting from the starting point determined earlier
	for (int i = 2; i < 6; i++) {
		handValue[i] = arr[start]->number;
		start--;
	}
}

void GameHandler::compareValues(PlayerNode *head) {
	PlayerNode *nodePtr = head; // the first player is at head
	int handSize = tableCnt + 2; // the total hand size is the card on the table + the 2 in the player's hand
	Card **totalHand = new Card*[handSize]; // the total hand of the current player
	int *currPlayerVal = new int[6]; // the current player's hand value
	Player *currPlayer;

	while (nodePtr) {
		currPlayer = nodePtr->thePlayer;
		// only check this player if they are in the round
		if (currPlayer->getInRound()) {
			// Initialize the beginning of totalHand (which all players share) with the table cards
			for (int i = 0; i < tableCnt; i++) {
				totalHand[i] = tableCard[i];
			}
			// initialize the rest of total hand with the cards in the player's possesion
			totalHand[tableCnt] = currPlayer->getCard1();
			totalHand[tableCnt + 1] = currPlayer->getCard2();

			// assign the value of the current player to currPlayerVal
			assignValue(totalHand, handSize, currPlayerVal);

			for (int i = 0; i < 6; i++) {
				// if the best Hand's value is greater than the player's at that index, don't continue, as the player
				// does not have the best hand
				if (winningHand[i] > currPlayerVal[i]) {
					break;
				}
				// if the best Hand is worse than the player's at that index, then the player has the best hand
				else if (winningHand[i] < currPlayerVal[i]) {
					for (int val = 0; val < 6; val++) {
						winningHand[val] = currPlayerVal[val]; // make the bestHand equal to the player's hand
					}
					winners[0] = currPlayer; // the only winner is now the current player
					numWinners = 1;
					break;
				}
				// if currPlayer's hand has been equal to the best hand for all index's, add that player to the winner list
				if (winningHand[i] == currPlayerVal[i] && i == 5) {
					cout << "THIS SHOULD HAPPEN" << endl;
					winners[numWinners] = currPlayer;
					numWinners++;
				}
			}
		}
		nodePtr = nodePtr->next;
	}
	delete[] totalHand;
	delete[] currPlayerVal;
}

void GameHandler::clearWinners() {
	// erase the previous winners and set the number of winners back to 0
	for (int i = 0; i < 4; i++)
		winners[i] = nullptr;
	numWinners = 0;
	// erase the winning hand information
	for (int i = 0; i < 6; i++)
		winningHand[i] = -1;
}

void GameHandler::singleWinner(Player* theWinner) {
	// if there's only one winner because everyone else flopped or dropped out, the winner is passed here
	winners[0] = theWinner;
	numWinners = 1;
}

Player* GameHandler::getWinner(int i) {
	// return the winner at that index
	return winners[i];
}

int GameHandler::getNumWinners() {
	return numWinners;
}

string GameHandler::cardToString(int num) {
	if (num == 1 || num == 14) // 1 is an ace
		return "ace";
	else if (num < 11) {
		std::ostringstream ss; // use stream to convert the integer to a string
		ss << num;
		return ss.str();
	}
	else if (num == 11) // 11's a jack, and so on
		return "jack";
	else if (num == 12)
		return "queen";
	else if (num == 13)
		return "king";
	else
		return "";
}

void GameHandler::showHand() {
	/*	8: straight flush
	7: four of a kind
	6: full house
	5: flush
	4: straight
	3: three of a kind
	2: two pairs
	1: one pair
	0: nothing (highest card wins)*/
	switch (winningHand[0]) {
		case 8:
			cout << "They had a straight flush, the highest card being a(n) ";
			cout << cardToString(winningHand[1]) << "." << endl;
			break;
		case 7:
			cout << "They had four of a kind of " << cardToString(winningHand[1]) << "." << endl;
		case 6:
			cout << "They had a full house, with three " << cardToString(winningHand[1]) << "s and two ";
			cout << cardToString(winningHand[2]) << "s." << endl;
			break;
		case 5:
			cout << "They had a flush, with the highest card being a(n) ";
			cout << cardToString(winningHand[1]) << "." << endl;
			break;
		case 4:
			cout << "They had a straight, with the highest card being a(n) " << cardToString(winningHand[1]) << "." << endl;
			break;
		case 3:
			cout << "They had three of a kind of " << cardToString(winningHand[1]) << endl;
			break;
		case 2:
			cout << "They had two pairs of " << cardToString(winningHand[1]) << " and ";
			cout << cardToString(winningHand[2]) << "." << endl;
			break;
		case 1:
			cout << "They had one pair of " << cardToString(winningHand[1]) << "." << endl;
			break;
		case 0:
			cout << "They had the highest cards: ";
			// show their 5 high cards forming their final hand
			for (int i = 1; i < 6; i++)
				cout << cardToString(winningHand[i]) << " ";
			cout << endl;
			break;
	}
}


#endif // GAME_H
