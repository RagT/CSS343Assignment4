/*
Transaction.h keeps track of data for a single checkout and return made
by the customer.
*/
#pragma once
#include"Item.h"

class Transaction
{
private:
	Item * itemCheckedOut;
	bool returned; //Whether item has been returned yet 

public:
	Transaction(Item * item);
	~Transaction();

	//getters
	Item * getItem();
	bool isReturned() const;

	//sets returned field to true
	void returnItem();
};