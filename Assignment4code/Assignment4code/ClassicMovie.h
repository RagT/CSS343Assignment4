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
	string majorActor;

public:
	ClassicMovie(string title, int stock, string director, int releaseYear,
		int releaseMonth, string majorActor)
		: Movie(title, stock, director, releaseYear) {};

	//getter methods
	int getReleaseMonth() const;
	string getMajorActor() const;

	//operator overloads
	bool operator==(ClassicMovie& other) const;
	bool operator<(ClassicMovie& other) const;
	bool operator>(ClassicMovie& other) const;

	string getInfo() const;
};
