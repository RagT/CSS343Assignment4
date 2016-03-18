#include "Store.h"
#include <iostream>
#include <fstream>
#include <limits>


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
//Reads in data from a text file and updates the rental history of the specified customer
//using the customer id to determine if the customer exists within the database
//Existence of a Movie is determined using different movie data combinations based on the genre
//to search through the correct set of movies the rental might be located
//ActionTypes determine the action taken on the current line of data (I, H, B, R)
void Store::processCommands(ifstream& infile)
{
	while (!infile.eof())
	{
		//create a Transaction
		Transaction * rental = new Transaction;

		//Action Types (I, H, B, R)
		char actionType = infile.get();
		
		//I: Go to next line
		if (actionType == 'I')
		{
			//remaining data is useless, so skip it
			infile.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//H: Display Customer's History
		else if (actionType == 'H')
		{
			//process and displays history from txt file
			processHistory(infile);
		}

		//B: Set Transaction as borrowed, determine which genre 
		//and assign it to the Customer in their history
		//R: Set Transaction as returned, increment stock
		else if (actionType == 'B' || actionType == 'R')
		{
			//Process & create a borrowed Transaction
			createTransaction(actionType, rental, infile);
		}

		else //invalid Action!
		{
			cout << "Invalid Command entered. Invalid Line: ";

			//print out the rest of the invalid line
			while (!infile.eof() && infile.get() != '\n')
			{
				cout << infile.get();
			}

			//spacing
			cout << endl;
		}

	//delete Transaction pointer
	delete rental;
	rental = NULL;

	}
}


//-----------------createBorrowedTransaction--------------------------
//Takes a Transaction Pointer and infile from the processCommands()
//Verifies Customer ID with the customers in the database
//Determines which genre movie is being rented and verifies that movie exists
//Calls completeTransaction to complete the transaction by inserting into history
void Store::createTransaction(char actionType, Transaction* &rental, ifstream& infile)
{
	//read in Customer's ID from infile
	int custID;
	infile >> custID;

	//returns NULL if customer doesn't exist
	Customer* cust = getCustomer(custID);

	//check to see if customer exists
	if (cust != NULL) //YES
	{
		//set Customer's ID in the Transaction
		rental->setCustID(custID);

		//set the MediaType in the Transaction
		char media;
		infile >> media;
		rental->setMediaType(media);

		//get genre from infile
		char genre;
		infile >> genre;

		//set genre in Transaction
		rental->setGenre(genre);
		infile.get();

		//using correct format for Classic Movie
		if (genre == 'C')
		{
			//get month from infile
			int month;
			infile >> month;

			//get year from infile
			int year;
			infile >> year;

			//get actor first name from txt file
			string actorF;
			char character = infile.get();

			//build actor's first name until space
			while (character != ' ')
			{
				actorF += character;
				character = infile.get();
			}

			//get actor's last name from txt file
			string actorL;
			character = infile.get();

			//build actor's last name
			while (character != '\n')
			{
				actorL += character;
				character = infile.get();
			}

			//does item exist?
			Item* found = getClassic(month, year, actorF, actorL);

			//complete transaction
			completeTransaction(actionType, found, rental);

		}

		//using correct format for Drama Movie
		else if (genre == 'D')
		{
			//get director from txt file
			string director;
			char character = infile.get();

			//build title until comma is reached
			while (character != ',')
			{
				director += character;
				character = infile.get();
			}

			//get title from txt file
			string title;
			character = infile.get();

			//build title until comma is reached
			while (character != ',')
			{
				title += character;
				character = infile.get();
			}

			//does item exist?
			Item* found = getDrama(director, title);

			//complete transaction
			completeTransaction(actionType, found, rental);

		}

		//using correct format for Comedy Movie
		else if (genre == 'F')
		{
			//get title from txt file
			string title;
			char character = infile.get();

			//build title from infile
			while (character != ',')
			{
				title += character;
				character = infile.get();
			}

			//get year from infile
			int year;
			infile >> year;

			//does item exist?
			Item* found = getComedy(title, year);

			//complete transaction
			completeTransaction(actionType, found, rental);
		}

		//Invalid movie! (Genre code is incorrect)
		else
		{
			//print out error message with the line
			cout << "Non-Existent video entered. Invalid Line: B "  << rental->getCustID() << " " <<
				media << " " << genre << " ";

			//print out the rest of the line
			while (!infile.eof() && infile.get() != '\n')
			{
				cout << infile.get();
			}

			//spacing
			cout << endl;
		}

	}

	else //NO: Customer does not exist
	{
		//print out error message with the line
		cout << "Non-Existent customer entered. Invalid Line: " << custID << endl;

		//print out the rest of the line
		while (!infile.eof() && infile.get() != '\n')
		{
			cout << infile.get();
		}

		//spacing
		cout << endl;
	}
}

//-----------------completeTransaction-------------------------------
//Takes in an Item and a Transaction from createTransaction function (for all genres)
//If Item exists, Customer's history is updated
//If Item does not exist, error message is printed with the rejected line
void Store::completeTransaction(char actionType, Item* & found, Transaction* & rental)
{
	//Yes: Item is found
	if (found != NULL)
	{
		//initiate a borrow
		if (actionType == 'B')
		{
			if (found->getStock() != 0)
			{
				//set returned as false
				rental->setBorrowed();

				//checked item out: decrement stock
				found->decrementStock();

				//set the found item in rental
				rental->setItem(found);

				//store completed transaction in history
				if (history.find(rental->getCustID()) != history.end())
				{
					list<Transaction*>  temp = history.find(rental->getCustID())->second;
					temp.push_back(rental);
				}
				else
				{
					list<Transaction*> newTransaction;
					newTransaction.push_back(rental);
					history[rental->getCustID()] = newTransaction;
				}
				rental = NULL;
			}

			//Item is out of stock!
			else
			{
				cout << "Sorry! The Movie " << found->getInfo() << "is currently out of stock!" << endl;
			}

		}

		//initiate a return
		else
		{
			//checked item in: increment stock
			found->incrementStock();

			//set the found item in rental
			rental->setItem(found);

			//store completed transaction in history
			list<Transaction*>  temp = history.find(rental->getCustID())->second;
			for (list<Transaction*>::const_iterator iterator = temp.begin(), end = temp.end(); iterator != end; ++iterator)
			{
				if (rental->getCustID() == (*iterator)->getCustID())
				{
					//set returned as true
					(*iterator)->returnItem();
				}
			}
		}

		
	}

	//No: item not found
	else
	{
		//print out error message with the line
		cout << "Non-Existent video entered. Invalid Line: " << actionType << " " << rental->getCustID() << " " << 
			rental->getMedia() << " " << rental->getGenre() << endl;
	}

}

//----------------------processHistory--------------------
//Takes in the infile as a reference and prints out a customer's history
void Store::processHistory(ifstream& infile)
{
	//Label for displaying Transactions of a particular Customer
	cout << "----------------------Customer Transactions------------------" << endl;

	//read in Customer's ID from infile
	int custID;
	infile >> custID;

	//determine if customer exists in the system
	Customer* temp = getCustomer(custID);

	//check to see if customer exists
	if (temp != NULL) //YES
	{
		//display customer's information
		cout << "Customer ID: " << custID << " " << temp->getFName() << " " << temp->getLName() << endl;

		//display customer's history
		displayHistory(custID);
	}

	else //NO
	{
		//display error message with rejected line
		cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
	}
	infile.get();
}

//----------------displayHistory---------------------------
//Displays the history of transactions (Checkouts and Returns) for customer with given id
void Store::displayHistory(int customerId) const
{
	if (history.find(customerId) != history.end())
	{
		list<Transaction*>  temp = history.find(customerId)->second;
		for (list<Transaction*>::const_iterator iterator = temp.begin(), end = temp.end(); iterator != end; ++iterator)
		{
			(*iterator)->display();
		}
	}
}

//---------------getCustomer----------------
//Retrieves a customer by their ID
Customer * Store::getCustomer(int id)
{
	if (customers.find(id) != customers.end())
	{
		return customers[id];
	}
	else
	{
		return NULL;
	}
}

//---------------getClassic----------------
//Retrieves a customer by their ID
Item * Store::getClassic(int releaseMonth, int releaseYear, string majorActorFirst, string majorActorLast)
{
	ClassicMovie classic("", 0, "", releaseYear, releaseMonth, majorActorFirst, majorActorLast);
	Item * itemToRetrieve = NULL;
	inventory.find(&classic, itemToRetrieve);
	return itemToRetrieve;
}

//---------------getDrama----------------
//Retrieves a drama movie by searching for it
//by it's title and year within the 
Item * Store::getDrama(string director, string title)
{
	DramaMovie drama(title, 0, director, 0);
	Item * itemToRetrieve = NULL;
	inventory.find(&drama, itemToRetrieve);
	return itemToRetrieve;
}

//---------------getComedy----------------
//Retrieves a comedy movie by searching for it
//by it's title and year within the 
Item * Store::getComedy(string title, int releaseYear)
{
	ComedyMovie comedy(title, 0, "", releaseYear);
	Item * itemToRetrieve = NULL;
	inventory.find(&comedy, itemToRetrieve);
	return itemToRetrieve;
}
