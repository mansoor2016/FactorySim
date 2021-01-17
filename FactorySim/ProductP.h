#pragma once

#include <string>

#include "ProductBase.h"

class ProductP : public ProductBase
{
public:
	std::string ToString() const override
	{
		return "P";
	}
};