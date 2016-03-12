/*
ItemStorage.h 
Handles storing of all items in the store.
Uses a hashtable to store the items.
*/

#pragma once
#pragma once
#include <vector>
#include "Item.h"
using namespace std;
class ItemStorage
{
private:
	Item * arr;
	int arrLength; // length of array
	int size; // number of elements in table

	//Calls specific item's hashcode method
	int hashCode(Item *) const;

public:
	ItemStorage();
	~ItemStorage();

	bool insert(Item *);
	Item * find(Item *);
	bool remove(Item *);
};

