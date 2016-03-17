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

//Displays the history of transactions (Checkouts and Returns) for customer with given id
void Store::displayHistory(int customerId) const
{
	cout << "Transactions for customer with id " << customerId << "Name: " << customers.at(customerId)->getFName() << " " 
		<< customers.at(customerId)->getLName() << endl;
	list<Transaction*>  temp = history.at(customerId);

	for (list<Transaction*>::const_iterator iterator = temp.begin(), end = temp.end(); iterator != end; ++iterator) 
	{
		cout << "Item Checked Out: " << endl << (*iterator)->getItem()->getInfo() << endl;
		if ((*iterator)->isReturned())
		{
			cout << "Item Returned: " << endl << (*iterator)->getItem()->getInfo() << endl;
		}
	}


}

Customer * Store::getCustomer(int id)
{
	return customers[id];
}

Item * Store::getClassic(int releaseMonth, int releaseYear, string majorActorFirst, string majorActorLast)
{
	ClassicMovie classic("", 0, "", releaseYear, releaseMonth, majorActorFirst, majorActorLast);
	Item * itemToRetrieve = NULL;
	inventory.find(&classic, itemToRetrieve);
	return itemToRetrieve;
}

Item * Store::getDrama(string director, string title)
{
	DramaMovie drama(title, 0, director, 0);
	Item * itemToRetrieve = NULL;
	inventory.find(&drama, itemToRetrieve);
	return itemToRetrieve;
}

Item * Store::getComedy(string title, int releaseYear)
{
	DramaMovie comedy(title, 0, "", releaseYear);
	Item * itemToRetrieve = NULL;
	inventory.find(&comedy, itemToRetrieve);
	return itemToRetrieve;
}
