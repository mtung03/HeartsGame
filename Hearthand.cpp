#include <iostream>
#include "Hearthand.h"
using namespace std;
 
Hearthand::Hearthand()
{
    hand = new List_linked_list;
    my_tricks = new List_linked_list;
    hand_size = 0;
    my_tricks_size = 0;
    trick_points = 0;
}
 
void Hearthand::disp_hand()
{
    int j;
    hand->print_list();
    cout << "          ";
    for( j = 0; j < hand_size and j < 10; j++ ) {
        cout << j << "  ";
    }
    if( hand_size > 10 ) {
        while( j < hand_size ) {
            cout << j << " ";
            j++;
        }
    }
    cout << endl;
}
 
void Hearthand::add_card(Card new_card)
{
    hand->insert_at_front(new_card);
    hand_size++;
}

void Hearthand::add_card_at_index(Card new_card, int index)
{
    hand->insert_at_index(new_card, index);
    hand_size++;
}
 
int Hearthand::get_points()
{
    return trick_points;
}

Card Hearthand::get_card()
{
    user_input = ask_choice();
    if ( user_input < 0 or user_input >= hand_size ) {
	cout << "invalid input" << endl;
	return get_card();
    }
    Card played = hand->remove_from_index(user_input);
    hand_size--;
    return played;
}


void Hearthand::add_trick_card(Card trick_card)
{
    Card heartTest;
    Card queen_spade('Q','S');
    heartTest.set_suit(HEART);
    my_tricks->insert_at_back(trick_card);
    my_tricks_size++;
    if( trick_card.get_suit() == heartTest.get_suit() ) {
        trick_points++;
    }
    else if( trick_card.same_card( queen_spade ) ) {
        trick_points = trick_points + 13;
    }
}

int Hearthand::ask_choice()
{
    int n;
    cout << "Play a card from an index: ";
    cin >> n;
    return n;
}
 
bool Hearthand::find_two()
{
    Card two_clubs('2','C');
    return hand->has_card(two_clubs);
}
 
bool lower_card(Card, Card);
 
void Hearthand::sort_hand()
{
    Card temp;
    for( int j = 0; j < 13; j++ ) {
        for( int i = j; i < 13; i++ ) {
            if(lower_card(hand->card_at(j), hand->card_at(i))) {
               temp = hand->card_at(i);
	       hand->replace_at_index(hand->card_at(j), i);
               hand->replace_at_index(temp, j);
            }
        }
    }
}
 
bool lower_card( Card one, Card two )
{
    if( one.get_suit() == two.get_suit() ) {
        return (one.card_int() > two.card_int());
    }
    else if( one.get_suit() == HEART or two.get_suit() == CLUB ) return true;
    else if( two.get_suit() == HEART or one.get_suit() == CLUB ) return false;
    else if( one.get_suit() == DIAMOND ) return false;
    else return true;
}

int Hearthand::get_input()
{
    return user_input;
}

bool Hearthand::has_suit(Suit s)
{
    for( int i = 0; i < hand->cards_in_hand(); i++ ) {
	if( hand->card_at(i).get_suit() == s ) return true;
    }
    return false;
}
