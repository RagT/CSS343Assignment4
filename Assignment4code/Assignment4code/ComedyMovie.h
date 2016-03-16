/*
ComedyMovie.h
Represents Comedy Genre of Movie
*/
#pragma once
#include "Movie.h"

class ComedyMovie :public Movie
{
public:
	ComedyMovie(string title, int stock, string director, string mediaType)
		: Movie(title, stock, director, releaseYear) {};

	//operator overloads
	bool operator==(ComedyMovie& other) const;
	bool operator<(ComedyMovie& other) const;
	bool operator>(ComedyMovie& other) const;

	string getInfo() const;
};
