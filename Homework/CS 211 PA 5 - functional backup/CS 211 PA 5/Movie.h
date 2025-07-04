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

// This file is provided by Adam Carter, annotated with my own
//		comments. 

#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include "Actor.h"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;
class Actor;
class Movie
{
private:
	// This is a hashtable of the actors in the movie.
	// The actor's ID is the key; the actor's Actor object
	//		is the value. 
    unordered_map<string, Actor*> _actors;

	// This is the movie's ID. 
    string _id;

	// This is the movie's primary title (added by Alex). 
	string _primary_title; 

public:
	// Adds an Actor to the hashtable of this movie's actors. 
    void addActor(Actor* actor);

	// Returns a vector containing all the Actor objects 
	// associated with this movie.
    vector<Actor*> getActors();

	// Sets the ID of this movie. 
    void setId(string id);

	// Gets the ID of this movie. 
    string getId() const;

	// Sets the primary name of this movie. 
	void setTitle(string title); 

	// Gets the primary name of this movie.
	string getTitle() const; 
};

#endif