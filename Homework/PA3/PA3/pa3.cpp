/*
Assignment: PA #3 - Guessing Game
Description: This program is a yes/no animal guessing game, using a
	binary tree to store all questions and possible animal answers. 
	As the game is replayed, the tree will acquire more and more 
	questions from the user, which can be used to further distinguish
	among possible animals that users might have the program guess. 
Author: Alex Childers
HSU ID: 013145324
Completion Time: 20 hours
In completing this program, I received help from the following people:
	N/A
*/

#include "AnimalTree.h"
#include <cstdlib> 
#include <iostream>

const string GREETING_MSG = "***Animal Guessing Game***";

int main(void)
{
	string out_file = "x"; 
	string play_again = "x";
	AnimalTree game_questions{};

	// Start up the game.
	cout << GREETING_MSG << endl;  

	do
	{
		// Load file if desired; create a new file otherwise. 
		out_file = game_questions.setUp();

		// Start playing the game.
		game_questions.playGame(); 

		// Output the final tree to the game file specified by the user. 
		game_questions.endGame(out_file);

		// Loop if the player wants to play again. 
		cout << "Would you like to play again? (yes/no): ";
		cin >> play_again; 
		while (play_again != "yes" && play_again != "no")
		{
			cout << "Invalid answer. Please type \"yes\" or \"no.\""
				<< endl;
			cout << "Would you like to play again? (yes/no): ";
			cin >> play_again;
		}
		if (play_again == "no")
		{
			cout << "Game over" << endl;
		} 
	} while (play_again == "yes");

	return 0;
}