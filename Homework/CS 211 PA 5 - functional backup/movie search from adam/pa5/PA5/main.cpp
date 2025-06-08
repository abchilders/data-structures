#include <vector>
#include <string>
#include <iostream>

#include "Actor.h"
#include "Movie.h"
#include "MovieSearch.h"

using namespace std;

int main(void)
{
    MovieSearch search{};

    cout << "Enter actors file: ";
    string user_input;
    getline(cin, user_input);
    search.loadFile(user_input);

    return 0;
}