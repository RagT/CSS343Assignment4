#include "ComedyMovie.h"

ComedyMovie::ComedyMovie()
{
}

ComedyMovie::~ComedyMovie()
{
}

bool ComedyMovie::operator==(Item & other) const
{
	//cast down to comedy movie from item
	const ComedyMovie& comedyMovie = static_cast<const ComedyMovie&>(other);
	return this->title == comedyMovie.title && this->releaseYear == comedyMovie.releaseYear;
}

bool ComedyMovie::operator<(Item & other) const
{
	const ComedyMovie& comedyMovie = static_cast<const ComedyMovie&>(other);
	if (this->title < comedyMovie.title)
	{
		return true;
	}
	return this->releaseYear < comedyMovie.releaseYear;
}

bool ComedyMovie::operator>(Item & other) const
{
	return !(*this < other) && !(*this == other);
}

string ComedyMovie::getInfo() const
{
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Director: " + director;
}

void ComedyMovie::setData(ifstream & infile)
{
	infile >> stock;
	infile.get();
	infile >> director;
	infile.get();
	infile >> title;
	infile.get();
	infile >> releaseYear;
}
