#include "ClassicMovie.h"

ClassicMovie::ClassicMovie(string title, int stock, string director, int releaseYear,
	int releaseMonth, string majorActor, string mediaType)
	: Movie(title, stock, director, releaseYear, mediaType)
{
	this->releaseMonth = releaseMonth;
	this->majorActor = majorActor;
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
	return majorActor;
}

bool ClassicMovie::operator==(ClassicMovie & other) const
{
	 return this->releaseYear == other.releaseYear && this->releaseMonth == other.releaseMonth
		&& this->majorActor == other.majorActor;
}

bool ClassicMovie::operator<(ClassicMovie & other) const
{
	if (this->releaseYear < other.releaseYear && this->releaseMonth < other.releaseMonth)
	{
		return true;
	}
	return this->majorActor < other.majorActor;
}

bool ClassicMovie::operator>(ClassicMovie & other) const
{
	return !(*this < other) && !(*this == other);
}
