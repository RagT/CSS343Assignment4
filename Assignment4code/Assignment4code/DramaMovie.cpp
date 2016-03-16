#include "DramaMovie.h"

DramaMovie::~DramaMovie()
{
}

bool DramaMovie::operator==(DramaMovie & other) const
{
	return this->director == other.director && this->title == other.title;
}

bool DramaMovie::operator<(DramaMovie & other) const
{
	if (this->director == other.director)
	{
		return true;
	}
	return this->title == other.title;
}

bool DramaMovie::operator>(DramaMovie & other) const
{
	return !(*this < other) && !(*this == other);
}

string DramaMovie::getInfo() const
{
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Director: " + director;
}
