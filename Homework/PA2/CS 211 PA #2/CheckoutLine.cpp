/*
Assignment: PA #2
Description: This program simulates a day at Jacks Mart. It expects a number
	of checkstands to simulate, and creates a CSV file containing the results
	of the simulation, as well as printing the average customer wait time to
	the screen.
Author: Alex Childers
HSU ID: 013145324
Completion Time: 10.5 hours
In completing this program, I received help from the following people:
	N/A
*/

#include "CheckoutLine.h"
#include <iostream>

CheckoutLine::CheckoutLine() : _line_name(0), _tick_count(0),
	_line(queue<Customer>{}), _served_customers(vector<Customer>{})
{
	// intentionally empty
}

CheckoutLine::CheckoutLine(int new_line_name = 0, int new_tick_count = 0,
	queue<Customer> new_line = queue<Customer>{}, 
	vector<Customer> new_served_customers = vector<Customer>{})
{
	_line_name = new_line_name; 
	_tick_count = new_tick_count;
	_line = new_line; 
	_served_customers = new_served_customers;
}

int CheckoutLine::getLineName()
{
	return _line_name; 
}

bool CheckoutLine::isEmpty()
{
	return (_line.empty()); 
}

void CheckoutLine::addCustomer(Customer some_customer)
{
	_line.push(some_customer); 
}

vector<Customer>& CheckoutLine::getServicedCustomers()
{
	return _served_customers; 
}

void CheckoutLine::tick()
{
	// if there is a customer in the checkstand
	if (isEmpty() == false)
	{
		// calculate a departure time for the first customer in line if they don't 
		// already have one
		Customer* front_customer = &_line.front(); 
		if (front_customer->getDepartureTime() == 0)
		{
			front_customer->setDepartureTime(_tick_count + 
				front_customer->getServiceTime());
		}

		// if the time elapsed is greater than the first customer's departure
		// time, the customer has completed the checkout process.
		if (_tick_count > front_customer->getDepartureTime())
		{
			_served_customers.push_back(*front_customer); 
			_line.pop(); 
		}
	}
	_tick_count++;
}