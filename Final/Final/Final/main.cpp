#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std; 

class BinaryNode {
public:
	int value;
	BinaryNode *left = nullptr;
	BinaryNode *right = nullptr;
	BinaryNode(int v = 0)
	{
		value = v;
	}
};

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

// Helper function to #3. 
void inOrderTraversal(vector<int>& numbers, BinaryNode* root)
{
	// check for nullness
	if (root == nullptr)
	{
		return;
	}

	// left
	inOrderTraversal(numbers, root->left);

	// us
	numbers.push_back(root->value);

	// right
	inOrderTraversal(numbers, root->right);

	return;
}

// Expects a hashtable of containing frequency counts for keys of type
// T. Returns the key with the highest frequency.
template <class T>
T getMaxOfKey(unordered_map<T, int> hashtable)
{
	T max_t = 0;
	for (auto kvp : hashtable)
	{
		if (kvp.second > hashtable[max_t])
		{
			max_t = kvp.first;
		}
	}
	return max_t; 
}

// =============================================================

// 1.) Write a function that sorts an array using Bubble Sort.
void bubbleSort(int* numbers, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				int temp = numbers[j]; 
				numbers[j] = numbers[j + 1]; 
				numbers[j + 1] = temp; 
			}
		}
	}
}

/* 2.) Implement a function that parses the supplied vector of integers
representing rainfall data and returns the day (as a string) that has
the most rain. The input vector is formatted such that index 0 
represents Sunday and every 7th item is the same day. Thus:
	0, 7, 14... is a Sunday
	1, 8, 15... is a Monday
	2, 9, 16... is a Tuesday
	etc. 
*/
string dayWithMostRain(vector<int> rainfall)
{
	// create a hashtable to contain the names of the week
	unordered_map<int, string> days_of_week{};
	days_of_week[0] = "Sunday"; 
	days_of_week[1] = "Monday"; 
	days_of_week[2] = "Tuesday"; 
	days_of_week[3] = "Wednesday"; 
	days_of_week[4] = "Thursday"; 
	days_of_week[5] = "Friday"; 
	days_of_week[6] = "Saturday"; 

	// create a hashtable to contain the rainfall data for each day
	// rainfall.first = day of week; rainfall.second = amount of rain
	unordered_map<int, int> rain_by_day; 

	// put rainfall data into our hashtable
	for (int i = 0; i < rainfall.size(); i++)
	{
		rain_by_day[i % 7] += rainfall[i]; 
	}

	// find the day with the most total rainfall
	/*
	int max_day = 0; 
	for (auto kvp : rain_by_day)
	{
		if (kvp.second > rain_by_day[max_day])
		{
			max_day = kvp.first; 
		}
	}
	*/
	return days_of_week[getMaxOfKey<int>(rain_by_day)]; 
}

/* 3.) Write a function called bstToVector that returns the supplied
	binary search tree into a sorted STL vector. 
*/
vector<int> bstToVector(BinaryNode* node)
{
	// do an in-order traversal of the tree so that it goes into 
	// the vector already in the correct order
	vector<int> numbers{}; 
	inOrderTraversal(numbers, node);

	return numbers; 
}

/* 4: Complete the function isBst() such that the function returns TRUE
	when the supplied node represents a valid BST and FALSE otherwise. 
*/

// Helper function for isBst. 
// min and max represent the lowest value that a left child should have
// and the highest value that a right child should have, respectively.
bool isBstHelper(BinaryNode* node, int min, int max)
{
	// check for nullness
	if (node == nullptr)
	{
		return true; 
	}

	// is the current node's value invalid, given the values of its 
	// parents? 
	if (node->value < min || node->value > max)
	{
		return false;
	}

	return isBstHelper(node->left, min, node->value - 1)
		&& isBstHelper(node->right, node->value, max); 
}

bool isBst(BinaryNode* node)
{
	return(isBstHelper(node, INT_MIN, INT_MAX));
}

/* METHOD USING IN-ORDER TRAVERSAL:
bool isBst(BinaryNode* node)
{
	 A tree is a binary search tree if:
		1.) The tree is a binary tree. 
			a.) All of its nodes have at most 2 children. 
			This criterion is automatically satisfied - we're being
			passed a binary node. 
		2.) All left children of a given node must be "less" than 
			the given node's value.
		3.) All right children of a given node must be "greater than" 
			or equal to the given node's value. 
	

	// check for nullness
	if (node == nullptr)
	{
		return true; 
	}
	
	// Step 1: Do an in-order traversal of the tree. 
	vector<int> tree_nums = bstToVector(node); 

	// Step 2: Check if this vector is in order from smallest to 
	// largest. If not, the tree is not a BST. 
	for (int i = 0; i < tree_nums.size() - 1; i++)
	{
		if (tree_nums[i] > tree_nums[i + 1])
		{
			return false; 
		}
	}
	return true; 
}*/

/* 5.) Write a function called findMostCommon that finds the most 
	commonly used character in the supplied string.
*/

char findMostCommon(string text)
{
	// what if the string is empty? 
	if (text == "")
	{
		return ' '; 
	}

	// create the hashtable containing character frequencies
	unordered_map<char, int> char_freq{};
	for (auto i : text)
	{
		char_freq[i]++; 
	}
	
	// now find the character in the hashtable with the highest 
	// frequency count

	/*
	char most_frequent = text[0]; 
	for (auto kvp : char_freq)
	{
		if (kvp.second > char_freq[most_frequent])
		{
			most_frequent = kvp.first; 
		}
	}
	return most_frequent; 
	*/

	return getMaxOfKey<char>(char_freq); 
}

int main(void)
{
	cout << boolalpha; 

	// 1: bubbleSort
	int numbers[10] = { 4, 6, 1, 4, 66, 2, 16, 4, 6, 1 };
	bubbleSort(numbers, 10); 

	// 2: rainfall data
	cout << "Problem 2: " << endl;
	vector<int> sample_rainfall{}; 
	for (int i = 2; i < 16; i++)
	{
		sample_rainfall.push_back(i); 
	}
	cout << "Most rainfall happened on Saturday: "
		<< dayWithMostRain(sample_rainfall) << endl; 

	// 3: BST to sorted vector
	cout << "Problem 3: " << endl; 
	
	// null tree
	BinaryNode* root{}; 
	cout << "Null tree: "; 
	vector<int> sorted = bstToVector(root); 
	for (auto i : sorted)
	{
		cout << i << " "; 
	}
	cout << endl; 

	// one element
	root = treeInsert(root, 5); 
	cout << "One element: "; 
	sorted = bstToVector(root); 
	for (auto i : sorted)
	{
		cout << i << " "; 
	}
	cout << endl; 

	// 2+ elements
	root = treeInsert(root, 10); 
	root = treeInsert(root, 2); 
	root = treeInsert(root, 9); 
	root = treeInsert(root, 1); 
	cout << "2+ elements: "; 
	sorted = bstToVector(root); 
	for (auto i : sorted)
	{
		cout << i << " "; 
	}
	cout << endl; 

	// problem 4
	cout << "Problem 4 " << endl; 
	// null tree
	BinaryNode* root4{};
	cout << "Is a null tree a BST? Should be true: ";
	cout << isBst(root4) << endl; 

	// one element
	root4 = treeInsert(root4, 5);
	cout << "Is a one-element tree a BST? Should be true: ";
	cout << isBst(root4) << endl; 

	// 2+ elements
	root4 = treeInsert(root4, 10);
	root4 = treeInsert(root4, 2);
	root4 = treeInsert(root4, 9);
	root4 = treeInsert(root4, 1);
	cout << "Is a 2+ element BST a BST? Should be true: "; 
	cout << isBst(root4) << endl; 

	cout << "Is a wack-ass tree a BST: Should be false: "; 
	BinaryNode* wack_tree = new BinaryNode(5); 
	wack_tree->left = new BinaryNode(2); 
	wack_tree->left->left = new BinaryNode(1); 
	wack_tree->left->right = new BinaryNode(4); 
	wack_tree->left->right->left = new BinaryNode(3); 
	wack_tree->left->right->right = new BinaryNode(6); 
	wack_tree->right = new BinaryNode(8); 
	wack_tree->right->left = new BinaryNode(7); 
	wack_tree->right->right = new BinaryNode(10); 
	cout << isBst(wack_tree) << endl; 

	// Problem 5
	cout << "Problem 5: " << endl; 
	cout << "Apple: " << findMostCommon("apple") << endl; 
	cout << "Banana: " << findMostCommon("banana") << endl; 
	cout << "Empty string: " << findMostCommon("") << endl; 
	cout << "kahwoiehoiadsfkcxxxxx: " << findMostCommon("kahwoiehoiadsfkcxxxxx") << endl; 

	return 0; 
}