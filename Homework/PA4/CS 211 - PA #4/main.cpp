/*
Assignment: PA #4: Text Encoding / Compression
Description: This program uses hash tables and priority queues to perform
	compression on input files.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 7.75 hours
In completing this program, I received help from the following people:
	N/A
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include "StringSplitter.h"
#include "WordCounter.h"

using namespace std; 

int main(void)
{
	string temp; 
	unordered_map<string, int> frequency{};

	// Get input file.
	cout << "(E)ncode or (D)ecode file: "; 
	cin >> temp;
	if (temp != "E" && temp != "e")
	{
		cout << "Decode functionality not supported. " << endl; 
		return 0; 
	}

	// To encode a file:
	// Get the input file name and open up the input stream. 
	string input_file = ""; 
	string file_contents = ""; 
	cout << "Enter file to compress: "; 
	cin >> input_file; 

	ifstream in_stream{ input_file }; 
	if (in_stream.is_open())
	{
		while (in_stream.good() == true)
		{
			// Put the file contents into a string. 
			getline(in_stream, temp); 
			file_contents += temp + " \n "; 
		}
	}
	in_stream.close(); 

	// Split that string into a vector of words, ignoring empty lines and 
	// spaces. 
	vector<string> file_words = StringSplitter::split(file_contents, " "); 

	// Record the frequency of each word in the given text file. 
	for (auto word : file_words)
	{
		// is word a newline?
		if (word.find('\n') == string::npos)
		{
			frequency[word]++;
		}
	}

	/* Record that input file name without the extension to create
	output file names later. 
	Note: I'm using a vector and piecing the <source> in 
	<source>.txt together just in case <source> itself contains periods,
	and to accommodate for file extensions other than ".txt."
	*/
	vector<string> file_name_pieces = StringSplitter::split(input_file, "."); 
	string source = ""; 
	for (int i = 0; i < file_name_pieces.size() - 1; i++)
	{
		source += (file_name_pieces[i] + "."); 
	}

	// Use the frequency recorded in step #1 to build a max-heap.
	priority_queue<WordCounter> freq_heap; 
	for (auto kvp : frequency)
	{
		WordCounter word{ kvp.first, kvp.second}; 
		freq_heap.push(word); 
	}

	// Removing items from the heap in order of importance, assign each word
	// a unique "binary" string value.
	int bin = 0; 
	while (freq_heap.empty() == false)
	{
		// Get a unique binary value. In this case, we're turning the
		// numbers bin = 0, 1, 2, etc. into binary representations, 
		// where bin++ with each new item from the heap. 
		string unique_binary = WordCounter::generateBinary(bin);

		// Remove the next word in the heap, assigning it a 
		// corresponding unique binary value. 
		WordCounter word = freq_heap.top();
		freq_heap.pop();
		frequency[word.getWord()] = stoi(unique_binary);
		bin++; 
	}

	// Change this if, for some reason, you want to write to a different
	// type of file other than .txt. 
	string extension = "txt";

	// Write to the output file the "binary" representation of the file. 
	string compressed_file = source + "compressed." + extension; 
	ofstream compressed_strm{compressed_file}; 
	for (auto word : file_words)
	{
		if (word.find('\n') == string::npos)
		{
			compressed_strm << frequency[word] << " ";
		}

		// else, if word is a newline character
		else
		{
			compressed_strm << endl; 
		}
	}
	compressed_strm.close(); 
	cout << "Encoded results written to: " << compressed_file << endl; 

	// Write the "binary" mapping to a separate file. 
	string code_file = source + "codes." + extension; 
	ofstream code_strm{ code_file }; 
	for (auto kvp : frequency)
	{
		code_strm << kvp.first << ":" << kvp.second << endl;
	}
	code_strm.close(); 
	cout << "Codes file written to: " << code_file << endl; 
	
	return 0; 
}