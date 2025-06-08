#include <iostream>
#include <string>
#include "ADTs\LinkedList.h"
#include "ADTs\BinarySearchTree.h"
#include "ADTs\TreeTraversal.h"

using namespace std;

//Removes all duplicates from a linked list
//e.g. 1 -> 4 -> 1 -> 3 -> 1 -> 4 -----> 1 -> 4 -> 3
ListNode<int>* removeDuplicates(ListNode<int> *front)
{
	// create a data structure to hold a list of numbers we've already seen
	unordered_map<int, int> visited_numbers{}; 
	
	// start traversing the list
	ListNode<int>* current = front; 
	ListNode<int>* previous = nullptr; 
	while (current != nullptr)
	{
		// if we've seen the current number before...
		int next_val = current->getValue(); 
		if (visited_numbers[next_val] > 0)
		{
			// remove it from the list
			previous->setNext(current->getNext()); 
			ListNode<int>* temp = current; 
			current = current->getNext(); 
			delete temp; 
		}
		else
		{
			previous = current; 
			current = current->getNext();
		}
		visited_numbers[next_val]++; 
	}

	return front;
}

//reorders the supplied binary search tree such that the supplied node is the new root of the tree
BinarySearchTree<int>* makeNewRoot(BinarySearchTree<int> *tree, BinaryNode<int> *new_root)
{
	// remove all elements from tree except the new_root value
	queue<BinaryNode<int>*> to_remove{}; 
	vector<int> values{}; 
	to_remove.push(tree->getRoot());
	while (to_remove.empty() == false)
	{
		BinaryNode<int>* node = to_remove.front(); 
		to_remove.pop(); 
		if (node == nullptr)
		{
			continue; 
		}
		to_remove.push(node->getLeftChild()); 
		to_remove.push(node->getRightChild()); 
		if (node != new_root)
		{
			values.push_back(node->getValue()); 
			tree->removeElement(node->getValue()); 
		}
	}

	// now re-add them to the tree
	for (auto i : values)
	{
		tree->addElement(i); 
	}

	return tree; 
}

//Converts a roman numeral into its integer representation
//e.g. I -> 1
//    IV -> 4
//    VI -> 6
//    XL -> 40

// My implementation: 
/*
int romanToInt(string numeral)
{
	// Our reference table for translating Roman numerals to Arabic numbers. 
	unordered_map<char, int> numeral_table{}; 
	numeral_table['I'] = 1; 
	numeral_table['V'] = 5;
	numeral_table['X'] = 10;
	numeral_table['L'] = 50; 
	numeral_table['C'] = 100; 
	numeral_table['D'] = 500; 
	numeral_table['M'] = 1000; 

	int total = 0; 

	// Split the string up into a list of characters. Then process the chars. 
	// NOTICE: My processing of chars requires dual-wielding two chars at once, processing
	// them on their own, and then adding to the total. This is clunky.
	// The class solution below is more elegant - if the current numeral is less than
	// the next number, simply subtract it from the total (it all works out the same
	// (way in the end.) 

	int i = 0; 
	while (i < numeral.length())
	{
		// Consider the next two numerals. 
		char current = numeral[i]; 
		char next = numeral[i + 1]; 

		// If the current numeral is smaller than the next numeral,
		// subtract current from next. Add to running total. 
		if (numeral_table[current] < numeral_table[next])
		{
			int to_add = numeral_table[next] - numeral_table[current]; 
			total += to_add; 
			i += 2; 
		}
		else // current >= next
		{
			total += numeral_table[current]; 
			i += 1; 
		}
	}
	return total;
}
*/

// Class implementation: 
int romanToInt(string numeral)
{
	unordered_map<char, int> roman{};
	roman['I'] = 1;
	roman['V'] = 5;
	roman['X'] = 10;
	roman['L'] = 50;
	roman['C'] = 100;
	roman['D'] = 500;
	roman['M'] = 1000;

	int total = 0; 
	int current = 0; 

	// last number is always added to the total 
	for (int i = 0; i < numeral.length() - 1; i++)
	{
		current = roman[numeral[i]]; 
		if (roman[numeral[i + 1]] > current)
		{
			total -= current; 
		}
		else
		{
			total += current; 
		}
	}
	total += roman[numeral[numeral.length() - 1]]; 
	return total; 
}

/*
Flip a bit to win.  Given a string of bits (1/0), where can you flip a single bit such that 
you create the longest sequence of 1s
a. e.g. 11011101111 -> 11011111111 (length = 8)

*/
string bitFlip(string sequence) 
{
	// find the index that should be replaced 
	int max_length = 0; // largest number of 1s surrounding a 0
	int start_max_index; // index of the 0 in the middle of our longest strand of 0s
	int recent_zero_index = -1; // index of the last 0 we encountered
	int prev_zero_index = -1; // index of 0 before the last one

	// traverse the string
	for (int i = 0; i < sequence.length(); i++)
	{
		// if current element is 0: calculate difference between this 
		// zero and prev_zero_index
		if (sequence[i] == '0')
		{
			// if there's more 1s surrounding recent_zero than prev_zero: 
			// update max_length and start_max_index
			if (i - prev_zero_index > max_length)
			{
				max_length = i - prev_zero_index; 
				start_max_index = recent_zero_index; 
			}

			// update our 0 trackers
			prev_zero_index = recent_zero_index; 
			recent_zero_index = i; 
		}
	}

	// check for that last 0 we encountered
	if (sequence.length() - prev_zero_index > max_length)
	{
		start_max_index = recent_zero_index; 
	}

	// once we've got the start_max_index of the zero that needs to be flipped, 
	// flip it and return 

	sequence[start_max_index] = '1'; 
	return sequence; 
}

int main(void)
{

    //task #1 test code
    cout << "Task #1 test code" << endl;
    LinkedList<int> to_remove{};
    to_remove.addElement(1);
    to_remove.addElement(4);
    to_remove.addElement(1);
    to_remove.addElement(3);
    to_remove.addElement(1);
    to_remove.addElement(4);
    ListNode<int>* front = removeDuplicates(to_remove.getFront());
    while (front != nullptr)
    {
        cout << front->getValue() << " ";
		front = front->getNext(); 
    }
    cout << " (expected: 1 4 3)" << endl;
    cout << endl << endl;

    //task #2 test code
    cout << "Task #2 test code" << endl;
    BinarySearchTree<int> tree{};
    tree.addElement(1);
    tree.addElement(2);
    tree.addElement(3);
    tree.addElement(4);
    tree.addElement(5);
    tree.addElement(6);
    BinaryNode<int>* root = tree.getRoot();
    root = root->getRightChild()->getRightChild()->getRightChild();
    BinarySearchTree<int>* reorderd = makeNewRoot(&tree, root);
    RecursivePreOrderTraversal<int> traversal{};
    traversal.traverse(reorderd->getRoot());
    cout << " (expected: varies)" << endl;
    cout << endl << endl;

    //task #3 test code
    cout << "Task #4 test code" << endl;
	cout << "III as INT: " << romanToInt("III") << endl; 
    cout << "IV as INT: " << romanToInt("IV") << endl;
    cout << "VI as INT: " << romanToInt("VI") << endl;
    cout << "MCM as INT: " << romanToInt("MCM") << endl;
    cout << "MDCXLVXI AS INT: " << romanToInt("MDCXLVXI") << endl;
    cout << endl << endl;

    //task #4 test code
    cout << "Task #4 test code" << endl;
    cout << "11011101111 -> " << bitFlip("11011101111") << endl;
    cout << "10011011000111110 -> " << bitFlip("10011011000111110") << endl;
    cout << endl << endl;
    return 0;
}