#include "ItemStorage.h"

ItemStorage::ItemStorage()
{
	ItemArr.resize(START_SIZE, NULL);
	size = 0;
}


ItemStorage::~ItemStorage()
{
	for (int i = 0; i < size; i++)
	{
		delete ItemArr[i];
	}
}

//Inserts new item in hashtable if spot isn't initially available,
//uses linear probing to find open spot.
bool ItemStorage::insert(Item * itemToInsert)
{
	int code = itemToInsert->hashCode();
	if (ItemArr[code % size] == NULL)
	{
		ItemArr[code % size] = itemToInsert;
		return true;
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
}

//Takes in two parameters an itemToFind and a pass by reference parameter to retrieve the item pointer
//from the hash table. Returns true if item is found in table false if not.
bool ItemStorage::find(Item * itemToFind, Item *& itemToRetrieve) const
{
	int code = itemToFind->hashCode;
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
