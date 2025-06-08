#include <iostream>
#include <string>
#include <queue>
#include "sorting\Sorting.h"
#include "ADTs\BinarySearchTree.h"
#include "ADTs\TreeTraversal.h"
#include "ADTs\RandomNumberGenerator.h"

using namespace std;

void mergeTrees()
{
    BinarySearchTree<int> tree1{};
    BinarySearchTree<int> tree2{};
    RandomNumberGenerator rng{};

    for(int i = 0; i < 15; i++)
    {
        tree1.addElement(rng.getRandomNumber(1, 100));
        tree2.addElement(rng.getRandomNumber(1, 100));
    }

    BinaryNode<int>* root1 = tree1.getRoot();
    BinaryNode<int>* root2 = tree2.getRoot();
    BinaryNode<int>* merged = nullptr;

    //LAB TASK: merge these two trees into a single, valid BST
    //NOTE: may be helpful to write a recursive helper function
	// Assume we put all values inside of root1 tree. 
	queue<BinaryNode<int>*> to_add{}; // things to add to tree
	to_add.push(root2);
	while (to_add.empty() == false) // some condition
	{
		// grab first thing from queue
		BinaryNode<int>* current = to_add.front(); 
		to_add.pop(); 

		if (current != nullptr)
		{
			// add children to the queue 
			to_add.push(current->getLeftChild()); 
			to_add.push(current->getRightChild()); 
			current->setLeftChild(nullptr); 
			current->setRightChild(nullptr); 

			// put current in its proper place 
			BinaryNode<int>* temp_root = root1; 
			while (true) // while no null child has been found where we can put null child 
			{
				// assign temp_root to be either its left or right child 
				// compare temp_root to current, then update temp_root based on value of current
				if (current->getValue() < temp_root->getValue())
				{
					if (temp_root->getLeftChild() == nullptr)
					{
						temp_root->setLeftChild(current);
						break; // gets you out of the while loop 
					}
					temp_root = temp_root->getLeftChild(); 
				}
				else
				{
					if (temp_root->getRightChild() == nullptr)
					{
						temp_root->setRightChild(current); 
						break; // gets you out of the while loop, you stop searching for a node to fill
					}
					temp_root = temp_root->getRightChild();
				}
			}
		}
	}
	merged = root1; 

    //if done correctly, should be in-order
    RecursiveInOrderTraversal<int> traversal{};
    traversal.traverse(merged);

}

bool areTheSame(BinaryNode<int>* tree1, BinaryNode<int>* tree2)
{
	if (tree1 == nullptr && tree2 != nullptr)
	{
		return false;
	}
	else if (tree1 != nullptr && tree2 == nullptr)
	{
		return false;
	}
	else if (tree1 == nullptr && tree2 == nullptr)
	{
		return true; 
	}
	// same value?
	if (tree1->getValue() == tree2->getValue())
	{
		return areTheSame(tree1->getLeftChild(), tree2->getLeftChild())
			&& areTheSame(tree1->getRightChild(), tree2->getRightChild());
	}
	else
	{
		return false; 
	}
}

// only works if all values within trees are unique values
void subtreeTest(BinaryNode<int>* tree1, BinaryNode<int>* tree2)
{
    //LAB TASK: determine if tree2 is a subtree of tree1
    //Note: writing a recursive helper function may be useful
	BinaryNode<int>* front = tree1; 
	while (front != nullptr)
	{
		if (tree2->getValue() == front->getValue())
		{
			// TO DO: matches trees, see if same 
			if (areTheSame(tree2, front) == true)
			{
				cout << "Is a subtree"; 
				return; 
			}
			else
			{
				cout << "Not a subtree" << endl; 
				return; 
			}
		}
		else if (tree2->getValue() < front->getValue())
		{
			// left side
			front = front->getLeftChild(); 
		}
		else
		{
			// right side 
			front = front->getRightChild(); 
		}
	}
	// if front pointer is null, that means tree2 value does not exist in tree1 
	cout << "Not a subtree. " << endl; 
}

void commonAncestor(BinaryNode<int>* tree, int val1, int val2)
{
    //LAB TASK: determine closest parent for val1 and val2
	if (tree->getValue() == val1 || tree->getValue() == val2)
	{
		cout << tree->getValue() << endl; 
		return; 
	}
	if (tree->getValue() > val1 && tree->getValue() > val2)
	{
		commonAncestor(tree->getLeftChild(), val1, val2);
	}
	else if (tree->getValue() < val1 && tree->getValue() < val2)
	{
		commonAncestor(tree->getRightChild(), val1, val2); 
	}
	else
	{
		// where they split
		cout << tree->getValue() << endl; 
	}
	// what if val1 and val2 are not in the tree? 
}


int main(void)
{
    BinarySearchTree<int> tree1{};
    BinarySearchTree<int> tree2{};

    tree1.addElement(10);
    tree1.addElement(5);
    tree1.addElement(7);
    tree1.addElement(2);
    tree1.addElement(9);
    tree1.addElement(15);
    tree1.addElement(11);
    tree1.addElement(12);
    tree1.addElement(20);
    tree1.addElement(25);
    tree1.addElement(27);
    tree1.addElement(30);

    tree2.addElement(20);
    tree2.addElement(25);
    tree2.addElement(27);
    tree2.addElement(30);

	// COMMENTED OUT FOR TESTING 
    // mergeTrees();

    //should be TRUE
    subtreeTest(tree1.getRoot(), tree2.getRoot());

    tree2 = BinarySearchTree<int>{};
    tree2.addElement(5);
    tree2.addElement(9);
    tree2.addElement(27);
    tree2.addElement(25);

    //should be FALSE
    subtreeTest(tree1.getRoot(), tree2.getRoot());

    //should be 5
    commonAncestor(tree1.getRoot(), 5, 7);

    //should be 11
    commonAncestor(tree1.getRoot(), 30, 12);

    //should be "NONE"
    commonAncestor(tree1.getRoot(), 30, 100);

    
    return 0;
}
