#include <iostream>
#include <cstdlib>
#include <time.h>
#include "HeartsGame.h"
using namespace std;
 
HeartsGame::HeartsGame()
{
    deck = new List_linked_list;
    Card test_card('A','C');
    hearts_broken = false;
    
    make_deck();

    for( int i = 0; i < 4; i++ ) {
        trick[i] = test_card;
    }
    
    for( int j = 0; j < 13; j++ ) {
        for( int k = 0; k < 4; k++ ) {
            players[k].add_card(deck->remove_from_front());
        }
    }
    
    for( int n = 0; n < 4; n++ ) {
        players[n].sort_hand();
    }
    
    trick_size = 0;
    curr_winner = find_starter();
}
 
/* the making and shuffling of a standard deck is a modified version
of the function from the  hand.cpp file provided to us */
void HeartsGame::make_deck()
{
	int s,r;
	    Card c;
	    for (s=0; s<=3; s++) {
		    for (r=0; r<=12; r++) {
			    c.set_suit((Suit)s);
			    c.set_rank((Rank)r);
			    deck->insert_at_front(c);
		    }
	    }
	    
	// use Knuth shuffle (Fisher-Yates)
	// http://en.wikipedia.org/wiki/Fisher–Yates_shuffle
	shuffle();
}

static int rand_seed = -1;
int random_int(int, int);
void seed_random(int);
 
void HeartsGame::shuffle()
{
	Card temp;
	for( int i = deck->cards_in_hand() - 1; i > 0; i-- ) {
		int curr_random = random_int(0, i);
		temp = deck->card_at(curr_random);
		deck->replace_at_index(deck->card_at(i), curr_random);
		deck->replace_at_index(temp, i);
	}
}

void seed_random(int s)
{
	if ( s > 0 ) {
		srand(s);
		rand_seed = s;
	}
}

int random_int(int lo, int hi)
{
	int range = hi - lo + 1;
	char	*seed_str;
	
	if ( rand_seed == -1 ) {
		seed_str = getenv( "HEART_SEED" );
		if ( seed_str != NULL )
		    seed_random( (unsigned) atoi(seed_str) );
		else
		    seed_random( (unsigned) time(NULL) );
	}
	if ( range <= 0 )
	    return 17;
	
	return lo + ( rand() % range );
}

void HeartsGame::play()
{
    cout << "Lets play! " << endl;
    int k;
    Card played_card;
    for( int i = 0; i < 13; i++ ) {
        for( int j = curr_winner; j < curr_winner+4; j++ ) {
            if( j > 3 ){ k = j-4;}
            else {k = j;}
            disp_trick();
            cout << "\nPlayer " << k+1 << ": ";
            players[k].disp_hand();
	    played_card = players[k].get_card();
	    if( trick_size == 0 ) {
		curr_suit = played_card.get_suit();
	    }
	    while( !check_card(played_card, k) ) {
		cout << "invalid move" << endl;
		players[k].add_card_at_index(played_card, players[k].get_input());
		played_card = players[k].get_card();
	    }
            trick[trick_size] = played_card;
            trick_size++;
	    cout << endl;
        }
        curr_winner = (curr_winner + get_winner())% 4;
        add_trick();
    }
    cout << endl << endl;
    for( int k = 0; k < 4; k++ ) {
        cout << "Player " << k+1 << ": " << players[k].get_points() << endl;
    }
}
 
int HeartsGame::find_starter()
{
    for( int i = 0; i < 4; i++ ) {
        if(players[i].find_two()) {
            return i;
        }
    }
    return -1;
}
 
void HeartsGame::disp_trick()
{
    cout << "Current Trick: ";
    for(int i = 0; i < trick_size; i++) {
        trick[i].print_card();
	cout << " ";
    }
}
 
int HeartsGame::get_winner()
{
    Rank curr_high = trick[0].get_rank();
    for( int i = 0; i < 4; i++ ) {
        if( trick[i].get_suit() == curr_suit ) {
            if( trick[i].get_rank() > curr_high ) {
                curr_high = trick[i].get_rank();
            }
        }
    }
    for( int j = 0; j < 4; j++ ) {
        if(trick[j].get_suit() == curr_suit and trick[j].get_rank() == curr_high) {
            return j;
        }
    }
    return -1;
}
 
void HeartsGame::add_trick()
{
    cout << "Player " << curr_winner+1 << " wins trick!" << endl;
    for( int i = 0; i < 4; i++ ) {
        players[curr_winner].add_trick_card(trick[i]);
        trick_size--;
    }
}

bool HeartsGame::check_card(Card check, int player)
{
    if( players[player].has_suit(curr_suit) and trick_size > 0 ) {
	return (curr_suit == check.get_suit());
    }
    else if( check.get_suit() == HEART ) {
	if( trick_size == 0 ) {
	    if( not hearts_broken ) return false;
	}
	else {
	    hearts_broken = true;
	}
    }    
    else return true;
}
