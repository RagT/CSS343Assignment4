#include "ClassicMovie.h"

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

string ClassicMovie::getInfo() const
{
	return "Title: " + title + "   Release Year: " + to_string(releaseYear)
		+ "   Release Month: " + to_string(releaseMonth) + "   Director: " + director +
		"   Major Actor: " + majorActor;
}

