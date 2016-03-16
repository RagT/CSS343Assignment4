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
