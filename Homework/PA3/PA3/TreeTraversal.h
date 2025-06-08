/*
Assignment: PA #3 - Guessing Game
Description: This program is a yes/no animal guessing game, using a
	binary tree to store all questions and possible animal answers.
	As the game is replayed, the tree will acquire more and more
	questions from the user, which can be used to further distinguish
	among possible animals that users might have the program guess.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 10:45 - WHEN
In completing this program, I received help from the following people:
	LIST PEOPLE HERE
*/

// This file is from the ADT package. 

#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include "BinaryNode.h"
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map> //AKA HashTable
using namespace std;

template <typename T>
class TreeTraversal
{
public:
	void virtual traverse(BinaryNode<T> *node) = 0;
};

template <typename T>
class RecursivePreOrderTraversal : public TreeTraversal<T>
{
public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		//Us
		cout << node->getValue() << " ";

		//Left
		traverse(node->getLeftChild());

		//Right
		traverse(node->getRightChild());
	}
};

template <typename T>
class RecursiveInOrderTraversal : public TreeTraversal<T>
{
public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		//Left
		traverse(node->getLeftChild());

		//Us
		cout << node->getValue() << " ";

		//Right
		traverse(node->getRightChild());
	}
};

template <typename T>
class TreeToSortedVector : public TreeTraversal<T>
{
private:
	vector<T> items{};

public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		//Left
		traverse(node->getLeftChild());

		//Us
		items.push_back(node->getValue());

		//Right
		traverse(node->getRightChild());
	}

	vector<T> &getItems()
	{
		return items;
	}
};


template <typename T>
class RecursiveReverseOrderTraversal : public TreeTraversal<T>
{
public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		//Right
		traverse(node->getRightChild());

		//Us
		cout << node->getValue() << " ";

		//Left
		traverse(node->getLeftChild());
	}
};

template <typename T>
class IterativeInOrderTraversal : public TreeTraversal<T>
{
public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		unordered_map<BinaryNode<T>*, bool> visited{};

		//set up stack
		stack<BinaryNode<T> *> to_visit{};
		to_visit.push(node);

		//while we haven't seen all nodes in our tree
		while (to_visit.size() > 0)
		{
			//grab current node
			BinaryNode<T> *current = to_visit.top();
			to_visit.pop();

			//null check, reset if necessary
			if (current == nullptr)
			{
				continue;
			}

			//process us...maybe
			if (visited[current] == false)
			{
				//process right child
				to_visit.push(current->getRightChild());

				//haven't seen yet, add back in
				visited[current] = true;
				to_visit.push(current);

				//process left node
				to_visit.push(current->getLeftChild());
			}
			else
			{
				cout << current->getValue() << " ";
			}



		}
	}
};

template <typename T>
class IterativeLevelOrderTraversal : public TreeTraversal<T>
{
public:
	void virtual traverse(BinaryNode<T> *node)
	{
		//ensure data integrity
		if (node == nullptr)
		{
			return;
		}

		unordered_map<BinaryNode<T>*, bool> visited{};

		//set up stack
		queue<BinaryNode<T> *> to_visit{};
		to_visit.push(node);

		//while we haven't seen all nodes in our tree
		while (to_visit.size() > 0)
		{
			//grab current node
			BinaryNode<T> *current = to_visit.front();
			to_visit.pop();

			//null check, reset if necessary
			if (current == nullptr)
			{
				continue;
			}

			//process us
			cout << current->getValue() << " ";

			//process left node
			to_visit.push(current->getLeftChild());

			//process right child
			to_visit.push(current->getRightChild());

		}
	}
};


#endif // !TREE_TRAVERSAL_H
