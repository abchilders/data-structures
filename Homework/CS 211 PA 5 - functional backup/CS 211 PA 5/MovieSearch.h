/*
Assignment: PA #5 - Graphs
Description: This program builds a graph from the IMDB actor database,
	which will allow us to determine relationships between actors.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 2 hours + 9:15 -
In completing this program, I received help from the following people:
	N/A
*/

// This file is adapted from MovieSearch.H provided by 
// Adam Carter. 

#ifndef MOVIE_SEARCH_H
#define MOVIE_SEARCH_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>

#include "Movie.h"
#include "Actor.h"
#include "StringSplitter.h"

class MovieSearch
{
private:
	unordered_map<string, Actor*> _actors; 
	unordered_map<string, Movie*> _movies; 

	/* important bits in our data:
		[0] = actor ID
		[1] = actor name
		[5] = actor movies (in CSV format)
	*/
	const int ID_INDEX = 0; 
	const int NAME_INDEX = 1; 
	const int MOVIES_INDEX = 5; 
public:
	// Task 1: Parsing Data
	// Converts a text file of TSV data into object form. 
	void loadActorFile(string file_name); 

	// Returns true if the given actor ID is found in the TSV file. 
	bool isValidActorId(string actor_id); 

	// Expects two actors, a hashtable of visited movies, and 
	// a hashtable of visited actors. 
	// Returns whether the second actor has been found as connected to the 
	// first actor or not. 
	bool findActor(Actor* origin, Actor* target,
		unordered_map<Movie*, int>& visited_movies,
		unordered_map<Actor*, int>& visited_actors);

	// Expects two actors and two hashtables that collectively hold
	// the paths taken to certain actors. 
	// Outputs the movie path taken between the start actor and 
	// end actor to the screen. 
	void outputPath(Actor* start, Actor* end,
		unordered_map<Actor*, Movie*>& pre_actors,
		unordered_map<Movie*, Actor*>& pre_movies);

	// Task 3: Listing an Actor's Movies
	// Lists the movies associated with the actor specified by
	// actor_id. 
	void task3(string actor_id); 

	// Task 4a: Connecting Actors
	// Searches the graph to determine whether or not two actors
	// can be connected by one or more movies. 
	void task4a(string actor_id_1, string actor_id_2); 

	// Task 4b: Outputting Connected Path
	// Outputs the path of movies that connect the two given actors
	// using the shortest possible number of movie connections.
	void task4b(string actor_id_1, string actor_id_2);

	// Task 5: Listing Associations by Degree
	// Given an actor and a degree number, this function outputs all related 
	// actors and their distanct in terms of the number of movies that separate 
	// them. 
	void task5(string actor_id, int max_degree);
};

#endif // MOVIE_SEARCH_H