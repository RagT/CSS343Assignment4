/*
Item.h
Generic class representing items in the store.
Abstract class. Must be inherited from.
*/
#pragma once
#include <string>
using namespace std;

class Item
{
protected:
	int stock; //number of this item currently in store

public:
	Item(int stock);
	~Item();

	//getters and setters
	virtual int getStock() const;
	virtual bool setStock(int newStock);

	//operator overloads
	virtual bool operator==(Item& other) const = 0;
	virtual bool operator<(Item& other) const = 0;
	virtual bool operator>(Item& other) const = 0;

	//Returns all the item information as a string
	virtual string getInfo() const = 0;

	//Returns a hashcode for this item for use in hashTable
	virtual int hashCode() const = 0;
};