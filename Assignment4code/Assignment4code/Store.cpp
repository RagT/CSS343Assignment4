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

			//Customer's ID
			int custID;
			infile >> custID;

			Customer* temp = getCustomer(custID);

			//check to see if customer exists
			if (temp != NULL) //YES
			{
				//display customer
				cout << "Customer ID: " << custID << " " << temp->getFName() << " " << temp->getLName() << endl;

				//display customer's history
				displayHistory(custID);
			}
			
			else //NO
			{
				cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
			}
			
			//gets rid of '\n'
			infile.get();
		}

		//B: Set Transaction as borrowed
		else if (actionType == 'B')
		{
			//Customer's ID
			int custID;
			infile >> custID;

			Customer* cust = getCustomer(custID);
			//check to see if customer exists
			if (cust != NULL) //YES
			{
				//set returned as false
				rental->setBorrowed();

				//set Customer's ID in the Transaction
				rental->setCustID(custID);
				
				//set the MediaType in the Transaction
				char media;
				infile >> media;
				rental->setMediaType(media);

				//get genre from infile
				char genre;
				infile >> genre;

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

					//Item was found
					if (found != NULL)
					{
						//set the found item in rental
						rental->setItem(found);


						//store completed transaction in history
						list<Transaction*>  temp = history.at(rental->getCustID());
						temp.push_back(rental);
					}

					//item not found
					else
					{
						//display error message with the rejected line
						cout << "Non-Existent video entered. Invalid Line: C " << month << " " <<
							actorF << " " << actorL << " " << endl;
					}

					


				}

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
					
					//Item was found
					if (found != NULL)
					{
						//set the found item in rental
						rental->setItem(found);

						//store completed transaction in history
						list<Transaction*>  temp = history.find(rental->getCustID())->second;
						temp.push_back(rental);
					}

					//item not found
					else
					{
						//prints error message with rejected line
						cout << "Non-Existent video entered. Invalid Line: D " << director << " " << title << endl;
					}

				}

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
					
					//Yes: Item is found
					if (found != NULL)
					{
						//set the found item in rental
						rental->setItem(found);

						//store completed transaction in history
						list<Transaction*>  temp = history.find(rental->getCustID())->second;
						temp.push_back(rental);
					}

					//No: item not found
					else
					{
						//print out error message with the line
						cout << "Non-Existent video entered. Invalid Line: F " << title << ", " << year
							<< endl;
					}
				}

				//Invalid movie!
				else
				{
					//print out error message with the line
					cout << "Non-Existent video entered. Invalid Line: " << "B " << rental->getCustID() << " " <<
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
				cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
				
				//gets rid of '\n'
				infile.get();
			}

		}

		//R: Set Transaction as returned
		else if (actionType == 'R')
		{

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

//Displays the history of transactions (Checkouts and Returns) for customer with given id
void Store::displayHistory(int customerId) const
{
	cout << "Transactions for customer with id " << customerId << "   Name: " << customers.find(customerId)->second->getFName() << " " 
		<< customers.find(customerId)->second->getLName() << endl;
	if (history.find(customerId) != history.end())
	{
		list<Transaction*>  temp = history.find(customerId)->second;
		for (list<Transaction*>::const_iterator iterator = temp.begin(), end = temp.end(); iterator != end; ++iterator)
		{
			(*iterator)->display();
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
