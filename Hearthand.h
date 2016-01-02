#ifndef HEARTHAND_H
#define HEARTHAND_H
#include "List_linked_list.h"
 
class Hearthand
{
    public:
        Hearthand();
	
	// uses the List_linked_list's print function and displays the indecies
	// of each card to help the user choose
        void disp_hand();
	
	// these functions utilize the public functions from the List_linked_list
        void add_card(Card);
	void add_card_at_index(Card, int);
        int get_points();
	
	// Returns a card of the player's choice from their hand
        Card get_card();
	
	// adds cards to the player's trick pile and calculates the points
        void add_trick_card(Card);
	
	// returns true if the hand has the two of clubs, false otherwise
        bool find_two();
	
	// sorts hand based on the normal way hands are sorted in hearts (i.e.
	// how I do it)
        void sort_hand();
	
	// returns the index of the card the user has chosen
	int get_input();
	
	// determines whether a certain suit is present in the hand
	bool has_suit(Suit);
 
    private:
      
	// gets index of a card from the user
        int ask_choice();
	int user_input;
	
	// uses the List_linked_list data structure to store the hand and the
	// cards the player has won
        List_linked_list *hand;	
        List_linked_list *my_tricks;
	
        int hand_size;
        int my_tricks_size;
	
	// 1 point for each heart, 13 for the queen of spades, 0 for any other
        int trick_points;
};
 
#endif // HEARTHAND_H
