#include "Transaction.h"



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