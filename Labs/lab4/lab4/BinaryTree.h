// Alex Childers
// CS 211 Lab 4
// 09/17/2018
// Header file for BinaryTree class. 

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"

class BinaryTree
{
public:
	// constructor
	BinaryTree(BinaryNode* node); 

	// setter for root
	void setRoot(BinaryNode* node); 

	// getter for root
	BinaryNode* getRoot();

private:
	BinaryNode* root; 
};

#endif /* BINARYTREE_H */