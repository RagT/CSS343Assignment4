/*
DramaMovie.h
Represents Drama genre of Movie
*/
#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
	DramaMovie(string title, int stock, string director, int releaseYear)
		: Movie(title, stock, director, releaseYear) {};

	//operator overloads
	bool operator==(DramaMovie& other) const;
	bool operator<(DramaMovie& other) const;
	bool operator>(DramaMovie& other) const;

	string getInfo() const;
};
