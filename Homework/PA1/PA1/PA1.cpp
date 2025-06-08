/*
Assignment: PA #1 - Inventory Management
Description: This program will take an inventory CSV file as input;
	allow the user to add, update, or remove items from the inventory; 
	and then output the resulting inventory back into the CSV file when 
	the user requests to exit the program. 
Author: Alex Childers
HSU ID: 013145324
Completion Time: 6.5 hours
In completing this program, I received help from the following people: 
	Adam Carter
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std; 

// This function expects an input stream and a vector of strings, and returns 
// nothing. It will insert three items at a time (one row of inventory) into a vector. 
void insertRow(ifstream &data, vector<string> &vect);

// This function expects a vector of strings and a string, and returns an int. 
// It will search every third index in the vector, and return the index
// of the string if it is found, and -1 otherwise.
int searchItems(string search_term, vector<string> &vect);

// This function expects a vector of strings, and returns nothing. It will 
// add an item requested by the user into the vector. 
void addToVector(vector<string> &vect);

// This function expects a vector of strings, and returns nothing.
// It will update an item in the vector as requested by the user. If the item
// doesn't exist, it will do nothing. 
void updateVector(vector<string> &vect);

// This function expects a vector of strings, and returns nothing.
// It will remove an item in the vector as requested by the user. 
void removeFromVector(vector<string> &vect);

int main(void)
{
	// Load the contents of inventory.csv into two vectors: one for the 
	// column headings, and one for the contents of the inventory.
	vector<string> header{};
	vector<string> inventory{}; 
	ifstream in_stream{ "inventory.csv" };
	if (in_stream.is_open() == true)
	{
		string item;

		// Insert first 3 words into header.
		insertRow(in_stream, header); 

		// Insert the rest of the items from inventory.csv into inventory.
		while (in_stream.good() == true)
		{
			insertRow(in_stream, inventory); 
		}
	}
	in_stream.close(); 

	// Provide menu options to the user.
	int menu_selection = 0; 
	while (menu_selection != 4)
	{
		cout << "Enter the number of the option you want to select: " << endl;
		cout << "1 - Add item" << endl;
		cout << "2 - Update item" << endl;
		cout << "3 - Remove item" << endl;
		cout << "4 - Quit program" << endl;
		cin >> menu_selection; 

		switch (menu_selection)
		{
		case 1:
			addToVector(inventory); 
			cout << endl;
			break; 
		case 2:
			updateVector(inventory); 
			cout << endl; 
			break;
		case 3:
			removeFromVector(inventory);
			cout << endl; 
			break;
		case 4:
			cout << "Ending program. " << endl; 
			break; 
		default:
			cout << "Invalid selection. Try again. " << endl << endl;
		}
	}

	// Write updated inventory back to inventory.csv.
	ofstream out_stream{ "inventory.csv" }; 
	out_stream << header[0] << ","; 
	out_stream << header[1] << ",";
	out_stream << header[2] << endl; 
	for (unsigned int i = 0; i < inventory.size(); i += 3)
	{
		out_stream << inventory[i] << ","; 
		out_stream << inventory[i + 1] << ","; 
		out_stream << inventory[i + 2] << endl;
	}
	out_stream.close(); 

	return 0; 
}

void insertRow(ifstream &data, vector<string> &vect)
{
	string item = "x"; 
	getline(data, item, ',');
	if (item != "")
	{
		vect.push_back(item);
		getline(data, item, ',');
		vect.push_back(item);
		getline(data, item);
		vect.push_back(item);
	}
	return; 
}

int searchItems(string search_term, vector<string> &vect)
{
	for (unsigned int i = 0; i < vect.size(); i += 3)
	{
		if (search_term == vect[i])
		{
			return i;
		}
	}
	return -1;
}

void addToVector(vector<string> &vect)
{
	string name = "";
	string quantity = ""; 
	string price = "";
	cout << "Enter the item name, quantity, and price, separated by "
		<< "carriage returns." << endl;

	// If the item is not already in the vector, add it to the vector. 
	cin.ignore(1000, '\n');
	getline(cin, name);
	getline(cin, quantity); 
	getline(cin, price);
	if (searchItems(name, vect) == -1)
	{
		vect.push_back(name);
		vect.push_back(quantity);
		vect.push_back(price); 
		cout << name << " successfully added to inventory." << endl;
	}
	else
	{
		cout << name << " already exists in inventory. " << endl; 
	}
	return;
}

void updateVector(vector<string> &vect)
{
	string name = ""; 
	string quantity = ""; 
	string price = "";
	cout << "Enter the existing item name, new quantity, and new price, "
		<< "separated by carriage returns." << endl;
	cin.ignore(1000, '\n');
	getline(cin, name);
	getline(cin, quantity);
	getline(cin, price);
	int item_index = searchItems(name, vect);

	// If the item is not found in the vector, don't do anything to the vector. 
	if (item_index == -1)
	{
		cout << name << " not found in inventory. " << endl;
		return;
	}

	// If the item is found, go ahead and update it.
	vect[item_index + 1] = quantity;
	vect[item_index + 2] = price; 
	cout << name << " successfully updated. " << endl;
	return; 
}

void removeFromVector(vector<string> &vect)
{
	string name = ""; 
	cout << "Enter the name of the item you want to remove." << endl;
	cin.ignore(1000, '\n');
	getline(cin, name);

	// If the item is not found in the vector, don't do anything.
	int item_index = searchItems(name, vect);
	if (item_index == -1)
	{
		cout << name << " not found in inventory. " << endl; 
		return;
	}

	// If the item is found in the vector, remove it. 
	// Information on vector::erase provided by cplusplus.com.
	vect.erase(vect.begin() + item_index, vect.begin() + item_index + 3);
	cout << name << " successfully removed." << endl; 
	return;
}