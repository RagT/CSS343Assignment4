/*
Raghu Tirumala, Randy Hang
Store.h

The store class contains all the data for the items inside
(DVD's, VCR's, etc.) as well as all the Customer data. The
History of a customer's transactions with the store are also kept
track of.
*/

#pragma once
#include "ItemStorage.h"
#include "Customer.h"
#include "Item.h"
#include "Transaction.h"
#include <map>
#include <list>
#include <iostream>
using namespace std;

class Store
{
public:
	Store();
	~Store();

	//Creates a new customer and adds them to store
	bool addCustomer(int id, std::string fName, string lName);

	//Adds a new item to the store. Takes in string containing relevant item information.
	bool addItem(string itemData);

	//Customer checks out item from the store
	bool checkOut(int customerId, string itemType, string itemData);

	//Customer returns item to the store
	bool returnItem(int customerId, string itemType, string itemData);

	//Get the history of a customer with given Customer id
	string getHistory(int customerId) const;

	//Prints entire inventory of store to cout
	void displayInventory() const;


private:
	//Stores items in the store
	ItemStorage inventory;

	//Stores data about customers
	map<int, Customer *> customers;

	//Stores data of transaction history of a customer
	//Maps customerId to a list of transactions
	map<int, list<Transaction *>> history;

	//getter methods
	Customer * getCustomer(int id);
	Item * getItem(string name, string itemType, string itemData);
};