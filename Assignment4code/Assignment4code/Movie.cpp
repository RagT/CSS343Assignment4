#include "Movie.h"

int Movie::hashString(const string& str) const
{
	int code = 0;
	for (int i = 1; i <= str.length(); i++)
	{
		code += i * (int)str.at(i - 1);
	}
	return code;
}

Movie::Movie()
{
}

Movie::~Movie()
{
}

//Getters
string Movie::getTitle() const
{
  return title;
}

string Movie::getDirector() const
{
  return director;
}

int Movie::getReleaseYear() const
{
  return releaseYear;
}

