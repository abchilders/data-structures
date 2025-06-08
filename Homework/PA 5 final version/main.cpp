/*
Assignment: PA #5 - Graphs
Description: This program builds a graph from the IMDB actor database,
	which will allow us to determine relationships between actors. 
Author: Alex Childers
HSU ID: 013145324
Completion Time: 13.25 hours 
In completing this program, I received help from the following people:
	N/A
*/

#include "MovieSearch.h" 

int main(void)
{
	MovieSearch search{}; 

	// Task 1: get input from the TSV file of actor information. 
	cout << "Enter actor's information file (e.g. reduced.tsv): ";
	string user_input; 
	getline(cin, user_input); 
	search.loadActorFile(user_input); 

	// Task 2: get input from the TSV file of movie information. 
	cout << "Enter movie's information file (e.g. reducedTitles.tsv): ";
	getline(cin, user_input); 
	search.loadMovieFile(user_input);

	// Task 3: listing an actor's movies.
	cout << "TASK 3" << endl; 
	cout << "Enter Actor ID: "; 
	string first_actor; 
	getline(cin, first_actor); 
	search.task3(first_actor);
	cout << endl; 
	
	// Task 4A: determining if two actors are connected.
	cout << "TASK 4A" << endl; 
	cout << "Enter First Actor ID: ";
	getline(cin, first_actor); 
	cout << "Enter Second Actor ID: "; 
	string second_actor; 
	getline(cin, second_actor); 
	search.task4a(first_actor, second_actor); 
	cout << endl;

	// Task 4B: outputting the path that connects two actors. 
	cout << "TASK 4B" << endl;
	cout << "Enter First Actor ID: ";
	getline(cin, first_actor);
	cout << "Enter Second Actor ID: ";
	getline(cin, second_actor);
	search.task4b(first_actor, second_actor);
	cout << endl;

	// Task 5: Listing Associations by Degree
	cout << "TASK 5 " << endl; 
	cout << "Enter Actor ID: "; 
	getline(cin, first_actor); 
	cout << "Enter Max Degree: "; 
	string max_degree;
	getline(cin, max_degree); 
	search.task5(first_actor, stoi(max_degree)); 

	return 0; 
}
