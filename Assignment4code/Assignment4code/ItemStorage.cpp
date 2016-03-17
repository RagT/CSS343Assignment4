/*
ItemStorage.cpp
Contains Implementation for class that stores all the Items in the store.
*/
#include "ItemStorage.h"

ItemStorage::ItemStorage()
{
	ItemArr = new Item*[START_SIZE];
	size = 0;
	arrLength = START_SIZE;
	for (int i = 0; i < arrLength; i++)
	{
		ItemArr[i] = NULL;
	}
}


ItemStorage::~ItemStorage()
{
	for (int i = 0; i < size; i++)
	{
		delete ItemArr[i];
	}
	delete[] ItemArr;
}

//Inserts new item in hashtable if spot isn't initially available,
//uses linear probing to find open spot.
bool ItemStorage::insert(Item * itemToInsert)
{
	resize();
	int code = itemToInsert->hashCode();
	if (ItemArr[code % size] == NULL)
	{
		ItemArr[code % size] = itemToInsert;
	}
	else
	{
		code = (code + 1) % size;
		while (ItemArr[code] != NULL)
		{
			code = (code + 1) % size;
		}
		ItemArr[code] = itemToInsert;
	}
	//Insert movie genre into corresponding set
	if (typeid(*itemToInsert).name() == "ClassicMovie")
	{
		classics.insert(itemToInsert);
	}
	if (typeid(*itemToInsert).name() == "DramaMovie")
	{
		dramas.insert(itemToInsert);
	}
	if (typeid(*itemToInsert).name() == "ComedyMovie")
	{
		comedies.insert(itemToInsert);
	}
	size++;
	return true;
}

//Takes in two parameters an itemToFind and a pass by reference parameter to retrieve the item pointer
//from the hash table. Returns true if item is found in table false if not.
bool ItemStorage::find(Item * itemToFind, Item *& itemToRetrieve) const
{
	int code = itemToFind->hashCode();
	if(*ItemArr[code % size] == *itemToFind)
	{
		itemToRetrieve = ItemArr[code % size];
		return true;
	}
	else
	{
		int foundIndex = (code + 1) % size;
		while (!(*ItemArr[code % size] == *itemToFind) || foundIndex == code % size)
		{
			foundIndex = (foundIndex + 1) % size;
		}
		if (foundIndex == code % size)
		{
			return false;
		}
		itemToRetrieve = ItemArr[foundIndex];
		return true;
	}
}

set<Item*> ItemStorage::getClassics()
{
	return classics;
}

set<Item*> ItemStorage::getDramas()
{
	return dramas;
}

set<Item*> ItemStorage::getComedies()
{
	return comedies;
}

void ItemStorage::displayAll()
{
	for (int i = 0; i < arrLength; i++)
	{
		if(ItemArr[i] != NULL)
			cout << *ItemArr[i];
	}
}

//Resizes array to have double the capacity if load factor is above 0.5
void ItemStorage::resize()
{
	if ((double)size / arrLength > 0.5)
	{
		Item** newItemArr = new Item*[arrLength * 2];
		for (int i = 0; i < arrLength; i++)
		{
			if (ItemArr[i] != NULL)
			{
				int newCode = ItemArr[i]->hashCode();
				if (newItemArr[newCode % (arrLength * 2)] == NULL)
				{
					newItemArr[newCode] = ItemArr[i];
				}
				else
				{
					newCode = (newCode + 1) % (arrLength * 2);
					while (newItemArr[newCode] != NULL)
					{
						newCode = (newCode + 1) % (arrLength * 2);
					}
					newItemArr[newCode] = ItemArr[i];
				}
				ItemArr[i] = NULL;
			}
		}
	}
}

