#include "ClassicMovie.h"

ClassicMovie::ClassicMovie()
{
	majorActorFirst = "";
	majorActorLast = "";
}

ClassicMovie::~ClassicMovie()
{
}

int ClassicMovie::getReleaseMonth() const
{
	return releaseMonth;
}

string ClassicMovie::getMajorActor() const
{
	return majorActorFirst + " " + majorActorLast;
}

bool ClassicMovie::operator==(Item & other) const
{
	//cast down to classic movie from item
	const ClassicMovie& classicMovie = static_cast<const ClassicMovie&>(other);
	 return this->releaseYear == classicMovie.releaseYear && this->releaseMonth == classicMovie.releaseMonth
		&& this->majorActorFirst == classicMovie.majorActorFirst && this->majorActorLast == classicMovie.majorActorLast;
}

bool ClassicMovie::operator<(Item & other) const
{
	//cast down to classic movie from item
	const ClassicMovie& classicMovie = static_cast<const ClassicMovie&>(other);
	if (this->releaseYear < classicMovie.releaseYear && this->releaseMonth < classicMovie.releaseMonth)
	{
		return true;
	}
	return this->getMajorActor() < classicMovie.getMajorActor();
}

bool ClassicMovie::operator>(Item & other) const
{
	return !(*this < other) && !(*this == other);
}

string ClassicMovie::getInfo() const
{
	ClassicMovie c;
	return title + "  " + c.to_string(releaseMonth) + "  " + c.to_string(releaseYear) + "  ( " + director +
		",  " + majorActorFirst + " " + majorActorLast + ")  Stock: " + c.to_string(stock);
}

void ClassicMovie::setData(ifstream & infile)
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
	infile >> majorActorFirst;
	infile.get();
	infile >> majorActorLast;
	infile.get();
	infile >> releaseMonth;
	infile.get();
	infile >> releaseYear;
	infile.get();
}

int ClassicMovie::hashCode() const
{
	return releaseYear + releaseMonth + hashString(majorActorFirst) + hashString(majorActorLast);
}

