// Alex Childers
// CS 211 Lab 4
// 09/17/2018
// Source file for BinaryNode class. 

#include <cstddef>
#include "BinaryNode.h"

using namespace std; 

BinaryNode::BinaryNode(int num = 0) : value(num), left(nullptr), right(nullptr)
{
	// intentionally empty
}

void BinaryNode::setValue(int num)
{
	value = num; 
}

void BinaryNode::setLeft(BinaryNode* left_ptr)
{
	left = left_ptr; 
}

void BinaryNode::setRight(BinaryNode* right_ptr)
{
	right = right_ptr; 
}

int BinaryNode::getValue() const
{
	return value; 
}

BinaryNode* BinaryNode::getLeft() const
{
	return left; 
}

BinaryNode* BinaryNode::getRight() const
{
	return right; 
}