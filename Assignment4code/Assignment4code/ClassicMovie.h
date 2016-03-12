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
		int releaseMonth, string majorActor, string mediaType)
		: Movie(title, stock, director, releaseYear, mediaType) {};

	//getter methods
	int getReleaseMonth() const;
	string getMajorActor() const;

	//operator overloads
	bool operator==(ComedyMovie& other) const;

	string getInfo() const;
	int hashCode() const;
};