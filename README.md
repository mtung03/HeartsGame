# HeartsGame
Full Hearts Implementation

As part of the "above and beyond" portion of a class assignment, I integrated
several auxilary files with code creating a standard deck. This code was 
originally written in summer 2015, and has been adjusted to work with the
 interface provided by these List_linked_list and card classes.

A quick rundown on the interface of this game:
  - Creates a standard 52 card deck, and deals it out randomly to four players
  - Finds the player with the two of clubs (traditionally the starting card) 
    and asks that player to play a card and start the game.
  - Goes around and displays each players hand, and asks them for a card to play
  - Prints out which player won the trick and starts the next turn with that 
    player
  - Continues until all cards have been played and then prints out each 
    players scores
  - ends the program

Notes on what cards players can play (program will print "invaid move" 
and ask for another card if a rule is broken):
  - Players must follow the suit of the current trick if they have that suit

  - Players cannot start a trick with a heart or the queen of spades if 
    hearts have not been "broken" (if this is confusing look up the standard 
    rules of hearts online)

  - Players cannot request a card index that is out of the range of their hand


Program deficiencies (i.e. stuff I want to change but have not gotten to or 
been able to figure out):

  - While the game determines which player has the two of clubs and starts with
    them, it currently allows them to play any card, not just the two

  - The program only runs for one "hand" of hearts, whereas a full game 
    traditionally goes until one player has over 100 points

  - Players cannot shoot the moon

  - The terminal window does not clear in between displaying the hands of the 
    players, theoreticall allowing for players to see each others hands

  - Can only be played with 4 different humans, instead of implementing some 
    form of AI to allow a human vs cpu game

  - General verbosity, code style, and documentation is somewhat inconsistent 
    throughout, which is indicative of the length of time spent working off and 
    on on this, and my general lazy habits when writing personal projects

Overview of Data structures used:

    standard deck                singly linked list
    hands of players             array of singly linked lists
    tricks                       standard array of cards
    tricks won by players        singly linked list

Overview of included files:

    heartmain.cpp: 
       - creates an instance of the HeartsGame class and runs it

    Card class (card.h, card.cpp):
	- Creates a standard playing card with a rank and suit.
	- Designed and coded by the instructor

    List_linked_list class (List_linked_list.h, List_linked_list.cpp):
	- Creates a singly linked list of cards that can be read and manipulated
	  through the various public functions
	- INTERFACE designed by instructor

    HeartsGame Class (HeartsGame.h, HeartsGame.cpp): 
       - Creates four players, and runs the main loop

    Hearthand Class (Hearthand.h, Hearthand.cpp): 
       - Uses the List_linked_list class and runs the necessary operations for a hand playing hearts
       - Abstracts actual data structure used

Compiled using the included Makefile
