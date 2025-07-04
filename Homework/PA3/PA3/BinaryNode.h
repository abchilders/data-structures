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

// This file is from the ADT package. 

#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <utility>
using namespace std;
template <typename T>
class BinaryNode
{
private:

	//underlying value in our node
	T _value;

	//a pointer to our left child
	BinaryNode<T> *_left_child;

	//a pointer to our right child
	BinaryNode<T> *_right_child;

	//disallow copy constructors
	BinaryNode(const BinaryNode<T> &other);
	BinaryNode(BinaryNode<T> &&other);

	//disallow assignment operator
	BinaryNode<T> &operator=(const BinaryNode<T> &other);
	BinaryNode<T> &operator=(BinaryNode<T> &&other);

protected:

public:

	//default constructor
	BinaryNode()
	{
		_left_child = nullptr;
		_right_child = nullptr;
	}

	BinaryNode(T value)
	{
		_left_child = nullptr;
		_right_child = nullptr;
		_value = value;
	}

	//constructor that takes in two binary nodes to set as left and right
	BinaryNode(BinaryNode<T> *left, BinaryNode<T> *right)
	{
		_left_child = left;
		_right_child = right;
	}

	virtual bool isLeaf()
	{
		return _left_child == nullptr && _right_child == nullptr;
	}

	BinaryNode<T> *getLeftChild()
	{
		return _left_child;
	}

	const BinaryNode<T> *getLeftChild() const
	{
		return _left_child;
	}

	void setLeftChild(BinaryNode<T> *left)
	{
		_left_child = left;
	}

	BinaryNode<T> *getRightChild()
	{
		return _right_child;
	}

	const BinaryNode<T> *getRightChild() const
	{
		return _right_child;
	}

	void setRightChild(BinaryNode<T> *right)
	{
		_right_child = right;
	}

	void setValue(T value)
	{
		_value = value;
	}

	T &getValue()
	{
		return _value;
	}

	const T &getValue() const
	{
		return _value;
	}
};

#endif