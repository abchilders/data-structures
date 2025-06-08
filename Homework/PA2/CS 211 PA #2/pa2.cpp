/*
Assignment: PA #2
Description: This program simulates a day at Jacks Mart. It expects a number
	of checkstands to simulate, and creates a CSV file containing the results
	of the simulation, as well as printing the average customer wait time to 
	the screen. 
Author: Alex Childers
HSU ID: 013145324
Completion Time: 10.5
In completing this program, I received help from the following people:
	N/A
*/

#include "CheckoutLine.h"
#include "CsvWriter.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std; 

const string OUT_FILE = "results.csv"; 
const int SIMULATION_LENGTH = 720; 

int main()
{
	// prompt user for the number of checkstands to simulate
	int num_checkstands = 0; 
	cout << "How many checkstands would you like to simulate? " << endl; 
	cin >> num_checkstands; 
	while (num_checkstands < 1)
	{
		cout << "Invalid checkstand amount. " << endl; 
		cout << "You should have at least one checkstand." << endl; 
		cout << "Try again: ";
		cin >> num_checkstands; 
	}

	// create a data structure that contains the appropriate number of
	//		checkstands
	vector<CheckoutLine*> checkstands; 
	for (int i = 0; i < num_checkstands; i++)
	{
		CheckoutLine* new_checkstand = new CheckoutLine(i, 0,
			queue<Customer>{}, vector<Customer>{});
		checkstands.push_back(new_checkstand); 
	}

	// set the probability of a new customer arriving equal to 0 
	int prob_new_cust = 0;  

	// for each minute in the simulation, generate new customers as needed,
	// simulate the checkstands, etc. 
	for (int i = 0; i < SIMULATION_LENGTH; i++)
	{
		// Determine if a new customer has arrived. 
		// if random number between 0 and 4 <= probability of new customer 
		// arriving, a new customer has arrived. generate it and place it in
		// a checkstand. 
		if ((rand() % 5) <= prob_new_cust)
		{
			// Create a new customer. 
			prob_new_cust = 0; 
			Customer new_cust;
			new_cust.setCustomerId(Customer::_id_counter); 
			Customer::_id_counter++; 
			new_cust.setArrivalTime(i); 
			new_cust.setServiceTime((rand() % 4) + 1); 

			// Add the customer to a checkstand, and update the customer's line
			// number.
			bool found_checkstand = false;
			unsigned int i = 0;
			while (found_checkstand == false && i < checkstands.size())
			{
				if (checkstands[i]->isEmpty() == true)
				{
					new_cust.setLineName(i);
					checkstands[i]->addCustomer(new_cust);
					found_checkstand = true;
				}
				i++;
			}
			if (found_checkstand == false)
			{
				int check_id = rand() % checkstands.size();
				new_cust.setLineName(check_id);
				checkstands[check_id]->addCustomer(new_cust);
			}
		}
		// else, if random number > prob_new_cust, increment probability of new
		// customer arriving by 1
		else
		{ 
			prob_new_cust++; 
		}

		// Now, process each checkstand. 
		for (auto j : checkstands)
		{
			j->tick(); 
		}
	}

	// put all the _served_customers by each checkout line into 1 vector
	// (and delete those CheckoutLine pointers while you're at it)
	int num_serviced_customers = 0; 
	for (auto i : checkstands)
	{
		num_serviced_customers += i->getServicedCustomers().size(); 
	}
	vector<Customer> all_custs;
	vector<Customer> serviced_per_line;
	all_custs.reserve(num_serviced_customers);
	for (auto i : checkstands)
	{
		serviced_per_line = i->getServicedCustomers();
		all_custs.insert(all_custs.end(), serviced_per_line.begin(),
			serviced_per_line.end());
		delete i;
	}

	// start writing to CSV writer (and calculate average wait time along the way)
	int cum_wait_time = 0; 
	CsvWriter writer; 
	writer.addText("Customers created: ");
	writer.addText(to_string(num_serviced_customers)); 
	writer.nextLine(); 
	writer.addText("Customer ID");
	writer.addText("Arrival"); 
	writer.addText("Time to Check Out");
	writer.addText("Departure");
	writer.addText("Total Wait");
	writer.addText("Line Number"); 
	writer.nextLine(); 
	for (auto i : all_custs)
	{
		cum_wait_time += i.getTotalWaitTime();
		writer.addText(to_string(i.getCustomerId()));
		writer.addText(to_string(i.getArrivalTime())); 
		writer.addText(to_string(i.getServiceTime())); 
		writer.addText(to_string(i.getDepartureTime())); 
		writer.addText(to_string(i.getTotalWaitTime()));
		writer.addText(to_string(i.getLineName())); 
		writer.nextLine(); 
	}

	// output results to CSV file
	string to_output = writer.toCsvString(); 
	ofstream results{ OUT_FILE }; 
	results << to_output; 
	results.close(); 

	// output average customer wait time to screen
	cout << "Average customer wait time was " << (cum_wait_time / all_custs.size())
		<< " minutes." << endl;

	return 0; 
}