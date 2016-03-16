/*
DramaMovie.h
Represents Drama genre of Movie
*/
#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
	DramaMovie(string title, int stock, string director, int releaseYear, string mediaType)
		: Movie(title, stock, director, releaseYear, mediaType) {};

	//operator overloads
	bool operator==(DramaMovie& other) const;
	bool operator<(DramaMovie& other) const;
	bool operator>(DramaMovie& other) const;

	string getInfo() const;
};
