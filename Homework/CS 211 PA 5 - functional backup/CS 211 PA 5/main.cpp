/*
Assignment: PA #5 - Graphs
Description: This program builds a graph from the IMDB actor database,
	which will allow us to determine relationships between actors. 
Author: Alex Childers
HSU ID: 013145324
Completion Time: 12 hours + 12:45 - 
In completing this program, I received help from the following people:
	N/A
*/

/*
QUESTIONS: 
- How does the program know how many tab-separated columns are
	in the TSV file? Should I hard-code it, or should the 
	program determine that? I think I should hard-code it, 
	because our program is dependent on the format of the TSV
	file to know where the names and IDs are anyway.
- There is some repetition in how we process reduced.tsv for actors and
	reducedTitles.tsv for movies. I want to condense these into functions.
	Where should I put these functions? (In the header file, in this main
	file?)
	- Define the functions in the header file. Main.cpp should be short. 
- Is there a certain way we should implement each of the tasks? (i.e. how
	will the user select task 3, task 4a, task 4b?)
	- do them all in a row, NOT menu
*/

/*
TO DO: 
- Do task 2. 
- Write helper function to validate input for actor IDs. 
*/
#include "MovieSearch.h"

using namespace std;  

int main(void)
{
	MovieSearch search{}; 

	// Get input from the TSV file of actors' information. 
	cout << "Enter actor's information file (e.g. reduced.tsv): ";
	string user_input; 
	getline(cin, user_input); 
	search.loadActorFile(user_input); 

	// Set up and execute Task 3: listing an actor's movies.
	cout << "TASK 3" << endl; 
	cout << "Enter Actor ID: "; 
	string first_actor; 
	getline(cin, first_actor); 
	search.task3(first_actor);
	cout << endl; 
	
	// Set up and execute Task 4A: determining if two actors are connected.
	cout << "TASK 4A" << endl; 
	cout << "Enter First Actor ID: ";
	getline(cin, first_actor); 
	cout << "Enter Second Actor ID: "; 
	string second_actor; 
	getline(cin, second_actor); 
	search.task4a(first_actor, second_actor); 
	cout << endl;

	// Set up and execute Task 4B: outputting the path that connects two 
	// actors. 
	cout << "TASK 4B" << endl;
	cout << "Enter First Actor ID: ";
	getline(cin, first_actor);
	cout << "Enter Second Actor ID: ";
	getline(cin, second_actor);
	search.task4b(first_actor, second_actor);
	cout << endl;

	// Set up and execute Task 5: Listing Associations by Degree
	cout << "TASK 5 " << endl; 
	cout << "Enter Actor ID: "; 
	getline(cin, first_actor); 
	cout << "Enter Max Degree: "; 
	string max_degree;
	getline(cin, max_degree); 
	search.task5(first_actor, stoi(max_degree)); 

	return 0; 
}
