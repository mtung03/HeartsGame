#ifndef HEARTSGAME_H
#define HEARTSGAME_H
#include "Hearthand.h"
 
class HeartsGame
{
    public:
        HeartsGame();
	
	// contains the main loop and calls most of the other functions
	// needed to run the game
        void play();
	
	// determines which hand contains the two of clubs and returns its 
	// index
        int find_starter();
	
	// prints the current trick
        void disp_trick();
	
	// determines the winner of the trick and returns its index
        int get_winner();
	
	// displays which player won the trick and adds its cards to their
	// tricks_won list
        void add_trick();
	
    private:
	// holds the standard deck that the hands are dealt from
        List_linked_list *deck;
	
	/* the making and shuffling of a standard deck is a modified version
	of the function from the  hand.cpp file provided to us */
	void make_deck();
	void shuffle();
	
	// an array of Hearthand objects holds the players
        Hearthand players[4];
	
	// holds the cards in the current trick
        Card trick[4];
	int trick_size;
	
	// keeps track of which suit was led in the current trick
	Suit curr_suit;
        
	// keeps track of the last player to win a trick
        int curr_winner;
	
	// holds whether or not hearts have been broken
	bool hearts_broken;
	
	// given the card played and the player, returns true if it is a valid
	// play, and false if it breaks a rule
	bool check_card(Card, int player);
};
 
#endif // HEARTSGAME_H
