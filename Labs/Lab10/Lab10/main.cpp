#include <unordered_map> //hash table
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "StringSplitter.h"
using namespace std;

// This function builds a concordance (sorted word frequency distribution) 
//		from a supplied file. 
// This function will be completed in lab as a class exercise after the PA #4 
//		checkin. 
void concordance(string text)
{
	unordered_map<string, int> frequencies{};
	vector<string> keys{}; 
	vector<string> words = StringSplitter::split(text, " "); 
	for (auto word : words)
	{
		frequencies[word]++; 
	}
	// The above lines are all that is neede to build a frequency distribution
	// for PA #4 (step #1), minus the vector<string> keys{}. 

	// If we had used a map, this step would be unnecessary, but Adam wanted
	// to show us how to use an unordered map. 
	for (auto kvp : frequencies)
	{
		keys.push_back(kvp.first); // not needed for PA 4
	}

	// sort the keys
	sort(keys.begin(), keys.end()); // not needed for PA 4
	for (auto key : keys)	 // could be adapted for when you put the items into 
							// the priority queue 
							// See Lab 9 for examples. 
	{
		cout << key << ": " << frequencies[key] << endl; 
	}
}

// Accepts a single string.
// Outputs true when each character in the string only occurs once. 
// This function should NOT be case sensitive - 'e' and 'E' should be treated as
//		the same. 
bool hasUniqueChars(string text)
{
	// convert the entire string to lowercase 
	unordered_map<char, int> frequency {};
	char temp;
	for (auto i: text)
	{
		temp = tolower(i); 
		if (frequency[temp] > 0)
		{
			return false; 
		}
		else
		{
			frequency[temp]++; 
		}
	}
	return true; 
}

// This function accepts two strings.
// It outputs true when they are anagrams of each other.
// (e.g. "anagram" can be reworded into "nag a ram")
bool isAnagram(string first, string second)
{
	int first_length(0), second_length(0); 

	// to hold the characters of the first word
	unordered_map<char, int> first_word{};
	for (auto i : first)
	{
		if (i != ' ')
		{
			first_word[i]++;
			first_length++;
		}
	}

	// to hold the characters of the second word
	unordered_map<char, int> second_word{};
	for (auto i : second)
	{
		if (i != ' ')
		{
			second_word[i]++;
			second_length++; 
		}
	}

	// do the two given words have the same amount of characters?
	if (first_length != second_length)
	{
		return false; 
	}

	// do all the characters in the first string match all the characters in the second string? 
	for (auto kvp : first_word)
	{
		// if the value is not equal to that character's value in second_word
		if (kvp.second != second_word[kvp.first])
		{
			return false; 
		}
	}
	return true; 
}

string mostCommonSubstring(string text, int size)
{
	// if the size of the substring is greater than the length of text, we
	// can't possibly get a valid substring
	if (size > text.length())
	{
		return ""; 
	}

	// generate each substring, and keep track of each substring's frequency
	// in an unordered map 
	unordered_map<string, int> substr_freqs{}; 
	string temp = ""; 
	for (int i = 0; i <= text.length() - size; i++)
	{
		temp = text.substr(i, size); 
		substr_freqs[temp]++; 
	}

	// figure out which substring is the most frequent
	string max_key = ""; 
	int max_freq = 0; 
	for (auto s : substr_freqs)
	{
		if (s.second > max_freq)
		{
			max_key = s.first; 
			max_freq = s.second; 
		}
	}
	return max_key;
}

int main(void)
{
	// concordance test
	ifstream input_file{ "test_file.txt" }; 
	string all_lines{};
	if (input_file.is_open() == true)
	{
		while (input_file.good() == true)
		{
			string line = ""; 
			getline(input_file, line); 
			all_lines += " " + line; 
		}
	}
	concordance(all_lines); 

	//unique chars test
	cout << boolalpha;
	cout << "***unique characters test***" << endl;

	//test case #1
	cout << "abcde: " <<
		hasUniqueChars("abcde") 
		<< " (expected: true)"
		<< endl;
 
	//test case #2:
	cout << "aaaa: " <<
		hasUniqueChars("aaaa")
		<< " (expected: false)"
		<< endl;

	//test case #3:
	cout << "(empty string): " <<
		hasUniqueChars("")
		<< " (expected: true)"
		<< endl;

	//test case #4:
	cout << "abcdea: " <<
		hasUniqueChars("abcdea")
		<< " (expected: false)"
		<< endl;

	//anagram tests
	cout << endl << endl;
	cout << "***anagram tests***" << endl;

	//test case #1:
	cout << "tab, bat: " <<
		isAnagram("tab", "bat")
		<< " (expected: true)"
		<< endl;

	//test case #2
	cout << "bat, tab: " <<
		isAnagram("bat", "tab")
		<< " (expected: true)"
		<< endl;

	//test case #3
	cout << "(empty), (empty): " <<
		isAnagram("", "")
		<< " (expected: true)"
		<< endl;

	//test case #4
	cout << "dog, cat: " <<
		isAnagram("dog", "cat")
		<< " (expected: false)"
		<< endl;

	//test case #5
	cout << "castles, castle: " <<
		isAnagram("castles", "castle")
		<< " (expected: false)"
		<< endl;

	//test case #6
	cout << "bat, tabb: " <<
		isAnagram("bat", "tabb")
		<< " (expected: false)"
		<< endl;

	//most common substring
	cout << endl << endl << "***Most common substring***" << endl;

	//test case #1
	cout << "abcabcdefdefabc. 3: " <<
		mostCommonSubstring("abcabcdefdefabc", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #2
	cout << "defdefabcabc, 3: " <<
		mostCommonSubstring("defdefabcabc", 3)
		<< " (expected: def)"
		<< endl;

	//test case #3
	cout << "aaabbcccc, 1: " <<
		mostCommonSubstring("aaabbcccc", 1)
		<< " (expected: c)"
		<< endl;

	//test case #4
	cout << "abcdefhijklmnopqrstuvwxyz, 4: " <<
		mostCommonSubstring("abcdefhijklmnopqrstuvwxyz", 4)
		<< " (expected: abcd)"
		<< endl;

	//test case #5
	cout << "abc, 5: " <<
		mostCommonSubstring("abc", 5)
		<< " (expected: NULL)"
		<< endl;

	//test case #6
	cout << "(Empty), 1: " <<
		mostCommonSubstring("", 1)
		<< " (expected: NULL)"
		<< endl;

	//test case #7
	cout << "abcabcab, 3: " <<
		mostCommonSubstring("abcabcab", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #8
	cout << "abcabcab, 0: " <<
		mostCommonSubstring("abcabcab", 0)
		<< " (expected: NULL)"
		<< endl;

	return 0;
}