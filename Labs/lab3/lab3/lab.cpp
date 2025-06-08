// Alex Childers
// CS 211 Lab 3
// 09/10/2018
// This program is a postfix calculator, implemented using a stack. 

#include "StringSplitter.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <stack>

using namespace std; 

// Expects two doubles, returns nothing. 
// Stores the values of the two top items in num_stack in the given double variables. 
void getOperands(stack<double> &num_stack, double &first, double &second);
	
int main(void)
{
	stack<double> numbers{};
	string input = ""; 
	vector<string> pieces{}; 
	string again = "y"; 
	while (again == "y")
	{
		cout << "Enter an expression to evaluate: ";
		getline(cin, input);
		pieces = StringSplitter::split(input, " ");
		for (auto i : pieces)
		{
			double first_num = 0;
			double second_num = 0;
			if (i == "+")
			{
				getOperands(numbers, first_num, second_num);
				numbers.push(first_num + second_num);
			}
			else if (i == "-")
			{
				getOperands(numbers, first_num, second_num);
				numbers.push(first_num - second_num);
			}
			else if (i == "*")
			{
				getOperands(numbers, first_num, second_num);
				numbers.push(first_num * second_num);
			}
			else if (i == "/")
			{
				getOperands(numbers, first_num, second_num);
				numbers.push(first_num / second_num);
			}
			else
			{
				string to_parse = i;
				
				double result = 0;

				// detect invalid state: if unexpected input is given, exit 
				try
				{
					result = stoi(to_parse);
				}
				catch (...)
				{
					cout << "Invalid input of " << to_parse << " encountered. Exiting." << endl;
					return 0; 
				}
				numbers.push(result);
			}
		}

		// detect invalid state: if there's more than one value left in the stack after
		//		the final calculation is performed, exit. otherwise, end program as normal. 
		double answer = numbers.top();
		numbers.pop();
		if (numbers.size() > 0)
		{
			cout << "Not enough operators given to process all numbers. Exiting." << endl;
			return 0; 
		}
		cout << "Result: " << answer << endl;
		cout << "Continue (y/n)?: ";
		getline(cin, again); 
		cout << endl; 
	}
	return 0; 
}

void getOperands(stack<double> &num_stack, double &first, double &second)
{
	// detect invalid state: if there are too many operations in the equation, exit
	if (num_stack.size() < 2)
	{
		cout << "Unexpected operation encountered. Exiting." << endl;
		exit(0); 
	}
	second = num_stack.top();
	num_stack.pop();
	first = num_stack.top();
	num_stack.pop();
}