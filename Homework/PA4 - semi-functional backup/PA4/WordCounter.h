/*
Assignment: PA #4: Text Encoding / Compression
Description: This program uses hash tables and priority queues to perform
	compression on input files.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 6.5 hours
In completing this program, I received help from the following people:
	N/A
*/

#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <string>

using namespace std; 

class WordCounter
{
public:
	// constructor
	WordCounter(string the_word, int freq);

	// to generate unique binary number
	// this function is basically task 4 from lab 9
	static string generateBinary(int num);

	// setters
	void setWord(string w); 
	void setFrequency(int f); 

	// getters
	string getWord() const; 
	int getFrequency() const; 

private:
	string _word; 
	int _frequency; 
};

// operator overloads for use in a priority queue 
bool operator< (const WordCounter& left, const WordCounter& right);
bool operator> (const WordCounter& left, const WordCounter& right);
bool operator== (const WordCounter& left, const WordCounter& right);

#endif // WORDCOUNTER_H