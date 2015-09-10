#include <iostream>
#include "card.h"
#include "playerList.h"
#include "player.h"
#include "gameHandler.h"
#include <sstream>
#include <string>
using namespace std;

int main() {
  srand(time(NULL)); // gives random seed determined by current time
  GameHandler handler;  // creates the handeler object
  // creates four players
  Player player1;
  Player player2;
  Player player3;
  Player player4;
  int roundCnt = 0; //round counter

  do{
  	handler.clearWinners(); // clear the winners from the previous round

  	// gives each player the first cards
  	player1.setCard1(handler.newCard());
  	player2.setCard1(handler.newCard());
  	player3.setCard1(handler.newCard());
  	player4.setCard1(handler.newCard());

  	// gives each player the second cards
  	player1.setCard2(handler.newCard());
  	player2.setCard2(handler.newCard());
  	player3.setCard2(handler.newCard());
  	player4.setCard2(handler.newCard());

  	// adds players to the list
  	handler.appendPlayer(&player1);
  	handler.appendPlayer(&player2);
  	handler.appendPlayer(&player3);
  	handler.appendPlayer(&player4);

  	// if any of the player has $0 before a round starts, they get dropped.
  	handler.getList()->dropPlayer();
  	if(handler.getList()->getNumPlayer() == 1)
       	break;

  	cout << "\t\t[ROUND " << roundCnt+1 << "]" << endl << endl; // n th round starts

  	handler.getList()->showPlayer(); // show the info of each player

  	handler.confirmRoundList();   // makes a circular list for the betting actions

  	if(handler.betting()) // pre-flop betting starts and it will return true if there is only one player left after betting
  	{
    	// If handler.betting() returns that there's only one player, set them as the winner
        handler.singleWinner(handler.getRoundList()->getHead()->thePlayer);
    	goto ENDROUND;  // and goto the end of the round
  	}

  	cout << "\t\t\t[THE FLOP]" << endl;               // the flop: three cards are put on the table
  	cout << "\t\t\t========================" << endl;
  	for(int i = 0; i < 3; i++)
    	handler.drawTableCard();	// draws three random cards from the deck
  	handler.showTableCard();  	// and displaying them to the screen
  	cout << "\t\t\t========================\n\n\n";
  	if(handler.betting()) //flop betting starts
  	{
      	// If handler.betting() returns that there's only one player, set them as the winner
          handler.singleWinner(handler.getRoundList()->getHead()->thePlayer);
      	goto ENDROUND;
  	}

  	cout << "\t\t\t[THE TURN]" << endl;
  	cout << "\t\t\t========================" <<endl;
  	handler.drawTableCard();
  	handler.showTableCard();
  	cout << "\t\t\t========================\n\n\n";
  	if(handler.betting()) // turn betting starts
  	{
    	// If handler.betting() returns that there's only one player, set them as the winner
    	handler.singleWinner(handler.getRoundList()->getHead()->thePlayer);
    	goto ENDROUND;
  	}

  	cout << "\t\t\t[THE RIVER]" << endl;
  	cout << "\t\t\t========================" << endl;
  	handler.drawTableCard();
  	handler.showTableCard();
  	cout << "\t\t\t========================\n\n\n";
  	if(handler.betting()) // river betting starts
  	{
    	// If handler.betting() returns that there's only one player, set them as the winner
        handler.singleWinner(handler.getRoundList()->getHead()->thePlayer);
    	goto ENDROUND;
  	}

  	// If there are still multiple players in the round, compare the values of their hands,
  	// and find the winner(s)
      handler.compareValues(handler.getList()->getHead());
  	goto ENDROUND;

ENDROUND:   // when the winner is determined, the following tasks are done before finishing the round
  	cout << "The winner of the round is player ";
  	for (int i = 0; i < handler.getNumWinners(); i++) {
      	cout << handler.getWinner(i)->getID();        	// shows the winner ID
      	if (i == handler.getNumWinners() - 1)
          	cout << endl;
      	else
          	cout << " and ";  	// in the case when there is more than one winner
  	}
  	cout <<endl;
  	handler.showHand();   // displays the winning hands
  	handler.giveMoney();  // give the money on the table to the winner
  	handler.setDefault(); // set the list, number of players, money on table, money checked, check status to default
  	handler.getRoundList()->setHead(nullptr); // set the Round list to default
  	handler.shuffleDeck(); // burn the cards and shuffles the deck
      handler.getList()->setHead(nullptr);  // set the gameList to default
  	roundCnt++;   // round number incremented
  	cin.ignore(); // flushing keyboard buffer
  	string dummy; // dummy variable for input
  	cout << "\t\t\t[PRESS ENTER TO END THE ROUND]" << endl; // wait for the user input to move onto the next round
  	getline(cin, dummy);  // accepts any input with '\n'
  }while(handler.getList()->getNumPlayer() != 1);   // the game goes forever until there is only one palyer left

  cout << "The final winner is Player " << handler.getList()->getHead()->thePlayer->getID() << endl;	// displays the final winner
  return 0; // end of the game
}
