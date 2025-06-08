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

// This file is based on MovieSearch.h provided by 
// Adam Carter. 

#include "MovieSearch.h"

void MovieSearch::loadActorFile(string file_name)
{
	ifstream in_stream{ file_name }; 
	if (in_stream.is_open() == true)
	{
		// clear out header data
		string line; 
		getline(in_stream, line); 

		// now, read actual data
		while (in_stream.good() == true)
		{
			getline(in_stream, line); 

			// split this line of data into attributes
			vector<string> data = StringSplitter::split(line, "\t"); 

			// Get the important items from our data: actor ID, 
			// name, and movies in CSV format 
			string actor_id = data[ACTOR_ID_INDEX]; 
			string actor_name = data[ACTOR_NAME_INDEX]; 
			vector<string> movie_ids = 
				StringSplitter::split(data[ACTOR_MOVIES_INDEX], ","); 

			// set up object to represent current actor
			Actor* some_actor = nullptr; 

			// is this actor already known in our graph? if not, 
			// create an object for them
			if (_actors.find(actor_id) == _actors.end())
			{
				some_actor = new Actor{};
				some_actor->setName(actor_name); 
				some_actor->setId(actor_id); 

				// attach actor to graph
				_actors[some_actor->getId()] = some_actor; 
			}

			// repopulate some_actor with graph value, just in case
			// weird stuff happened along the way
			some_actor = _actors[actor_id]; 

			// attach movies to actor
			for (auto movie_id : movie_ids)
			{
				// set up object for this movie
				Movie* some_movie = nullptr; 

				// if the movie isn't already in the graph, go ahead
				// and create an object for it, and attach it to 
				// the graph
				if (_movies.find(movie_id) == _movies.end())
				{
					some_movie = new Movie{}; 
					some_movie->setId(movie_id); 
					_movies[some_movie->getId()] = some_movie; 
				}
				// confirm value of some_movie just in case something
				// weird happened along the way
				some_movie = _movies[movie_id]; 

				// attach actor to movie and movie to actor
				some_actor->addMovie(some_movie); 
				some_movie->addActor(some_actor); 
			}
		}
	}
}

void MovieSearch::loadMovieFile(string file_name)
{
	ifstream in_stream{ file_name };
	if (in_stream.is_open() == true)
	{
		// clear out header data
		string line;
		getline(in_stream, line);

		// now, read actual data
		while (in_stream.good() == true)
		{
			getline(in_stream, line);

			// split this line of data into attributes
			vector<string> data = StringSplitter::split(line, "\t");

			// Get the important items from our data: movie id
			// and movie title
			string movie_id = data[MOVIE_ID_INDEX];
			string movie_title = data[MOVIE_TITLE_INDEX];

			// is this movie already known in our graph? if not, we
			// won't bother processing it 
			if (_movies.find(movie_id) == _movies.end())
			{
				continue; 
			}

			// otherwise, let's add the movie title to the
			// corresponding movie
			_movies[movie_id]->setTitle(movie_title); 
		}
	}
}

bool MovieSearch::isValidActorId(string actor_id)
{
	if (_actors[actor_id] == nullptr)
	{
		return false; 
	}
	else
	{
		return true; 
	}
}

bool MovieSearch::findActor(Actor* origin, Actor* target,
	unordered_map<Movie*, int>& visited_movies,
	unordered_map<Actor*, int>& visited_actors)
{
	// mark our current actor as visited
	visited_actors[origin]++;

	// did we find the actor we were passed?
	if (origin == target) // compare objects or targets?
	{
		return true;
	}

	// if we didn't find the actor, keep searching.
	// look through all of this actor's movies
	for (auto movie : origin->getMovies())
	{
		// if we haven't visited this movie yet
		if (visited_movies[movie] < 1)
		{
			// mark it as visited
			visited_movies[movie]++;

			// then search though this movie's actors 
			for (auto actor : movie->getActors())
			{
				// only search through actors that we haven't visited yet
				if (visited_actors[actor] < 1)
				{
					bool found = findActor(actor, target, visited_movies, visited_actors);

					// if we hit a dead end, keep going until we've exhausted the entire 
					// connected graph (i.e. we get to the top of the call stack and we 
					// still haven't found a connection)
					if (found == false)
					{
						continue;
					}

					// otherwise, we've found our connection
					else
					{
						return true;
					}
				}
			}
		}
	}

	// if we've traversed entire DFS path and found nothing, then return false
	return false;
}

void MovieSearch::outputPath(Actor* start, Actor* end,
	unordered_map<Actor*, Movie*>& pre_actors,
	unordered_map<Movie*, Actor*>& pre_movies)
{
	// we're going to walk backwards from the end actor to 
	// the start actor, and then reverse that walk so that we have 
	// the walk from start to end in the proper order 
	Actor* current_actor = end; 
	stack<string> path{}; 
	while(current_actor != start)
	{
		// put the movie parent into a stack (for reversibility later)
		path.push(pre_actors[current_actor]->getTitle()); 

		// now walk back to the previous actor in the path
		current_actor = pre_movies[pre_actors[current_actor]]; 
	}

	// output everything in the stack 
	cout << "Actors are connected through movies: " << endl; 
	while (path.empty() == false)
	{
		cout << "* " << path.top() << endl; 
		path.pop(); 
	}
}

void MovieSearch::task3(string actor_id)
{
	// Check for valid actor ID input. 
	if (isValidActorId(actor_id) == false)
	{
		cout << "Invalid actor ID given." << endl; 
		return; 
	}

	// Fetch the requested actor and their information.
	Actor* the_actor = _actors[actor_id];
	cout << "Actor name: " << the_actor->getName() << endl;
	cout << "Movies: ";
	vector<Movie*> actor_movies = the_actor->getMovies();
	for (int i = 0; i < actor_movies.size() - 1; i++)
	{
		cout << actor_movies[i]->getTitle() << "; ";
	}
	cout << actor_movies[actor_movies.size() - 1]->getTitle() << endl;

	return; 
}

void MovieSearch::task4a(string actor_id_1, string actor_id_2)
{
	// validate actor input
	if (isValidActorId(actor_id_1) == false
		|| isValidActorId(actor_id_2) == false)
	{
		cout << "Invalid actor ID given." << endl; 
		return; 
	}

	// if both actors are valid, then start searching. 
	unordered_map<Movie*, int> visited_movies{};
	unordered_map<Actor*, int> visited_actors{};
	bool found = findActor(_actors[actor_id_1], _actors[actor_id_2],
		visited_movies, visited_actors);

	// output whether we found a connection or not
	if (found == true)
	{
		cout << "Actors are connected" << endl;
	}
	else
	{
		cout << "Actors are not connected" << endl;
	}

	return; 
}

void MovieSearch::task4b(string actor_id_1, string actor_id_2)
{
	// validate input
	if (isValidActorId(actor_id_1) == false
		|| isValidActorId(actor_id_2) == false)
	{
		cout << "Invalid actor ID given. " << endl;
		return;
	}

	// if the first actor and the second actor are the same, just 
	// return and don't bother with the whole process
	if (actor_id_1 == actor_id_2)
	{
		cout << "They are the same actor!" << endl; 
		return; 
	}

	// hashtables to store which actor led to which movie, and 
	// vice versa 
	unordered_map<Actor*, Movie*> actor_parents{}; 
	unordered_map<Movie*, Actor*> movie_parents{};
	Actor* origin = _actors[actor_id_1]; 
	Actor* target = _actors[actor_id_2]; 

	queue<Actor*> to_process{}; 
	to_process.push(origin); 

	while (to_process.empty() == false)
	{
		Actor* current_actor = to_process.front(); 
		to_process.pop(); 

		for (auto movie : current_actor->getMovies())
		{
			// if we've already seen this movie, skip it
			if (movie_parents[movie] != nullptr)
			{
				continue;
			}

			// note the movie's "parent" actor, which also serves as a 
			// record of having been visited
			movie_parents[movie] = current_actor; 

			// then start processing each actor connected to this 
			// movie
			for (auto actor : movie->getActors())
			{
				// if we've already seen this actor, skip them
				if (actor_parents[actor] != nullptr || actor == origin)
				{
					continue;
				}

				// note this actor's "parent" movie, which also 
				// serves as a record of having been visited
				actor_parents[actor] = movie;

				// is this actor our target? 
				// if so, call the helper function to output
				// the sequence of movies, because all this 
				// indentation is getting ridiculous 
				if (actor == target)
				{
					outputPath(origin, target, actor_parents, movie_parents);
					return; 
				}

				// enqueue the actor for processing
				to_process.push(actor); 
			}
		}
	}

	// if we get to the end of our queue and we still haven't 
	// found the target, they're disconnected. 
	cout << "Actors are not connected" << endl; 
	return; 
}

void MovieSearch::task5(string actor_id, int max_degree)
{
	if (isValidActorId(actor_id) == false)
	{
		cout << "Invalid actor ID given." << endl; 
		return; 
	}

	int degree = 1;
	unordered_map<Actor*, int> visited_actors{};
	unordered_map<Movie*, int> visited_movies{}; 
	Actor* the_actor = _actors[actor_id];
	cout << "Actor: " << the_actor->getName() << endl;

	// our list of actors that need to be processed for 
	// a certain degree level
	queue<Actor*> process_now{};

	// actors that will be processed after we're done with 
	// current degree level
	queue<Actor*> process_next{};
	process_next.push(the_actor);

	// until degree is more than max_degree
	while (degree <= max_degree)
	{
		// a variable to help me put commas between actors
		bool no_comma = true;

		// move the list of actors we were going to process into 
		// our current queue to consider
		swap(process_now, process_next);

		// set up output
		cout << "Degree " << degree << " Connections: ";

		while (process_now.empty() == false)
		{
			Actor* current_actor = process_now.front();
			process_now.pop();
			visited_actors[current_actor]++;

			// for each movie associated with the current actor, add other 
			// actors at <degree> level 
			for (auto movie : current_actor->getMovies())
			{
				if (visited_movies[movie] > 0)
				{
					continue; 
				}
				// add other actors at degree level
				// and, for each actor in this list, increase degree by 1.
				// repeat from while loop
				vector<Actor*> movie_actors = movie->getActors();
				for (int i = 0; i < movie_actors.size(); i++)
				{
					if (visited_actors[movie_actors[i]] > 0)
					{
						continue;
					}
					if (no_comma == false)
					{
						cout << ", ";
					}
					cout << movie_actors[i]->getName();
					process_next.push(movie_actors[i]);
					no_comma = false;
				}
			}
		}
		cout << endl;
		degree++;
	}
	return;
}