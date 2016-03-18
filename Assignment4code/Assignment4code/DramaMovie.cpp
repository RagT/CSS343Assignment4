#include "DramaMovie.h"

DramaMovie::DramaMovie()
{
}

DramaMovie::~DramaMovie()
{
}

bool DramaMovie::operator==(Item & other) const
{
	//cast down to drama movie from item
	const DramaMovie& dramaMovie = static_cast<const DramaMovie&>(other);
	return this->director == dramaMovie.director && this->title == dramaMovie.title;
}

bool DramaMovie::operator<(Item & other) const
{
	//cast down to drama movie from item
	const DramaMovie& dramaMovie = static_cast<const DramaMovie&>(other);

	if (this->director < dramaMovie.director)
	{
		return true;
	}
	return this->title < dramaMovie.title;
}

bool DramaMovie::operator>(Item & other) const
{
	return !(*this < other) && !(*this == other);
}

string DramaMovie::getInfo() const
{
	return title + "   " + to_string(releaseYear)
		+ "     Dir: " + director + "   Stock: " + to_string(stock);
}

void DramaMovie::setData(ifstream & infile)
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

int DramaMovie::hashCode() const
{
	return hashString(title) + hashString(director);
}
