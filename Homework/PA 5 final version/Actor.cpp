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

// This file is provided by Adam Carter. 

#include "Actor.h"

void Actor::addMovie(Movie* movie)
{
    _movies[movie->getId()] = movie;
}

vector<Movie*> Actor::getMovies()
{
    vector<Movie*> result{};
    for (auto movie : _movies)
    {
        result.push_back(movie.second);
    }
    return result;
}

void Actor::setName(string name)
{
    _name = name;
}

string Actor::getName() const
{
    return _name;
}

void Actor::setId(string id)
{
    _id = id;
}
string Actor::getId() const
{
    return _id;
}