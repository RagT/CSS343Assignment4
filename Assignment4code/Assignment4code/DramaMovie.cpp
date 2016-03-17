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
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Director: " + director;
}

void DramaMovie::setData(ifstream & infile)
{
	infile >> stock;
	infile.get();
	infile >> director;
	infile.get();
	infile >> title;
	infile.get();
	infile >> releaseYear;

}
