#include "Item.h"

Item::Item()
{
}

Item::Item(int stock)
{
	this->stock = stock;
}

Item::~Item()
{
}

int Item::getStock() const
{
	return stock;
}

bool Item::setStock(int newStock)
{
	if (newStock < 0)
	{
		return false;
	}
	stock = newStock;
}
