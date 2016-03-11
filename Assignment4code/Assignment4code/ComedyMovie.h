/*
ComedyMovie.h
Represents Comedy Genre of Movie
*/
#pragma once
#include "Movie.h"

class ComedyMovie :public Movie
{
public:
	ComedyMovie(string title, int stock, string director, int releaseYear,
		int releaseMonth, string majorActor, string mediaType)
		: Movie(title, stock, director, releaseYear, mediaType) {};

	//operator overloads
	bool operator==(ComedyMovie& other) const;

	string getInfo() const;
	int hashCode() const;
};