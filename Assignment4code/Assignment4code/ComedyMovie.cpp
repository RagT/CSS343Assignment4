#include "ComedyMovie.h"

ComedyMovie::ComedyMovie(string title, int stock, string director)
	: Movie(title, stock, director, releaseYear) 
{

}

ComedyMovie::~ComedyMovie()
{
}

bool ComedyMovie::operator==(ComedyMovie & other) const
{
	return this->title == other.title && this->releaseYear == other.releaseYear;
}

bool ComedyMovie::operator<(ComedyMovie & other) const
{
	if (this->title < other.title)
	{
		return true;
	}
	return this->releaseYear < other.releaseYear;
}

bool ComedyMovie::operator>(ComedyMovie & other) const
{
	return !(*this < other) && !(*this == other);
}

string ComedyMovie::getInfo() const
{
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Director: " + director + " Media Type: ";
}
