#include "Transaction.h"

Transaction::Transaction()
{
	itemCheckedOut = NULL;
	returned = true;
	custID = 0;
	mediaType = 'Z';
}

Transaction::Transaction(Item* item)
{
	itemCheckedOut = item;
}


Transaction::~Transaction()
{
}

Item* Transaction::getItem()
{
	return itemCheckedOut;
}

int Transaction::getCustID()
{
	return custID;
}

char Transaction::getMedia()
{
	return mediaType;
}

bool Transaction::isReturned() const
{
	return returned;
}

void Transaction::returnItem()
{
	returned = true;
}

void Transaction::setBorrowed()
{
	returned = false;
}

void Transaction::setMediaType(char other)
{
	mediaType = other;
}

void Transaction::setCustID(int other)
{
	custID = other;
}

void Transaction::display()
{
	cout << "Borrow by " << "Customer: " << custID << " " << itemCheckedOut->getInfo() << endl;
	if (returned)
	{
		cout << "Return by " << "Customer: " << custID << " " << itemCheckedOut->getInfo() << endl;
	}
}
