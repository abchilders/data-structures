/*
QUESTIONS:
How do you initialize vectors and queues? (see constructor)
	-I made it work somehow, but I don't know if that's the "right" way
	-SEE BELOW 

When returning a reference to a vector: do I say "return &vect_name" or just 
	"return vect_name," letting the function signature take care of the 
	reference? That wouldn't make sense... so what's the syntax? 
	-I tried looking this up myself but I'd like confirmation. 
	-IT FIGURES IT OUT BY ITSELF, NO CHANGE NEEDED 
*/

/*
TO-DO: 
Complete tick(). 
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

queue<Customer> CheckoutLine::getLine()
{
	return _line; 
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

//DEBUG
int CheckoutLine::getTick()
{
	return _tick_count; 
}

void CheckoutLine::tick()
{
	if (isEmpty() == false)
	{
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