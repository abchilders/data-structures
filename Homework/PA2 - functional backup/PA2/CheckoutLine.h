/*
QUESTIONS:
Should I add setters/getters for *all* private member variables or is it not 
	required here?
	- MAYBE ADD THEM FOR NOW AND THEN DELETE THEM IF I END UP NOT USING THEM?
	- I DON'T THINK I'LL NEED THEM 
	- NAH DON'T NEED
*/

/*
Assignment: PA #2
Description: This program simulates a day at Jacks Mart. It expects a number
of checkstands to simulate, and creates a CSV file containing the results
of the simulation, as well as printing the average customer wait time to
the screen.
Author: Alex Childers
HSU ID: 013145324
Completion Time: ENTER HERE
In completing this program, I received help from the following people:
LIST PEOPLE HERE
*/

#ifndef CHECKOUTLINE_H
#define CHECKOUTLINE_H

#include "Customer.h"
#include <vector>
#include <queue>

class CheckoutLine
{
public:
	// default constructor
	CheckoutLine(); 

	// constructor
	CheckoutLine(int new_line_name, int new_tick_count,
		queue<Customer> new_line, vector<Customer> new_served_customers); 

	// getter for _line_name
	int getLineName(); 

	// getter for _line
	queue<Customer> getLine(); 

	// returns true if the _line queue is empty
	bool isEmpty(); 

	// adds a customer to _line queue
	void addCustomer(Customer some_customer); 

	// returns a reference to the vector of serviced customers
	vector<Customer>& getServicedCustomers();

	// increases _tick_count by one and does tick-specific actions for the 
	// checkstand
	void tick();

	//DEBUG
	// returns _tick_count
	int getTick();

private:
	int _line_name; 
	int _tick_count; 
	queue<Customer> _line; 
	vector<Customer> _served_customers; 
};

#endif /* CHECKOUTLINE_H */