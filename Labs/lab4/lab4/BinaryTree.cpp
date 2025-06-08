// Alex Childers
// CS 211 Lab 4
// 09/17/2018
// Source file for BinaryTree class. 

#include <cstddef>
#include "BinaryTree.h"
#include "BinaryNode.h"

using namespace std;

BinaryTree::BinaryTree(BinaryNode* node = nullptr)
{
	root = node; 
}

void BinaryTree::setRoot(BinaryNode* node)
{
	root = node; 
}

BinaryNode* BinaryTree::getRoot()
{
	return root; 
}