/*	Alex Childers
	CS 211 Lab 4
	09/17/2018
	This program is intended to create a binary tree, populate it with
		values, and have functions that return the height of the tree and 
		whether it is full or not.
*/

#include <cstdlib>
#include <iostream>
#include "BinaryNode.h"

using namespace std; 

typedef BinaryNode* BinaryNodePtr;

int main()
{
	BinaryNode test_node{3}; // DEFAULT CONSTRUCTOR NOT WORKING? 

	cout << "Initialized value of test_node is " << test_node.getValue() << endl; 

	return 0; 
}