/*
Classic.h
Represents the Classic genre of the Movie.
*/
#pragma once
#include "Movie.h"

class ClassicMovie : public Movie
{
protected:
	//Attributes unique to ClassicMovie
	int releaseMonth;
	string majorActorFirst;
	string majorActorLast;

public:
	ClassicMovie();

	ClassicMovie(string title, int stock, string director, int releaseYear,
		int releaseMonth, string majorActorFirst, string majorActorLast)
		: Movie(title, stock, director, releaseYear) 
	{
		this->releaseMonth = releaseMonth;
		this->majorActorFirst = majorActorFirst;
		this->majorActorLast = majorActorLast;
	};
	~ClassicMovie();

	//getter methods
	int getReleaseMonth() const;
	string getMajorActor() const;

	//operator overloads
	bool operator==(Item& other) const;
	bool operator<(Item& other) const;
	bool operator>(Item& other) const;

	string getInfo() const;
	void setData(ifstream& infile);
};