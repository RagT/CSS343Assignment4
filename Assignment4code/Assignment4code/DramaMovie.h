/*
DramaMovie.h
Represents Drama genre of Movie
*/
#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
public:
	DramaMovie();
	DramaMovie(string title, int stock, string director, int releaseYear)
		: Movie(title, stock, director, releaseYear) {};
	~DramaMovie();

	//operator overloads
	bool operator==(Item& other) const;
	bool operator<(Item& other) const;
	bool operator>(Item& other) const;

	string getInfo() const;

	//Reads in Item from file
	void setData(ifstream& infile);
};
