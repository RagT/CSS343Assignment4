/*
Movie.h
Generic Movie class
Abstract class. Must be inherited from.
*/
#pragma once
#include "Item.h"

class Movie : public Item
{
protected:
	//Data all movies have

	string title;
	string director;
	int releaseYear;

	int hashString(const string& str) const;

public:
	Movie();

	Movie(string title, int stock, string director, int releaseYear)
		: Item(stock) 
	{
		this->title = title;
		this->director = director;
		this->releaseYear = releaseYear;
	};
	~Movie();
	
	//operator overloads
	virtual bool operator==(Item& other) const = 0;
	virtual bool operator<(Item& other) const = 0;
	virtual bool operator>(Item& other) const = 0;

	//getter methods
	string getTitle() const;
	string getDirector() const;
	
	int getReleaseYear() const;

	virtual string getInfo() const = 0;

	int hashCode() const;

	//Reads in Item from file
	virtual void setData(ifstream& infile) = 0;
};
