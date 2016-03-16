#include "Customer.h"


Customer::Customer(int id, string fName, string lName)
{
	this->id = id;
	this->fName = fName;
	this->lName = lName;
}

Customer::~Customer()
{
}

int Customer::getId() const
{
	return id;
}

string Customer::getFName() const
{
	return fName;
}

string Customer::getLName() const
{
	return lName;
}
