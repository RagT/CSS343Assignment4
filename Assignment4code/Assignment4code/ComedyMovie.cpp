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
	ComedyMovie c;
	return title + "   " + c.to_string(releaseYear)
		+ "     Dir: " + director + "   Stock: " + c.to_string(stock);
}

void ComedyMovie::setData(ifstream & infile)
{
	infile.get();
	infile.get();
	infile >> stock;
	infile.get();
	infile.get();
	char character = infile.get();
	while (character != ',')
	{
		director += character;
		character = infile.get();
	}
	infile.get();
	character = infile.get();
	while (character != ',')
	{
		title += character;
		character = infile.get();
	}
	infile.get();
	infile >> releaseYear;
	infile.get();
}

int ComedyMovie::hashCode() const
{
	return hashString(title) + releaseYear;
}
