#pragma once
#ifndef MOVIE_SEARCH_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>

#include "Movie.h"
#include "Actor.h"
#include "StringSplitter.h"
using namespace std;
class MovieSearch
{
private:
    unordered_map<string, Actor*> _actors;
    unordered_map<string, Movie*> _movies;

public:
    void loadFile(string file_name)
    {
        ifstream input_file{ file_name };
        if (input_file.is_open() == true)
        {
            //clear out header data
            string line;
            getline(input_file, line);

            //now, read actual data
            while (input_file.good() == true)
            {
                getline(input_file, line);
                vector<string> data = StringSplitter::split(line, "\t");

                //Important bits in our data:
                //[0] - actor ID
                //[1] - actor name
                //[5] - actor movies (in CSV format)
                string actor_id = data[0];
                string actor_name = data[1];
                vector<string> movie_ids = StringSplitter::split(data[5], ",");

                //object to represent current actor
                Actor* some_actor = nullptr;

                //instead of creating this actor immediately, check to
                //see if actor is already known in our graph.
                if (_actors.find(actor_id) == _actors.end())
                {
                    some_actor = new Actor{};
                    some_actor->setName(actor_name);
                    some_actor->setId(actor_id);

                    //attach actor in graph
                    _actors[some_actor->getId()] = some_actor;
                }

                //repopulate some_actor with graph value
                some_actor = _actors[actor_id];

                //attach movies to actor
                for (auto movie_id : movie_ids)
                {
                    //Because this particular movie_id might have
                    //already been created, we need to ensure
                    //that the movie isn't in the graph before we
                    //create that movie again
                    Movie* some_movie = nullptr;
                    if (_movies.find(movie_id) == _movies.end())
                    {
                        some_movie = new Movie{};
                        some_movie->setId(movie_id);
                        _movies[some_movie->getId()] = some_movie;
                    }
                    some_movie = _movies[movie_id];
                    
                    //attach actor to movie and movie to actor
                    some_actor->addMovie(some_movie);
                    some_movie->addActor(some_actor);
                }
            }
        }
    }

};


#define MOVIE_SEARCH_H
#endif // !MOVIE_SEARCH_H
