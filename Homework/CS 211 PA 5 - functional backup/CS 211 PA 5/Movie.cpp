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

// This file is provided by Adam Carter.

#include "Movie.h"

void Movie::addActor(Actor* actor)
{
    _actors[actor->getId()] = actor;
}

vector<Actor*> Movie::getActors()
{
    vector<Actor*> result{};
    for (auto item : _actors)
    {
        result.push_back(item.second);
    }
    return result;
}

void Movie::setId(string id)
{
    _id = id;
}

string Movie::getId() const
{
    return _id;
}

void Movie::setTitle(string title)
{
	_primary_title = title; 
}

string Movie::getTitle() const
{
	return _primary_title;
}
