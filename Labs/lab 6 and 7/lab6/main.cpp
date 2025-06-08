#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <queue> // for PQ
#include <functional> // for making a min-queue
#include <vector> // also needed for PQ 
#include "sorting\Sorting.h"
#include "ADTs\BinarySearchTree.h"
#include "ADTs\TreeTraversal.h"
#include "ADTs\RandomNumberGenerator.h"

using namespace std;

// Adam's getHeight
// efficiency: O(N)
int getHeight(BinaryNode<int>* node)
{
	if (node == nullptr)
	{
		return -1; 
	}
	int left_height = getHeight(node->getLeftChild()); 
	int right_height = getHeight(node->getRightChild()); 
	int max_height = left_height; 
	if (right_height > left_height)
	{
		max_height = right_height; 
	}
	return 1 + max_height; 
}

// my getHeight
/*
int getHeight(BinaryNode<int>* node)
{
	// node is nullptr
	if (node == nullptr)
	{
		return -1; 
	}

	// node is the root of the tree, and the only node in the tree
	else if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
	{
		return 0; 
	}

	// the height of whichever child is bigger, + 1 is the height 
	int left_child_height = getHeight(node->getLeftChild());
	int right_child_height = getHeight(node->getRightChild()); 
	if (left_child_height > right_child_height)
	{
		return left_child_height + 1; 
	}
	else
	{
		return right_child_height + 1; 
	}
} */ 

// Adam's isAvl
// Efficiency: O(N^2)
bool isAvlHelper(BinaryNode<int>* node)
{
	if (node == nullptr)
	{
		return true; 
	}
	int left_height = getHeight(node->getLeftChild()); 
	int right_height = getHeight(node->getRightChild()); 
	if (abs(left_height - right_height) < 2)
	{
		return isAvlHelper(node->getLeftChild())
			&& isAvlHelper(node->getRightChild()); 
	}
	else
	{
		return false; 
	}
}

bool isAvl(BinarySearchTree<int>* tree)
{
	return isAvlHelper(tree->getRoot()); 
}

/* error: forgot to recursively check rest of tree 
bool isAvl(BinarySearchTree<int> *tree)
{
	// is the tree a BST? 
		// yes, because the given tree is of type BinarySearchTree

	// is the difference between height of right and left subtrees <= 1? 
	BinaryNode<int>* root = tree->getRoot(); 
	if (root == nullptr)
	{
		return true; 
	}
	int left_height = getHeight(root->getLeftChild());
	int right_height = getHeight(root->getRightChild()); 
	int difference = abs(left_height - right_height); 
	if (difference > 1)
	{
		return false; 
	}
	return true; 
}
*/

// Adam's rotateLeft - identical to mine
BinaryNode<int>* rotateLeft(BinaryNode<int>* original_root)
{
	BinaryNode<int>* new_root = original_root->getRightChild();
	original_root->setRightChild(new_root->getLeftChild()); 
	new_root->setLeftChild(original_root); 
	return new_root; 
}

// my rotateLeft - identical to Adam's, but with comments
/*
BinaryNode<int>* rotateLeft(BinaryNode<int>* original_root)
{
	// At the node whose left and right height differ by more than one: 
	// Let original_root = the node where the imbalance is
		// done

	// let new_root = original_root->getRightChild()
	BinaryNode<int>* new_root = original_root->getRightChild();

	// set original_root's right child = new_root's left child
	original_root->setRightChild(new_root->getLeftChild());

	// set new_root's left child = original_root
	new_root->setLeftChild(original_root);

    return new_root;
} */

// Adam's isFull
bool isFullHelper(BinaryNode<int>* node)
{
	if (node == nullptr)
	{
		return true; 
	}
	if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
	{
		// 0 children
		return true; 
	}
	else if (node->getLeftChild() == nullptr || node->getRightChild() == nullptr)
	{
		// 1 child - we know that at least one child has contents, and at least one child is nullptr
		return false; 
	}
	else
	{
		// 2 children - neither is nullptr
		return isFullHelper(node->getRightChild())
			&& isFullHelper(node->getLeftChild()); 
	}
}

bool isFull(BinarySearchTree<int>* tree)
{
	if (tree == nullptr)
	{
		return true; 
	}
	return isFullHelper(tree->getRoot()); 
}

// my version
/*
bool isFull(BinaryNode<int>* node)
{
	if (node == nullptr)
	{
		return true; 
	}
	
	if (node->getLeftChild() != nullptr && node->getRightChild() != nullptr)
	{
		// two children
		return isFull(node->getLeftChild()) && isFull(node->getRightChild()); 
	}
	else if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
	{
		// no children
		return true;
	}
	else
	{
		// 1 child
		return false; 
	}
} 

bool isFull(BinarySearchTree<int> *tree)
{
	BinaryNode<int>* tree_root = tree->getRoot(); 
	return isFull(tree_root); 
	// how to perform on tree directly? 
} */

// Adam's levelOrderTraversal
// can't do level-order traversal recursively - it's 
// way easier to just use a queue
void levelOrderTraversal(BinarySearchTree<int> *tree)
{
	if (tree == nullptr)
	{
		return; 
	}
	queue<BinaryNode<int>*> node_queue{}; 
	node_queue.push(tree->getRoot());
	while (node_queue.empty() == false)
	{
		BinaryNode<int>* top = node_queue.front(); 
		node_queue.pop();
		if (top != nullptr)
		{
			cout << top->getValue() << ", "; 
			node_queue.push(top->getLeftChild()); 
			node_queue.push(top->getRightChild()); 
		}
	}
}

// mine
/*
void levelOrderTraversal(BinarySearchTree<int> *tree)
{
	queue<BinaryNode<int>*> ordered_nodes{};
	if (tree->getRoot() != nullptr)
	{
		ordered_nodes.push(tree->getRoot());
	}
	while (ordered_nodes.empty() == false)
	{
		BinaryNode<int>* top_node = ordered_nodes.front();
		ordered_nodes.pop(); 

		// push only if not null
		if (top_node->getLeftChild() != nullptr)
		{
			ordered_nodes.push(top_node->getLeftChild());
		}
		if (top_node->getRightChild() != nullptr)
		{
			ordered_nodes.push(top_node->getRightChild());
		}
		cout << top_node->getValue() << " "; 
	}
	return;
} */

// Adam's isComplete
bool isComplete(BinarySearchTree<int>* tree)
{
	if (tree == nullptr)
	{
		return true;
	}
	queue<BinaryNode<int>*> node_queue{};
	node_queue.push(tree->getRoot());
	bool has_null = false; 
	while (node_queue.empty() == false)
	{
		BinaryNode<int>* top = node_queue.front();
		node_queue.pop();
		if (top != nullptr)
		{
			if (has_null == true)
			{
				return false; 
			}
			cout << top->getValue() << ", ";
			node_queue.push(top->getLeftChild());
			node_queue.push(top->getRightChild());
		}
		else
		{
			has_null = true; 
		}
	}
}


// a tree w/ positive balance factor can't be complete, also - could do recursive check 
// mine
/*
bool isComplete(BinarySearchTree<int>* tree)
{
	// create modified level order traversal which flags a bool var
	// whenever a null child is found; if another non-null child is 
	// found after that null child, return false

	queue<BinaryNode<int>*> ordered_nodes{};
	bool null_spot_found = false; 
	if (tree->getRoot() != nullptr)
	{
		ordered_nodes.push(tree->getRoot()); 
	}
	while (ordered_nodes.empty() == false)
	{
		BinaryNode<int>* top_node = ordered_nodes.front();
		ordered_nodes.pop();

		// push only if not null
		if (top_node->getLeftChild() != nullptr)
		{
			if (null_spot_found == true)
			{
				return false; 
			}
			ordered_nodes.push(top_node->getLeftChild());
		}
		else
		{
			null_spot_found = true; 
		}

		if (top_node->getRightChild() != nullptr)
		{
			if (null_spot_found == true)
			{
				return false; 
			}
			ordered_nodes.push(top_node->getRightChild());
		}
		else
		{
			null_spot_found = true; 
		}
	} 

    return true;
} */

// Midterm Question #1: use PQ to solve first midterm question. 
int findNthSmallest(vector<int> numbers, int n)
{
	priority_queue<int, vector<int>, greater<int>> sorted{};
	for (auto i : numbers)
	{
		sorted.push(i);
	}
	int nth_smallest = 0; 
	for (int i = 0; i < n; i++)
	{
		nth_smallest = sorted.top();
		sorted.pop();
	}
	return nth_smallest; 
}

// Midterm Question #2: Complete a function that determines 
// whether or not the supplied vector of integers is a
// binary min-heap. 

bool isMinHeap(vector<int> numbers)
{
	// A vector is a binary min-heap if the parent is "more
	// important" (i.e. smaller) than its child. 
	// So, we need to recursively check if each parent in 
	// the vector is larger than both its children. 
	
	// check: 0 nodes
	if (numbers.size() == 0)
	{
		return true; 
	}

	// check: 1 node
	if (numbers.size() == 1)
	{
		return true; 
	}

	// check: 2+ nodes
}

int main(void)
{
	// given a vector that represents effort expenditure
	// e.g. {1, 1, 2, 3}
	// we need to combine these efforts into a single value 
	// such that the amount of effort expended is minimized. 
	// Example: 
	// {1, 1, 2, 3} -> {2, 2, 3} (2 effort)
	// {2, 2, 3} -> {4, 3} (4 effort)
	// {4, 3} -> {7} (7 effort)
	// total effort = 2 + 3 + 7 = 13
	priority_queue<int, vector<int>, greater<int>> pq{}; 
	vector<int> effort{ 1, 1, 2, 3 }; 

	// add everything to our pq
	for (auto i : effort)
	{
		pq.push(i); 
	}
	int total_effort = 0; 
	while (pq.size() > 1)
	{
		int first = pq.top();
		pq.pop(); 
		int second = pq.top(); 
		pq.pop(); 
		int temp = first + second; 
		total_effort += temp; 
		pq.push(temp); 
	}
	cout << "Total effort: " << total_effort << endl;

	// Challenge: Midterm question number 1
	// This is a test for findNthSmallest(test_nums, i).
	vector<int> test_nums = { 1, 3, 2, 5, 4, 9, 8, 6 }; 
	for(int i = 1; i <= test_nums.size(); i++)
	{
		cout << "The " << i << " smallest number in test_nums is " << findNthSmallest(test_nums, i) << endl; 
	}

    BinarySearchTree<int> tree{};
    
    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: -1)" << endl;

    tree.addElement(10);
    tree.addElement(5);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 1)" << endl;

    tree.addElement(15);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 1)" << endl;

    tree.addElement(12);
    tree.addElement(20);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 2)" << endl;

    tree.addElement(11);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: FALSE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 3)" << endl;

    tree.addElement(13);
    tree.addElement(1);
    tree.addElement(7);

    cout << boolalpha << "Is Full: " << isFull(&tree) << " (expected: TRUE)" << endl;
    cout << boolalpha << "Is Complete: " << isComplete(&tree) << " (expected: FALSE)" << endl;
    cout << boolalpha << "Is AVL: " << isAvl(&tree) << " (expected: TRUE)" << endl;
	cout << boolalpha << "Height: " << getHeight(tree.getRoot()) << " (expected: 3)" << endl;
	cout << "Level-order traversal: ";
	levelOrderTraversal(&tree);
	cout << "(expected: 10, 5, 15, 1, 7, 12, 20, 11, 13)" << endl; 
	cout << "    -as corrected by Alex to account for missing 7" << endl; 
	cout << "(expected: 10, 5, 15, 1, 12, 20, 11, 13) - original" << endl;

    //Note: this breaks the tree structure because our BST isn't informed of the new root.  Must be done last
	cout << endl;
	BinaryNode<int>* rotated = rotateLeft(tree.getRoot());
    RecursivePreOrderTraversal<int> traversal{};
    traversal.traverse(rotated);
	cout << endl;
    
    //rotate again just for fun
    rotated = rotateLeft(rotated);
    traversal.traverse(rotated);
    return 0;
}
