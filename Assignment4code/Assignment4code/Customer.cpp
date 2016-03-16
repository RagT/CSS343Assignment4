#include "Customer.h"
#include <iostream>
#include <fstream>


Customer::Customer()
{
	this->id = NULL;
	this->fName = "";
	this->lName = "";
}

Customer::Customer(int id, string fName, string lName)
{
	this->id = id;
	this->fName = fName;
	this->lName = lName;
}

Customer::~Customer()
{
}

void Customer::setData(ifstream& infile)
{
	infile >> id;
	infile.get();
	infile >> fName;
	infile.get();
	infile >> lName;
	infile.get();

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
