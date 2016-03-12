/*
Customer.h
Keeps track of a single customer's information.
*/
#pragma once
#include <string>
using namespace std;

class Customer
{
protected:
	int id;
	string fName;
	string lName;

public:
	Customer(int id, std::string fName, std::string lName);
	~Customer();

	//getter methods
	int getId() const;
	string getFName() const;
	string getLName() const;
};