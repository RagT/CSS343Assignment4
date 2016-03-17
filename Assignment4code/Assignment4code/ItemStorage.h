/*
ItemStorage.h
Handles storing of all items in the store.
Uses a hashtable to store the items.
Uses sets to store genres of movies in sorted order.
*/

#pragma once
#pragma once
#include <set>
#include <vector>
#include <typeinfo>
#include <iostream>
#include "ClassicMovie.h"
#include "DramaMovie.h"
#include "ComedyMovie.h"
using namespace std;

const int START_SIZE = 101;

class ItemStorage
{
private:
	Item** ItemArr;
	int arrLength; //capacity of array
	int size; // number of elements in table

	set<Item*> classics;
	set<Item*> dramas;
	set<Item*> comedies;

	void resize();

public:
	ItemStorage();
	~ItemStorage();

	bool insert(Item * itemToInsert);
	bool find(Item * itemToFind, Item *& itemToRetrieve) const;

	void displayAll();

	set<Item*> getClassics();
	set<Item*> getDramas();
	set<Item*> getComedies();
};