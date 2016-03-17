/*
ComedyMovie.h
Represents Comedy Genre of Movie
*/
#pragma once
#include "Movie.h"

class ComedyMovie :public Movie
{
public:
	ComedyMovie();
	ComedyMovie(string title, int stock, string director)
		: Movie(title, stock, director, releaseYear) {};
	~ComedyMovie();

	//operator overloads
	bool operator==(Item& other) const;
	bool operator<(Item& other) const;
	bool operator>(Item& other) const;

	string getInfo() const;
	void setData(ifstream& infile);
};