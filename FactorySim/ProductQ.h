#pragma once

#include "ProductBase.h"

class ProductQ : public ProductBase
{
public:
	std::string ToString() const override
	{
		return "Q";
	}
};