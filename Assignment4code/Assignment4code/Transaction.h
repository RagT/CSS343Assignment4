/*
Transaction.h keeps track of data for a single checkout and return made
by the customer.
*/
#pragma once
#include"Item.h"
#include <iostream>
class Transaction
{
private:
	Item * itemCheckedOut; //The item that the transaction is being performed upon
	bool returned; //Whether item has been returned yet 
	int custID;	//Customer that performed the transaction
	char mediaType; //D is for 'DVD'

public:
	Transaction();	//default constructor
	Transaction(Item * item);
	~Transaction();

	//getters
	Item * getItem();
	int getCustID();
	char getMedia();
	bool isReturned() const;

	//sets returned field to true
	void returnItem();
	
	void setBorrowed();
	void setMediaType(char);
	void setCustID(int);
	void display();
};
