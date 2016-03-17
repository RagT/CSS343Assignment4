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
#include "Movie.h"
#include "DramaMovie.h"
#include "ComedyMovie.h"
#include "ClassicMovie.h"
#include "Transaction.h"
#include <map>
#include <list>
#include <iostream>
#include <sstream>
using namespace std;

class Store
{
public:
	Store();
	~Store();

	//build Customer map from a text file
	void buildCustomers(ifstream& infile);

	//Create and add all items to the Store
	void addItems(ifstream& infile);

	//Runs all commads from passed in ifstream
	void processCommands(ifstream& infile);

	//Customer checks out item from the store
	bool checkOut(int customerId, string itemType, string itemData);

	//Customer returns item to the store
	bool returnItem(int customerId, string itemType, string itemData);

	//Get the history of a customer with given Customer id
	void displayHistory(int customerId) const;

	//Prints entire inventory of store to cout
	void displayInventory() const;
	
	//Function to process actiontype H
	void processHistory(ifstream& infile);

	//Create a borrowed transaction
	void createBTransaction(Transaction* &, ifstream&);


private:
	//Stores items in the store
	ItemStorage inventory;

	//Stores data about customers
	map<int, Customer *> customers;

	//Stores data of transaction history of a customer
	//Maps customerId to a list of transactions
	map<int, list<Transaction *> > history;

	//getter methods
	Customer * getCustomer(int id);
	Item * getClassic(int releaseMonth, int releaseYear, string majorActorFirst, string majorActorLast);
	Item * getDrama(string director, string title);
	Item * getComedy(string title, int releaseYear);
};
