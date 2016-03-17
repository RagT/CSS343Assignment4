#include "Store.h"
#include <iostream>
#include <fstream>



Store::Store()
{
}


Store::~Store()
{
}

//-------------- buildCustomers -------------------
//Creates customers from a textfile
//Then, populates the customers map with the created customer 
void Store::buildCustomers(ifstream& infile)
{
	while (!infile.eof())
	{
		if (!infile.eof())
		{
			Customer* toAdd = new Customer;
			toAdd->setData(infile);
			customers[toAdd->getId()] = toAdd;
		}
	}
}
//----------------- addItems ----------------------
//Creates Items from text file to add to Store
void Store::addItems(ifstream & infile)
{
	while (!infile.eof())
	{
		Item * newItem = NULL;
		char itemType = infile.get();
		if (itemType == 'D')
		{
			newItem = new DramaMovie();
			newItem->setData(infile);
			inventory.insert(newItem, itemType);
		}
		else if (itemType == 'F')
		{
			newItem = new ComedyMovie();
			newItem->setData(infile);
			inventory.insert(newItem, itemType);
		} 
		else if (itemType == 'C')
		{
			newItem = new ClassicMovie();
			newItem->setData(infile);
			inventory.insert(newItem, itemType);
		}
		else
		{
			cout << "Error Invalid Item Type: " << itemType << endl;
			infile.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

//----------------- processCommands ----------------------
//Creates Items from text file to add to Store
void Store::processCommands(ifstream& infile)
{
	while (!infile.eof())
	{
		Transaction * movieRental = NULL;

		//Action Type "I" - do nothing, "H" - display customer
		//"B" - Borrow item, "R" - Return item
		char actionType = infile.get();
		
		//I: Go to next line
		if (actionType == 'I')
		{
			//skip the line
			infile.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//H: Display Customer's History
		else if (actionType == 'H')
		{
			//Label
			cout << "----------------------Customer Transactions------------------" << endl;

			int custID;

			infile >> custID;

			Customer* temp = getCustomer(custID);

			//check to see if customer exists
			//YES
			if (temp != NULL)
			{
				//display customer
				cout << "Customer ID: " << custID << temp->getFName() << " " << temp->getLName() << endl;

				//display customer's history
				displayHistory(custID);
			}
			//NO
			else
			{
				cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
			}
		}

		//B: Set Transaction as borrowed
		else if (actionType == 'B')
		{

		}

		//R: Set Transaction as returned
		else if (actionType == 'R')
		{

		}

		else //invalid Action!
		{

		}

	}
}

void Store::displayHistory(int customerId) const
{
	list<Transaction> * temp = history[customerId];

}

Customer * Store::getCustomer(int id)
{
	return customers[id];
}
