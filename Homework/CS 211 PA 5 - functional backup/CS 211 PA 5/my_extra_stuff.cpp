// This function opens up an input stream for the purpose of reading
//		a TSV file into a vector of strings, where each item in the 
//		vector represents one actor or movie. 
//vector<string> readTSVinput(string prompt);

/*
int main(void)
{
	// Read actor information from a TSV into a vector of strings,
		// each containing tab-separated info about one actor. 
	string actor_prompt = "Enter the name of a TSV file containing information about actors \n (e.g. reduced.tsv): ";
	vector<string> actor_info = readTSVinput(actor_prompt);
	// DEBUG
	cout << "Read in actor info." << endl;

	// Read movie information from a TSV into a vector of movies,
	// each containing tab-separated info about one movie. 
	string movie_prompt = "Enter the name of a TSV file containing information about movies \n (e.g. reducedTitles.tsv): ";
	vector<string> movie_info = readTSVinput(movie_prompt);
	cout << "Read in movie info." << endl;

	// Load the information from the movie_info vector into a list
	// (hashtable) of Movie objects. 
	unordered_map<string, Movie*> movies{};
	for (int i = 0; i < movie_info.size() - 1; i++)
	{
		// Create Movie object for the current movie. 
		Movie* next_movie = new Movie;

		// Split the row i into a vector of attribute values for the
		// current movie. 
		vector<string> attribute_info = StringSplitter::split(movie_info[i], "\t");

		// Set the movie's ID and primary title. We won't add actors
		// yet. 
		string movie_id = attribute_info[MOVIE_ID_INDEX];
		string movie_title = attribute_info[MOVIE_TITLE_INDEX];
		next_movie->setId(movie_id);
		next_movie->setTitle(movie_title);

		// Now add this movie to our hashtable of Movie objects, where 
		// the movie ID is the key and the corresponding Movie object
		// is the value. 
		movies[movie_id] = next_movie;

		// DEBUG: 
		//cout << movies[movie_id]->getId() << endl; 
		//cout << movies[movie_id]->getTitle() << endl << endl; 
	}
	cout << "Added all movies." << endl;

	// Load the information from the actor_info vector into a list
	// (hashtable) of Actor objects. 
	unordered_map<string, Actor*> actors{};
	for (int i = 0; i < actor_info.size() - 1; i++)
	{
		// Create Actor object for the current actor. 
		Actor* next_actor = new Actor;

		// Split the row i into a vector of attribute values for the
		// current actor. 
		vector<string> attribute_info = StringSplitter::split(actor_info[i], "\t");

		// Set the actor's ID and name. Add movies that this actor is 
		// in.
		string actor_id = attribute_info[ACTOR_ID_INDEX];
		string actor_name = attribute_info[ACTOR_NAME_INDEX];
		string actor_in_movies = attribute_info[ACTOR_IN_MOVIES_INDEX];
		next_actor->setId(actor_id);
		next_actor->setName(actor_name);

		// Separate out the list of movies in which an actor has 
		// participated. Then add movies to the Actor object from this 
		// list. 
		vector<string> movies_known_for = StringSplitter::split(actor_in_movies, ",");
		for (auto j : movies_known_for)
		{
			next_actor->addMovie(movies[j]);
		}

		// Now add this actor to our hashtable of Actor objects, where 
		// the actor ID is the key and the corresponding Actor object
		// is the value. 
		actors[actor_id] = next_actor;
	}

	task3(actors);

	return 0;
}
*/

/*
vector<string> readTSVinput(string prompt)
{
	string filename;
	string file_contents = "";
	string temp = "";

	// Get the name of the text file.
	cout << prompt;
	getline(cin, filename);

	// Open up the input stream with the given text file.
	// Read the text file into a string.
	ifstream input_stream{ filename };
	if (input_stream.is_open() == true)
	{
		// Ignore the first line of input.
		getline(input_stream, temp);
		// vector<string> columns = StringSplitter::split(temp, "\t");
		// num_columns = columns.size();

		// Then put the rest of the TSV file contents into a
		// string.
		while (input_stream.good() == true)
		{
			getline(input_stream, temp);
			file_contents += (temp + "\n");
		}
	}
	input_stream.close();

	// DEBUG
	cout << "This is a test for input stream success." << endl;
	cout << file_contents;
	cout << endl << endl << endl;


	// Now split this string into a vector containing all the
	// pieces of information.
	vector<string> TSV_info =
		StringSplitter::split(file_contents, "\n");

	// DEBUG
	cout << "This is a test for StringSplitter success." << endl;
	for (auto item : TSV_info)
	{
		cout << item << endl << endl;
		cout << "DONE" << endl;
	}
	cout << endl;

	return TSV_info;
} */

//// Task 4B: Outputting Connected Path
	//// Continuing from Task #4A, you must output the path of movies that 
	//// connect the two actors using the shortest possible number of movie
	//// connections. 
	//void task4b(string actor_id_1, string actor_id_2)
	//{
	//	// validate actor input
	//	if (_actors[actor_id_1] == nullptr)
	//	{
	//		cout << actor_id_1 << " doesn't exist in the file." << endl;
	//	}
	//	if (_actors[actor_id_2] == nullptr)
	//	{
	//		cout << actor_id_2 << " doesn't exist in the file." << endl;
	//	}

	//	// if both actors are valid, then start searching. 
	//	unordered_map<Movie*, int> visited_movies{};
	//	unordered_map<Actor*, int> visited_actors{};
	//	vector<string> path{};
	//	path = findActorPath(_actors[actor_id_1], _actors[actor_id_2],
	//		visited_movies, visited_actors, nullptr, path);
	//	
	//	// output the path
	//	for (auto movie : path)
	//	{
	//		cout << movie << endl; 
	//	}
	//}

	//vector<string> findActorPath(Actor* origin, Actor* target,
	//	unordered_map<Movie*, int>& visited_movies,
	//	unordered_map<Actor*, int>& visited_actors, Movie* calling_movie,
	//	vector<string>& reverse_path)
	//{
	//	// mark our current actor as visited
	//	visited_actors[origin]++;

	//	// did we find the actor we were passed?
	//	if (origin == target) // compare objects or targets?
	//	{
	//		// push back the movie that called me 
	//		reverse_path.push_back(calling_movie->getId());
	//		return reverse_path; 
	//	}

	//	// if we didn't find the actor, keep searching.
	//	// look through all of this actor's movies
	//	for (auto movie : origin->getMovies())
	//	{
	//		// if we haven't visited this movie yet
	//		if (visited_movies[movie] < 1)
	//		{
	//			// mark it as visited
	//			visited_movies[movie]++;

	//			// then search though this movie's actors 
	//			for (auto actor : movie->getActors())
	//			{
	//				// only search through actors that we haven't visited yet
	//				if (visited_actors[actor] < 1)
	//				{
	//					reverse_path = findActorPath(actor, target, visited_movies, 
	//						visited_actors, movie, reverse_path);
	//					if (reverse_path.size() == 0)
	//					{
	//						continue; 
	//					}
	//					else
	//					{
	//						reverse_path.push_back(movie->getId()); 
	//					}
	//				}
	//			}
	//		}
	//	}
	//	
	//	return reverse_path;
	//}