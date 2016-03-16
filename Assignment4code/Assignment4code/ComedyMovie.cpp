#include "ComedyMovie.h"

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
