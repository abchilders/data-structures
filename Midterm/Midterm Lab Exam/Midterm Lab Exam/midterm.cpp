// Alex Childers
// Last modified 10/14/2018
// Midterm Lab Exam

#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std; 

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
// binary min-heap. (use priority queue)
// ASSUME NO EMPTY SPACES IN THE GIVEN VECTOR - IT'S ALREADY COMPLETE

bool isMinHeap(vector<int> numbers)
{
	// Assume that the given vector represents a complete binary tree. 
	// Then, the only other rule: A node's parent must be more important 
	// (smaller) than the node. Or, in other words, a node must be smaller
	// than all of its children. 
	for (unsigned int i = 0; i < (numbers.size() - 2) / 2; i++)
	{
		// is the parent less than the left child?
		if (numbers[i] > numbers[2 * i + 1])
		{
			return false; 
		}

		// is the parent less than the right child? 
		if (numbers[i] > numbers[2 * i + 2])
		{
			return false;
		}
	}
	return true; 
}

// Midterm Question #3: Given the following definition:
class BinaryNode
{
public:
	int value; 
	BinaryNode *left; 
	BinaryNode *right; 
};
// Write a recursive function that uses cout to output the BST in reverse
// sorted order (largest to smallest.) (use binary tree)
void reverseOrderTraversal(BinaryNode* root)
{
	// check for nullness
	if (root == nullptr)
	{
		return; 
	}

	// right
	reverseOrderTraversal(root->right); 

	// us
	cout << root->value << " "; 

	// left
	reverseOrderTraversal(root->left); 
	
	return; 
}

// helper function for creating BST
BinaryNode* treeInsert(BinaryNode* node, int val)
{
	if (node == nullptr)
	{
		BinaryNode* new_node = new BinaryNode{};
		new_node->value = val;  
		return new_node; 
	}

	if (val < node->value)
	{
		BinaryNode* left = treeInsert(node->left, val); 
		node->left = left; 
	}
	else
	{
		BinaryNode* right = treeInsert(node->right, val); 
		node->right = right; 
	}
	return node; 
}

// Midterm Question #4: Given the following definition of a linked list:
class LinkedList
{
public:
	int value; 
	LinkedList* next; 
};
// Write a function that reverses the order of the linked list. (use linked
// list)
LinkedList* reverseLinkedList(LinkedList* root)
{
	LinkedList* previous{};
	LinkedList* current = root;
	LinkedList* next{};
	while (current != nullptr)
	{
		next = current->next; 
		current->next = previous; 
		previous = current; 
		current = next; 
	}
	return previous; 
}

// helper for testing purposes
void traverseLinkedList(LinkedList* root)
{
	LinkedList* current = root; 
	while (current != nullptr)
	{
		cout << current->value << " "; 
		current = current->next; 
	}
}

// helper for testing purposes
void headInsert(LinkedList* &root, int val)
{
	LinkedList* new_node = new LinkedList; 
	new_node->value = val; 
	new_node->next = root; 
	root = new_node; 
	return;
}

// helper function for isAvl: getHeight 
int getHeight(BinaryNode* node)
{
	if (node == nullptr)
	{
		return -1;
	}
	int left_height = getHeight(node->left);
	int right_height = getHeight(node->right);
	int max_height = left_height;
	if (right_height > left_height)
	{
		max_height = right_height;
	}
	return 1 + max_height;
}

// Midterm Question #5: Given the above definition of a Binary Node, write
// a recursive function to determine whether or not the supplied tree is AVL.
bool isAvl(BinaryNode* root)
{
	// first off: is the tree a BST in the first place?
	// CHECK TO SEE IF THIS IS A NECESSARY PRECAUTION

	// now, we can ask: is the tree AVL compliant? 
	if (root == nullptr)
	{
		return true; 
	}
	int left_height = getHeight(root->left); 
	int right_height = getHeight(root->right); 
	if (abs(left_height - right_height) < 2)
	{
		return isAvl(root->left)
			&& isAvl(root->right); 
	}
	else
	{
		return false; 
	}
}

// Midterm Question #6: Write a function that sorts an STL stack from 
// smallest to largest. You may use one additional stack for this operation,
// but no other data structure (e.g. array) or sorting algorithm. 
vector<int> sortStack(stack<int> &some_stack)
{
	stack<int> temp_stack{}; 
	vector<int> results{};
	int min(0), top(0);

	// if you've already gone through the loop, some_stack is guaranteed
	// to be the one holding the numbers, not temp_stack - temp_stack must
	// be empty in order to re-execute this particular while loop
	while (some_stack.empty() == false)
	{
		min = some_stack.top();
		some_stack.pop();
		while (some_stack.empty() == false)
		{
			top = some_stack.top();
			if (top < min)
			{
				temp_stack.push(min);
				min = top;
			}
			else
			{
				temp_stack.push(top);
			}
			some_stack.pop();
		}
		results.push_back(min);

		// just in case nothing was put into temp_stack after some_stack was
		// emptied - say, if there was only one element left in 
		// some_stack before this
		if (temp_stack.empty() == true)
		{
			break; 
		}
		min = temp_stack.top();
		temp_stack.pop();
		while (temp_stack.empty() == false)
		{
			top = temp_stack.top();
			if (top < min)
			{
				some_stack.push(min);
				min = top;
			}
			else
			{
				some_stack.push(top);
			}
			temp_stack.pop();
		}
		results.push_back(min);
	}

	// put stuff back into stack
	for (auto i : results)
	{
		temp_stack.push(i); 
	}
	while (temp_stack.empty() == false)
	{
		some_stack.push(temp_stack.top()); 
		temp_stack.pop(); 
	}

	return results; 
}

int main(void)
{
	// Challenge: Midterm question number 1
	// This is a test for findNthSmallest(test_nums, i).
	cout << "Problem 1: " << endl; 
	vector<int> test_nums = { 1, 3, 2, 5, 4, 9, 8, 6 };
	for (unsigned int i = 1; i <= test_nums.size(); i++)
	{
		cout << "The " << i << " smallest number in test_nums is " << findNthSmallest(test_nums, i) << endl;
	}
	cout << endl; 

	// Driver for problem 2. 
	cout << "Problem 2: " << endl; 
	cout << boolalpha; 
	cout << isMinHeap(test_nums) << endl; 
	vector<int> test_2 = { 1, 2, 4, 5, 3, 8, 10, 6, 9, 7 };
	cout << isMinHeap(test_2) << ": should be true " << endl; 
	vector<int> test_3 = { 1, 2, 4, 5, 3, 8, 10, 6, 9, 7, 12 };
	cout << isMinHeap(test_3) << ": should be true " << endl; 
	vector<int> test_4 = { 5, 4, 3, 6, 7, 8, 10, 2, 9, 1 };
	cout << isMinHeap(test_4) << ": should be false " << endl; 
	cout << endl; 

	// Driver for problem 3. 
	cout << "Problem 3: " << endl; 
	// null tree
	BinaryNode* root{}; 
	cout << "Null tree: "; 
	reverseOrderTraversal(root);
	cout << endl;

	root = treeInsert(root, 5);
	cout << "One element: "; 
	reverseOrderTraversal(root);
	cout << endl; 

	root = treeInsert(root, 10);
	root = treeInsert(root, 2); 
	root = treeInsert(root, 9);
	root = treeInsert(root, 1);
	cout << "2+ elements: "; 
	reverseOrderTraversal(root);
	cout << endl; 

	root = treeInsert(root, 3); 
	reverseOrderTraversal(root); 
	cout << endl; 
	cout << endl; 

	// Driver for problem 4. 
	// null linked list
	cout << "Problem 4: " << endl; 
	LinkedList* head{}; 
	head = reverseLinkedList(head); 
	cout << "Null list reversed: ";
	traverseLinkedList(head);
	cout << endl; 

	// one item
	headInsert(head, 6); 
	head = reverseLinkedList(head); 
	cout << "One item (6) reversed: ";
	traverseLinkedList(head);
	cout << endl;

	// now MORE
	for (int i = 5; i > 0; i--)
	{
		headInsert(head, i); 
	}
	cout << "Multiple items- before: ";
	traverseLinkedList(head);
	cout << endl;
	head = reverseLinkedList(head); 
	cout << "After: ";
	traverseLinkedList(head);
	cout << endl;

	// DRIVER FOR PROBLEM 5???
	BinaryNode* root1{}; 
	cout << "A null tree is an AVL tree: " << isAvl(root1) << endl; 

	root1 = treeInsert(root1, 1); 
	cout << "A one-element tree is an AVL tree: " << isAvl(root1) << endl; 

	cout << "Is root an AVL tree?: " << isAvl(root) << endl; 

	root = treeInsert(root, 66);
	root = treeInsert(root, 67);
	root = treeInsert(root, 68);
	root = treeInsert(root, 69);
	root = treeInsert(root, 70);

	cout << "Now it shouldn't be: " << isAvl(root) << endl;

	cout << endl;

	// driver for problem 6
	cout << "Problem 6: " << endl;
	
	// null stack
	cout << "Null stack: " << endl; 
	stack<int> sample_stack{};
	vector<int> sample_results = sortStack(sample_stack);
	for (auto i : sample_results)
	{
		cout << i << " "; 
	}
	cout << endl; 

	// one item in stack 
	cout << "One item in stack: " << endl; 
	sample_stack.push(5); 
	sample_results = sortStack(sample_stack);
	for (auto i : sample_results)
	{
		cout << i << " ";
	}
	cout << endl;

	if (sample_stack.empty() == false)
	{
		cout << "sample_stack has " << sample_stack.top() << endl; 
	}

	// two or more items in stack
	cout << "Two or more items in stack: " << endl; 
	sample_stack.push(34); 
	sample_stack.push(2); 
	sample_stack.push(5); 
	sample_stack.push(43); 
	sample_stack.push(7);
	sample_stack.push(100); 
	sample_stack.push(7); 
	sample_stack.push(100); 
	sample_results = sortStack(sample_stack);
	for (auto i : sample_results)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << "Add one more for luck: " << endl; 
	sample_stack.push(99); 
	sample_results = sortStack(sample_stack);
	for (auto i : sample_results)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0; 
}