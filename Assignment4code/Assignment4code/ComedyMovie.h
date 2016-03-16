/*
ComedyMovie.h
Represents Comedy Genre of Movie
*/
#pragma once
#include "Movie.h"

class ComedyMovie :public Movie
{
public:
	ComedyMovie(string title, int stock, string director)
		: Movie(title, stock, director, releaseYear) {};
	~ComedyMovie();

	//operator overloads
	bool operator==(ComedyMovie& other) const;
	bool operator<(ComedyMovie& other) const;
	bool operator>(ComedyMovie& other) const;

	string getInfo() const;
};