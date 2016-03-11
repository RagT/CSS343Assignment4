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

	//Type of media 'D' for dvd 'V' for VCR etc.
	string mediaType;

public:
	Movie(string title, int stock, string director, int releaseYear, string mediaType)
		: Item(stock) {};
	~Movie();

	//getter methods
	string getTitle() const;
	string getDirector() const;
	string getMediaType() const;
	int getReleaseYear() const;

	//operator overloads
	virtual bool operator==(Movie& other) const = 0;

	virtual string getInfo() const = 0;

	virtual int hashCode() const = 0;
};