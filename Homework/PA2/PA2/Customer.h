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

#ifndef CUSTOMER_H
#define CUSTOMER_H

using namespace std; 

class Customer
{
public:
	// default constructor
	Customer(); 

	// constructor 
	Customer(int new_customer_id, int new_arrival_time, int new_service_time,
		int new_departure_time, int new_line_name);

	// setter for _customer_id
	void setCustomerId(int new_id); 

	// setter for _arrival_time
	void setArrivalTime(int new_arrival_time); 

	// setter for _service_time
	void setServiceTime(int new_service_time); 

	// setter for _departure_time
	void setDepartureTime(int new_departure_time); 

	// setter for _line_name
	void setLineName(int new_line_name); 

	// getter for _customer_id
	int getCustomerId(); 

	// getter for _arrival_time
	int getArrivalTime(); 

	// getter for _service_time
	int getServiceTime();

	// getter for _departure_time
	int getDepartureTime(); 

	// getter for _line_name
	int getLineName(); 
	
	// computes the total wait time
	int getTotalWaitTime(); 

	// id counter
	static int _id_counter;

private:
	int _customer_id; 
	int _arrival_time; 
	int _service_time; 
	int _departure_time; 
	int _line_name; 
};

#endif /* CUSTOMER_H */