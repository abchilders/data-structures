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

#include "WordCounter.h"

string WordCounter::generateBinary(int num)
{
	if (num == 0)
	{
		return "0"; 
	}
	string output = ""; 
	while (num > 0)
	{
		int result = num & 1; 
		if (result == 1)
		{
			output = "1" + output; 
		}
		else
		{
			output = "0" + output; 
		}
		num = num >> 1; 
	}
	return output; 
}

WordCounter::WordCounter(string the_word = "", int freq = 0)
{
	_word = the_word; 
	_frequency = freq; 
}

void WordCounter::setWord(string w)
{
	_word = w; 
}

void WordCounter::setFrequency(int f)
{
	_frequency = f; 
}

string WordCounter::getWord() const
{
	return _word; 
}

int WordCounter::getFrequency() const
{
	return _frequency; 
}

// operator overloads for use in a priority queue 
bool operator< (const WordCounter& left, const WordCounter& right) 
{
	return left.getFrequency() < right.getFrequency(); 
}

bool operator> (const WordCounter& left, const WordCounter& right)
{
	return left.getFrequency() > right.getFrequency(); 
}

bool operator== (const WordCounter& left, const WordCounter& right)
{
	return left.getFrequency() == right.getFrequency(); 
}