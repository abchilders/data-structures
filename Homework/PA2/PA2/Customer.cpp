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

int Customer::getTotalWaitTime()
{
	return (_departure_time - _arrival_time); 
}