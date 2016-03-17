#include "ClassicMovie.h"

ClassicMovie::ClassicMovie()
{
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
		&& this->majorActorFirst == classicMovie.getMajorActor();
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
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Release Month: " + to_string(releaseMonth) + "   Director: " + director +
		"   Major Actor: " + majorActorFirst + " " + majorActorLast;
}

void ClassicMovie::setData(ifstream & infile)
{
	infile >> stock;
	infile.get();
	infile >> director;
	infile.get();
	infile >> title;
	infile.get();
	infile >> releaseMonth;
	infile >> majorActorFirst;
	infile >> majorActorLast;
}

