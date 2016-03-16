#include "Movie.h"



Movie::Movie(string title, int stock, string director, int releaseYear):Item(stock)
{
  this->title = title;
  this->director = director;
  this->releaseYear = releaseYear;
}


int Movie::hashString(const string& str) const
{
	int code = 0;
	for (int i = 1; i <= str.length; i++)
	{
		code += i * (int)str.at(i);
	}
	return code;
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

int Movie::hashCode() const
{
	return hashString(title) + hashString(director) + releaseYear + hashString(mediaType);
}

/*string Movie::getMediaType() const
{
  return mediaType;
}*/
