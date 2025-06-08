// Alex Childers
// CS 211 Lab 4
// 09/17/2018
// Header file for BinaryNode class. 

#ifndef BINARYNODE_H
#define BINARYNODE_H

class BinaryNode
{
public:
	// constructor
	BinaryNode(int num);

	// setter for value
	void setValue(int num);

	// setter for left
	void setLeft(BinaryNode* left_ptr);

	// setter for right
	void setRight(BinaryNode* right_ptr);

	// getter for value
	int getValue() const;

	// getter for left
	BinaryNode* getLeft() const;

	// getter for right
	BinaryNode* getRight() const;

private:
	int value;
	BinaryNode* left;
	BinaryNode* right;
};

#endif /* BINARYNODE_H */
