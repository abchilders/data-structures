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

// This file is loosely adapted from "BinarySearchTree.h" and 
// "TreeTraversal.h" in the ADT package.

#ifndef ANIMALTREE_H
#define ANIMALTREE_H
#include "BinaryNode.h"
#include <fstream>
#include <string>

class AnimalTree
{
public:
	// constructor
	AnimalTree();

	// asks the user if they want to load a file- if so, loads the 
	// file into an AnimalTree; if not, creates new tree
	// returns the name of the file to save the results to 
	string setUp();

	// runs through the game
	void playGame(); 

	// output the final tree to the game file specified by the user
	void endGame(string out_filename);

private:
	BinaryNode<string>* _root = nullptr;
	
	// used to mark answer nodes
	string _answer_flag = "*"; 

	// for creating a default tree
	void createTree();

	// for creating a tree, given an input file to load
	void createTree(ifstream &in_stream);

	// helper function that allows recursion in createTree
	BinaryNode<string>* createTreeHelper(BinaryNode<string>* current, ifstream &in_stream);

	// performs a pre-order traversal of the entire tree
	void preOrderTraversal(BinaryNode<string>* node, ostream &out_stream);

	// deletes tree for which node is the root
	// (sort of a replacement for the destructor) 
	void cleanUp(BinaryNode<string>* node);
};

#endif // ANIMALTREE_H