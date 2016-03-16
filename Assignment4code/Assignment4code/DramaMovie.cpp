#include "DramaMovie.h"

DramaMovie::DramaMovie(string title, int stock, string director, int releaseYear, string mediaType)
	: Movie(title, stock, director, releaseYear, mediaType) 
{

}

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
		+ "   Director: " + director + " Media Type: " + mediaType;
}
