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

#include "AnimalTree.h"
#include "BinaryNode.h"
#include <queue>
#include <iostream>

static string _default_val = "dog?";

AnimalTree::AnimalTree(): _root(nullptr), _answer_flag("*")
{
	// intentionally empty
}

string AnimalTree::setUp()
{
	string answer = "x";
	string file_name = "x";
	cout << "Load file? (yes/no): ";
	cin >> answer;
	while (answer != "yes" && answer != "no")
	{
		cout << "Invalid response. Just type \"yes\" or \"no.\"" << endl;
		cout << "Load file? (yes/no): ";
		cin >> answer;
	}

	// if the user wants to load an existing file, open an input stream
	// and load the contents into an AnimalTree
	cin.ignore(); 
	if (answer == "yes")
	{
		cout << "File name: ";
		getline(cin, file_name);
		ifstream input_file{ file_name };
		if (input_file.is_open())
		{
			if (input_file.good() == true)
			{
				createTree(input_file);
			}
		}
		else
		{
			cout << file_name << " not found. Creating new " << file_name
				<< " instead." << endl;
			createTree();
		}
		cout << "..." << file_name << " loaded" << endl;
		input_file.close();
	}
	else
	{
		cout << "Save results to: ";
		getline(cin, file_name);
		createTree();
	}

	return file_name;
}

void AnimalTree::playGame()
{
	// While we are not at a leaf node, ask questions. 
	string question_response = "x";
	BinaryNode<string>* previous = nullptr;
	BinaryNode<string>* current = _root;
	while (current->isLeaf() == false)
	{
		cout << current->getValue() << " (yes/no): ";
		cin >> question_response;
		previous = current;

		// If the user responds "yes" to the question, go to right child. 
		if (question_response == "yes")
		{
			current = current->getRightChild();
		}

		// If the user responds "no" to the question, go to left child. 
		else if (question_response == "no")
		{
			current = current->getLeftChild();
		}

		// Other answers are invalid - prompt for an answer again. 
		else
		{
			cout << "Invalid answer. Please type \"yes\" or \"no.\""
				<< endl;
		}
	}

	// At a leaf node, guess the animal. 
	string final_answer;
	cout << "Is it a " << current->getValue() << " (yes/no): ";
	cin >> final_answer;
	while (final_answer != "yes" && final_answer != "no")
	{
		cout << "Invalid answer. Please type \"yes\" or \"no.\""
			<< endl;
		cout << "Is it a " << current->getValue() << " (yes/no): ";
		cin >> final_answer;
	}

	// If the computer gets the animal right, the game is over. 
	if (final_answer == "yes")
	{
		cout << "I win! Game over." << endl;
	}

	// If the computer didn't guess the animal correctly, ask the user to 
	// give us information about it to put into the tree. 
	else
	{
		cin.ignore();
		string new_animal = "x";
		cout << "Darn, I got it wrong. What is the correct answer: ";
		getline(cin, new_animal);
		string new_question = "x";
		string wrong_animal = current->getValue();
		wrong_animal = wrong_animal.substr(0, (wrong_animal.size() - 1));
		cout << "What is a yes/no question that I can use to "
			<< "differentiate between a " << wrong_animal
			<< " and a " << new_animal << "?" << endl;
		getline(cin, new_question);
		cout << "Is the answer to this question yes or no?: ";
		cin >> final_answer;
		while (final_answer != "yes" && final_answer != "no")
		{
			cout << "Invalid answer. Please type \"yes\" or \"no.\""
				<< endl;
			cout << "Is the answer to this question yes or no?: ";
			cin >> final_answer;
		}

		// Put new answer into the tree. 
		BinaryNode<string>* question_node = new BinaryNode<string>{ new_question };
		BinaryNode<string>* animal_node = new BinaryNode<string>{ new_animal + "?" };
		if (final_answer == "yes")
		{
			// the new animal becomes the right child of the new question
			question_node->setRightChild(animal_node);
			question_node->setLeftChild(current);
		}
		else
		{
			// the new animal becomes the left child of the new question
			question_node->setLeftChild(animal_node);
			question_node->setRightChild(current);
		}

		// Now that the new question and new animal have been connected, 
		// reconnect it to the rest of the tree - the previous question's 
		// child needs to be reassigned. 
		if (previous == nullptr)
		{
			_root = question_node;
		}
		else
		{
			if (question_response == "yes")
			{
				previous->setRightChild(question_node);
			}
			else
			{
				previous->setLeftChild(question_node);
			}
		}
	}
}

void AnimalTree::endGame(string out_filename)
{
	ofstream out_file{ out_filename };
	if (out_file.is_open())
	{
		preOrderTraversal(_root, out_file);
	}
	out_file.close(); 
	cleanUp(_root); 
}

void AnimalTree::createTree()
{
	_root = new BinaryNode<string>{ _default_val };
}

void AnimalTree::createTree(ifstream &in_stream)
{
	_root = createTreeHelper(_root, in_stream);
}

BinaryNode<string>* AnimalTree::createTreeHelper(BinaryNode<string>* current, ifstream &in_stream)
{
	string val = "x";
	getline(in_stream, val); 

	// assuming that if the first line of the input file is empty, the rest
	// of it is empty
	if (val == "" || val.at(0) == ' ')
	{
		createTree(); 
		return _root; 
	}
	if (val.substr(0, 1) == _answer_flag)
	{
		val.erase(0, 1);
		current = new BinaryNode<string>{ val };
	}
	else
	{
		current = new BinaryNode<string>{ val };
		current->setLeftChild(createTreeHelper(current->getLeftChild(), in_stream));
		current->setRightChild(createTreeHelper(current->getRightChild(), in_stream));
	}
	return current;
}

void AnimalTree::preOrderTraversal(BinaryNode<string>* node, ostream &out_stream)
{
	// consider: what if we're given a nullptr node?
	if (node == nullptr)
	{
		return;
	}

	// us 
	if (node->isLeaf() == true)
	{
		out_stream << _answer_flag << node->getValue() << endl; 
	}
	else
	{
		out_stream << node->getValue() << endl;
	}

	// left
	preOrderTraversal(node->getLeftChild(), out_stream);

	// right
	preOrderTraversal(node->getRightChild(), out_stream);
}

void AnimalTree::cleanUp(BinaryNode<string>* node)
{
	if (node == nullptr)
	{
		return; 
	}
	cleanUp(node->getLeftChild());
	cleanUp(node->getRightChild()); 
	delete node; 
}