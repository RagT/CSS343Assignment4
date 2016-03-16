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
