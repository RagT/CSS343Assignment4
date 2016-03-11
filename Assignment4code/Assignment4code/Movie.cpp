#include "Movie.h"



Movie::Movie(string title, int stock, string director, int releaseYear, string mediaType):Item(stock)
{
  this->title = title;
  this->director = director;
  this->releaseYear = releaseYear;
  this->mediaType = mediaType;
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

string Movie::getMediaType() const
{
  return mediaType;
}
