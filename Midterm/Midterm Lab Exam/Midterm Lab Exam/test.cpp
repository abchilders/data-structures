/*
#include <cstdlib>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

using namespace std; 

class BinaryNode
{
public:
	int value; 
	BinaryNode *left; 
	BinaryNode *right; 
};

class LinkedList
{
public:
	int value; 
	LinkedList* next; 
};

// Problem 1
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

// Problem 2
bool isMinHeap(vector<int> numbers)
{
	// parent	= (i-1)/2
	//			= (size - 2)/2
	for (int i = 0; i < (numbers.size() - 2) / 2; i++)
	{
		// left
		if (numbers[i] > numbers[2 * i + 1])
		{
			return false; 
		}
		
		// right
		if (numbers[i] > numbers[2 * i + 2])
		{
			return false; 
		}
	}
	return true; 
}

// Problem 3
void reverseOrderTraversal(BinaryNode *root)
{
	// check nullness
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

// Problem 4
LinkedList* reverseLinkedList(LinkedList *root)
{
	LinkedList* previous_node{}; 
	LinkedList* current_node = root; 
	LinkedList* next_node{}; 

	while (current_node != nullptr)
	{
		next_node = current_node->next; 
		current_node->next = previous_node; 
		previous_node = current_node;
		current_node = next_node; 
	}
	return previous_node; 
}

// helper function for problem 5
int getHeight(BinaryNode *root)
{
	if (root == nullptr)
	{
		return -1; 
	}

	int left_height = getHeight(root->left); 
	int right_height = getHeight(root->right); 
	int max_height = left_height; 
	if (right_height > left_height)
	{
		max_height = right_height; 
	}
	return max_height + 1; // height of child, plus yourself 
}

// Problem 5
bool isAvl(BinaryNode *root)
{
	// check for nullness
	if (root == nullptr)
	{
		return true; 
	}

	// get balance factor from left and right heights
	int left_height = getHeight(root->left); 
	int right_height = getHeight(root->right); 

	if (abs(left_height - right_height) < 2)
	{
		return isAvl(root->left) && isAvl(root->right); 
	}
	else
	{
		return false; 
	}
} 

vector<int> sortStack(stack<int> &some_stack)
{
	stack<int> temp_stack{};
	vector<int> results{};
	int min(0), top(0); 

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

		if (temp_stack.empty == false)
		{
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
	}

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
}*/