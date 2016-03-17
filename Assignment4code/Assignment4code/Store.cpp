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
		Transaction * rental = NULL;

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
				cout << "Customer ID: " << custID << temp->getFName() << " " << temp->getLName() << endl;

				//display customer's history
				displayHistory(custID);
			}
			
			else //NO
			{
				cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
			}
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
				char media = NULL;
				infile >> media;
				rental->setMediaType(media);

				//get genre
				char genre = NULL;
				infile >> genre;
				infile.get();	//clear space

				if (genre == 'C')
				{
					//get month
					int month = NULL;
					infile >> month;

					//get year
					int year = NULL;
					infile >> year;

					//get actor first name
					string actorF = NULL;
					char character = infile.get();

					while (character != ' ')
					{
						actorF += character;
						character = infile.get();
					}

					//get actor first name
					string actorL = NULL;
					character = infile.get();

					while (character != '\n')
					{
						actorL += character;
						character = infile.get();
					}

					

					//does item exist?
					Item* found = getClassic(month, year, actorF, actorL);

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
						cout << "Non-Existent video entered. Invalid Line: C " << month << " " <<
							actorF << " " << actorL << " " << endl;
					}

					


				}

				else if (genre == 'D')
				{
					//get director
					string director = NULL;
					char character = infile.get();

					while (character != ',')
					{
						director += character;
						character = infile.get();
					}

					//get title
					string title = NULL;
					character = infile.get();

					while (character != ',')
					{
						title += character;
						character = infile.get();
					}

					//does item exist?
					Item* found = getDrama(director, title);

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
						cout << "Non-Existent video entered. Invalid Line: D " << director << " " << title << endl;
					}

				}

				else if (genre == 'F')
				{
					//get title
					string title = NULL;
					char character = infile.get();

					while (character != ',')
					{
						title += character;
						character = infile.get();
					}

					//get year
					int year = NULL;
					infile >> year;

					//does item exist?
					Item* found = getComedy(title, year);

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
						cout << "Non-Existent video entered. Invalid Line: F " << media << " " << genre << " ";

						//print out the rest of the line
						while (!infile.eof() && infile.get() != '\n')
						{
							cout << infile.get();
						}

						//spacing
						cout << endl;
					}
				}

				//Invalid movie!
				else
				{
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

			else //NO
			{
				cout << "Non-Existent customer entered. Invalid Line: " << "H " << custID << endl;
			}

		}

		//R: Set Transaction as returned
		else if (actionType == 'R')
		{

		}

		else //invalid Action!
		{
			cout << "Invalid Command entered. Invalid Line: ";

			//print out the rest of the line
			while (!infile.eof() && infile.get() != '\n')
			{
				cout << infile.get();
			}

			//spacing
			cout << endl;
		}

	}
}

//Displays the history of transactions (Checkouts and Returns) for customer with given id
void Store::displayHistory(int customerId) const
{
	cout << "Transactions for customer with id " << customerId << "   Name: " << customers.at(customerId)->getFName() << " " 
		<< customers.at(customerId)->getLName() << endl;
	
	list<Transaction*>  temp = history.at(customerId);
	for (list<Transaction*>::const_iterator iterator = temp.begin(), end = temp.end(); iterator != end; ++iterator) 
	{
		(*iterator)->display();
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
