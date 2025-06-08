#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Complete the hackerrankInString function below.
string hackerrankInString(string s)
{
	string target = "hackerrank";
	int j = 0; // number of matching characters between target and s
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == target[j])
			j++;
	}
	if (j == target.length()) // if all characters in target appear in s
		return "YES";
	else
		return "NO";
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string s;
		getline(cin, s);

		string result = hackerrankInString(s);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}