#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

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

// Helper function to find the key of the item with the highest
// frequency in a hashtable of frequencies. 
template<class T>
T findMaxKey(unordered_map<T, int> freq)
{
	T max_key{}; 
	for (auto kvp: freq)
	{
		// if the frequency of the current item we're considering is 
		// greater than the frequency of what we previously 
		// considered to be the most frequent key
		if (kvp.second > freq[max_key])
		{
			// then our current item is the new most frequent thing
			max_key = kvp.first; 
		}
	}
	return max_key; 
}

void bubbleSort(int* numbers, int size)
{
	// i represents the numbers that have already been bubbled up
	// into their correct spot. we need to bubble all [size] 
	// elements into place. 
	for (int i = 0; i < size; i++)
	{
		// j represents the number of comparisons that need to be 
		// made for the current list of items that haven't been 
		// bubbled yet: total # of items - # items already sorted
		// - 1 because we make n-1 comparisons for n items
		for (int j = 0; j < size - i - 1; j++)
		{
			// if numbers[j] > numbers[j+1], swap
			if (numbers[j] > numbers[j + 1])
			{
				int temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}
	}
	return;
}

string dayWithMostRain(vector<int> rainfall)
{
	// Create a hashtable containing strings for the days of the
	// week. 
	unordered_map<int, string> days_of_week{};
	days_of_week[0] = "Sunday"; 
	days_of_week[1] = "Monday";
	days_of_week[2] = "Tuesday";
	days_of_week[3] = "Wednesday";
	days_of_week[4] = "Thursday";
	days_of_week[5] = "Friday";
	days_of_week[6] = "Saturday";

	// Create a hashtable for the rainfall data corresponding to
	// each day of the week. 
	unordered_map<int, int> rain_per_day{};

	// Read the data from the rainfall vector into rain_per_day.
	for (int i = 0; i < rainfall.size(); i++)
	{
		rain_per_day[i % 7] += rainfall[i]; 
	}

	// Find the day with the highest frequency.
	// REPLACED: int most_rain_day = findMaxKey<int>(rain_per_day);
	int most_rain_day = 0; 
	for (auto kvp : rain_per_day)
	{
		// if the frequency of the current item we're considering is 
		// greater than the frequency of what we previously 
		// considered to be the most frequent key
		if (kvp.second > rain_per_day[most_rain_day])
		{
			// then our current item is the new most frequent thing
			most_rain_day = kvp.first;
		}
	}

	// Return the string corresponding to that day of the week. 
	return days_of_week[most_rain_day];
}

// helper function for task 3
// performs an in-order traversal on the given BST, putting BST
// contents into the given vector
void inOrderTraversal(vector<int>& nums, BinaryNode* root)
{
	// check for nullness
	if (root == nullptr)
	{
		return; 
	}

	// left
	inOrderTraversal(nums, root->left); 

	// us
	nums.push_back(root->value); 

	// right 
	inOrderTraversal(nums, root->right); 

	return; 
}

vector<int> bstToVector(BinaryNode* node)
{
	// create a vector to hold the bst
	vector<int> sorted_bst{};

	// perform an in-order traversal to get the contents into the 
	// BST
	inOrderTraversal(sorted_bst, node); 

	// sort the resulting vector, just in case we weren't passed a 
	// true BST
	sort(sorted_bst.begin(), sorted_bst.end()); 

	return sorted_bst;
}

// Helper function for task 4. 
// Takes the root of a binary tree, the lowest that value could be 
// in order to be valid, and the highest that value could be in 
// order to be valid. 
bool isBstHelper(BinaryNode* root, int min, int max)
{
	// null check
	if (root == nullptr)
	{
		return true; 
	}
	// check for value validity
	if (root->value < min || root->value > max)
	{
		return false; 
	}
	// check if its subtrees are valid BSTs
	return isBstHelper(root->left, min, root->value - 1)
		&& isBstHelper(root->right, root->value, max);
}

bool isBst(BinaryNode* node)
{
	/* A tree is a BST if:
		It is a binary tree. (given by BinaryNode structure)
		All left children's values < their parent's value. 
		All right children's values >= their parent's value. 
	*/

	// Recursive solution: check if each subtree is a BST. 
	// We're passing a representation of negative infinity as the 
	// minimum value, and a representation of positive infinity as
	// the maximum value. 
	return isBstHelper(node, INT_MIN, INT_MAX);
}

char findMostCommon(string text)
{
	// Create a hashtable to contain character frequencies. 
	unordered_map<char, int> char_freq{}; 

	// Populate this hashtable with values from the given string. 
	for (auto i : text)
	{
		char_freq[i]++; 
	}

	// Now return the character with the highest frequency.
	return findMaxKey<char>(char_freq);
}

int main(void)
{
	cout << boolalpha;

	// 1: bubbleSort
	int numbers[10] = { 4, 6, 1, 4, 66, 2, 16, 4, 6, 1 };
	bubbleSort(numbers, 10);
	cout << "Problem 1: " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << numbers[i] << " ";
	}
	cout << endl;

	// 2: rainfall data
	cout << "Problem 2: " << endl;
	vector<int> sample_rainfall{};
	for (int i = 2; i < 16; i++)
	{
		sample_rainfall.push_back(i);
	}
	sample_rainfall.push_back(0);
	sample_rainfall.push_back(0);
	sample_rainfall.push_back(2364);
	cout << "Most rainfall happened on Tuesday: "
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