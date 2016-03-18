/*
StoreMain.cpp

Main program, calls methods on the Store class.
*/

#include "Store.h"
#include <iostream>
#include <fstream>

int main()
{
	ifstream customers("data4customers.txt");
	ifstream movies("data4movies.txt");
	ifstream commands("data4commands.txt");
	
	Store MovieStore;
	MovieStore.buildCustomers(customers);
	MovieStore.addItems(movies);
	
	//display inventory
	ItemStorage forDisplay = MovieStore.getInventory();
	forDisplay.displayAll();
	
	MovieStore.processCommands(commands);
}
