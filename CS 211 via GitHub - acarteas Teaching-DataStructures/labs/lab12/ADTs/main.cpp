#include <iostream>
#include <string>
#include "ADTs\LinkedList.h"
#include "ADTs\BinarySearchTree.h"
#include "ADTs\TreeTraversal.h"

using namespace std;

//Removes all duplicats from a linked list
//e.g. 1 -> 4 -> 1 -> 3 -> 1 -> 4 -----> 1 -> 4 -> 3
ListNode<int>* removeDuplicates(ListNode<int> *front)
{
	// Have a data structure to keep track of all the numbers we've seen so far. 
	unordered_map<int, int> number_count; 
	
	ListNode<int> next = front; 
	return nullptr;
}

//reorders the supplied binary search tree such that the supplied node is the new root of the tree
BinarySearchTree<int>* makeNewRoot(BinarySearchTree<int> *tree, BinaryNode<int> *new_root)
{
    //Task #2 TODO: implement
	return nullptr;
}

//Converts a roman numeral into its integer representation
//e.g. I -> 1
//    IV -> 4
//    VI -> 6
//    XL -> 40
int romanToInt(string numeral)
{
    //Task #3 TODO: implement 
	return -1;
}

/*
Flip a bit to win.  Given a string of bits (1/0), where can you flip a single bit such that 
you create the longest sequence of 1s
a. e.g. 11011101111 -> 11011111111 (length = 8)

*/
string bitFlip(string sequence)
{
    //TASK #6 TODO: implement!
	return sequence;
}

int main(void)
{

    //task #1 test code
    cout << "Task #2 test code" << endl;
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
        cout << front << " ";
    }
    cout << " (expected: 1 4 3)" << endl;
    cout << endl << endl;

    //task #2 test code
    cout << "Task #3 test code" << endl;
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
    cout << "III as INT: " << romanToInt("III");
    cout << "IV as INT: " << romanToInt("IV");
    cout << "VI as INT: " << romanToInt("VI");
    cout << "MCM as INT: " << romanToInt("MCM");
    cout << "MDCXLVXI AS INT: " << romanToInt("MDCXLVXI");
    cout << endl << endl;

    //task #4 test code
    cout << "Task #4 test code" << endl;
    cout << "11011101111 -> " << bitFlip("11011101111") << endl;
    cout << "10011011000111110 -> " << bitFlip("10011011000111110") << endl;
    cout << endl << endl;
    return 0;
}