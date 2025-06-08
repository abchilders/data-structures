/* 
QUESTIONS:
How do I initialize the static int? (or use static variables in general)
	Do I include _id_counter in the constructor? (currently no have)
	Do I need setters and getters for _id_counter? (currently yes have)
	NO SETTERS/GETTERS NEEDED 

(In generateCustomer, how to keep track of this new customer?)
	-I think it'll be placed into the CheckoutLine _line queue.
	-But it returns nothing, so where does this customer go? 
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

#include "Customer.h"

using namespace std; 

int Customer::_id_counter = 0; 

Customer::Customer() : _customer_id(0), _arrival_time(0), _service_time(0),
	_departure_time(0), _line_name(0)
{
	// intentionally empty
}

Customer::Customer(int new_customer_id = 0, int new_arrival_time = 0,
	int new_service_time = 0, int new_departure_time = 0, 
	int new_line_name = 0)
{
	_customer_id = new_customer_id;
	_arrival_time = new_arrival_time;
	_service_time = new_service_time;
	_departure_time = new_departure_time;
	_line_name = new_line_name;
}

void Customer::setCustomerId(int new_id)
{
	_customer_id = new_id; 
}

void Customer::setArrivalTime(int new_arrival_time)
{
	_arrival_time = new_arrival_time;
}

void Customer::setServiceTime(int new_service_time)
{
	_service_time = new_service_time;
}

void Customer::setDepartureTime(int new_departure_time)
{
	_departure_time = new_departure_time; 
}

void Customer::setLineName(int new_line_name)
{
	_line_name = new_line_name;
}

int Customer::getCustomerId()
{
	return _customer_id;
}

int Customer::getArrivalTime()
{
	return _arrival_time;
}

int Customer::getServiceTime()
{
	return _service_time;
}

int Customer::getDepartureTime()
{
	return _departure_time;
}

int Customer::getLineName()
{
	return _line_name;
}

void Customer::generateCustomer(int arrival_time, int line_name)
{
	_id_counter++; 
	Customer(_id_counter, arrival_time, 0, 0, line_name);
}

int Customer::getTotalWaitTime()
{
	return (_departure_time - _arrival_time); 
}