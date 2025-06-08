/* QUESTIONS:
This default constructor thing isn't really working??? ???

What is the best way to initialize private member variables? 
	-Constructor(int value = 0)
	{
		_private_value = value; 
	}

Should "static int _id_counter" be public? 
	I've read that static variables should be defined in the .cpp file, rather
	than the .h file. Is this true? YES - MUST BE INITIALIZED OUTSIDE OF CLASS DEF 
		DEFINE IN CLASS, INITIALIZE OUTSIDE OF CLASS 
	(Also read: declare the variable in header file; initialize it in .cpp
	file) 
	-SO SHOULD IT BE PUBLIC? 

Is it ok to include the #include statements and "using namespace std"? 
	-I'LL FIGURE THIS OUT MYSELF
	-DON'T DUPLICATE - JUST USE AS NEEDED. TRIAL AND ERROR IF NEEDED BUDDY 

Should I include comments indicating what each public member function is? 
	-probably
	- SURE GO AHEAD THAT'S FINE 

For string _line_name:
	-Should this be an int instead? 
	- YEAH USE AN INT 
*/

/* RESOURCES:
https://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
https://www.learncpp.com/cpp-tutorial/811-static-member-variables/
to read later: https://en.cppreference.com/w/cpp/language/static
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

	// creates a new customer
	static void generateCustomer(int arrival_time, int line_name); 
	
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