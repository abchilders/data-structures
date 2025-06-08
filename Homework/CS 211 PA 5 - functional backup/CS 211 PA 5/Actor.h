/*
Assignment: PA #5 - Graphs
Description: This program builds a graph from the IMDB actor database,
	which will allow us to determine relationships between actors.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 5:00 -
In completing this program, I received help from the following people:
	N/A
*/

// This file is provided by Adam Carter, with modifications and comments
//		by me. 

#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include "Movie.h"
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Movie;
class Actor
{
private:
	// A hashtable containing the list of movies this Actor
	// has been in. 
    unordered_map<string, Movie*> _movies;

	// The actor's name. 
    string _name;

	// The actor's ID. 
    string _id;

public:
	// Adds a Movie to the hashtable of Movies with which this 
	// Actor is associated. 
    void addMovie(Movie* movie);

	// Returns a vector of pointers to all the Movies this 
	// actor has been in. 
    vector<Movie*> getMovies();

	// Setter for Actor's _name. 
    void setName(string name);

	// Getter for Actor's _name. 
    string getName() const;

	// Setter for Actor's _id. 
    void setId(string id);

	// Getter for Actor's _id. 
    string getId() const;
};

#endif