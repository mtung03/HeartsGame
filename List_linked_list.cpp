#include "List_linked_list.h"

#include <iostream>
#include <cassert>

using namespace std;

/*
 * The following #define allows us to use Card_Node as a type.
 * Because the node structure is private, we would otherwise
 * have to write List_linked_list::Card_node everywhere.
 *
 * I put a few of those in, so you can see what I mean (see
 * the copy constructor.
 */
#define Card_Node List_linked_list::Card_Node

List_linked_list::List_linked_list()
{
	front = NULL;
	back = NULL;
	cards_in_list = 0;
}

List_linked_list::~List_linked_list()
{
	make_empty();
}

/*
 * Explicit copy constructor necessary because of cards list 
 * in the heap.
 */
List_linked_list::List_linked_list(const List_linked_list &source)
{
	if (source.front == NULL) return; // nothing to do

	front = new List_linked_list::Card_Node;
        List_linked_list::Card_Node *this_current   = front;
	List_linked_list::Card_Node *source_current = source.front;

	while (source_current != NULL) {
		// deep copy each Card_Node
		if (source_current->next != NULL) {
			List_linked_list::Card_Node *new_node
                                = new List_linked_list::Card_Node();
			this_current->next  = new_node;
			new_node->card      = source_current->next->card;
		} else {
			this_current->next = NULL; // at back
		}
		source_current = source_current->next;
		this_current   = this_current->next;
	}
}

/*
 * Explicit operator= overload necessary because of heap-allocated 
 * card nodes
 */
List_linked_list List_linked_list::operator =(const List_linked_list &source)
{
	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (front != NULL) {
		Card_Node *next = front->next;
		delete front;
		front = next;
	}
	// copy over all cards from source list
	if (source.front == NULL) return *this; // nothing to do

	front = new Card_Node;
	Card_Node *this_current   = front;
	Card_Node *source_current = source.front;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next  = new_node;
		} else {
			this_current->next = NULL; // at back
		}
		source_current = source_current->next;
		this_current   = this_current->next;
	}
	return *this;
}

void List_linked_list::print_list()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}

int List_linked_list::cards_in_hand()
{
	return cards_in_list;
}

void List_linked_list::make_empty()
{
	// delete list by looping through and deleting each node
	Card_Node *iterator = front;
	Card_Node *deleter = front;
	while( iterator != NULL ) {
		iterator = iterator -> next;
		delete deleter;
		deleter = iterator;
	}
	front = NULL;
	cards_in_list = 0;
}

void List_linked_list::insert_at_front( Card inserter )
{
	insert_at_index( inserter, 0 );
}

void List_linked_list::insert_at_back( Card inserter )
{
	Card_Node *insert = new Card_Node;
	insert->card = inserter;
	insert->next = NULL;
	if( is_empty() ) {
	      front = insert;
	      back = insert;
	}
	else {
	      back->next = insert;
	      back = insert;
	}
	cards_in_list++;
}

void List_linked_list::insert_at_index( Card inserter, int index )
{
	if( index == cards_in_list && not is_empty() ) {
		insert_at_back( inserter );
		return;
	}
	Card_Node *insert = new Card_Node;
	insert->card = inserter;

	if( index == 0 ) {
		insert->next = front;
		front = insert;
	}
	else {
		Card_Node *prev = get_to_index( index-1 );
		insert->next = prev->next;
		prev->next = insert;
	}
	if( cards_in_list == 0 ) {
		back = insert;
	}
	cards_in_list++;
}

void List_linked_list::replace_at_index( Card replace, int index )
{
	Card_Node *iterator = get_to_index( index );

	iterator->card = replace;
}

Card List_linked_list::card_at( int index )
{
	Card_Node *iterator = get_to_index( index );

	return (iterator->card);
}

bool List_linked_list::has_card( Card c )
{
	if( is_empty() ) return false;
	Card_Node *iterator = front;
	while( iterator->next != NULL ) {
		if( iterator->card.same_card(c) ) {
			return true;
		}
		iterator = iterator->next;
	}
	if( iterator->card.same_card(c) ) {
		return true;
	}

	return false;
}

bool List_linked_list::remove( Card remover )
{
	if( not has_card(remover) ) {
		return false;
	}
	for( int i = 0; i < cards_in_list; i++ ) {
		if( remover.same_card( card_at(i) ) ) {
			remove_from_index(i);
			return true;
		}
	}
	return false;
}

Card List_linked_list::remove_from_front()
{
	return remove_from_index( 0 );
}

Card List_linked_list::remove_from_back()
{
	return remove_from_index( cards_in_list-1 );
}

Card List_linked_list::remove_from_index( int index )
{
	Card_Node *remover;
	if( index == 0 ) {
		remover = front;
		front = front->next;
	}
	else {
		Card_Node *preremover = get_to_index(index-1);
		if( index == cards_in_list-1 ) {
		      back = preremover;
		}
		remover = preremover->next;
		preremover->next = remover->next;
	}

	Card returner = remover->card;

	delete remover;

	cards_in_list--;
	return returner;
}

Card_Node *List_linked_list::get_to_index( int index )
{
	assert( not is_empty() and index <= cards_in_list );

	Card_Node *iterator = front;
	for( int i = 0; i < index and iterator->next != NULL; i++) {
		iterator = iterator->next;
	}
	return iterator;
}
