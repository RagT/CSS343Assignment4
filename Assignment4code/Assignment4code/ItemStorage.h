/*
ItemStorage.h 
Handles storing of all items in the store.
Uses a hashtable to store the items.
*/

#pragma once
#pragma once
#include <set>
#include "ClassicMovie.h"
#include "DramaMovie.h"
#include "ComedyMovie.h"
using namespace std;

class ItemStorage
{
private:
	Item * arr;
	int arrLength; // length of array
	int size; // number of elements in table

	set<ClassicMovie> classics;
	set<DramaMovie> dramas;
	set<ComedyMovie> comedies;

public:
	ItemStorage();
	~ItemStorage();

	bool insert(Item *);
	Item * find(Item *);
	bool remove(Item *);
};

