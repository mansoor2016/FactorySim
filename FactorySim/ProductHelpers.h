#pragma once

#include <string>
#include <stdexcept>

#include "Components.h"
#include "ProductP.h"
#include "ProductQ.h"

struct ProductHelpers
{
	enum ProductType : size_t
	{
		P,
		Q,
		Count,
		Undefined,
	};

	static ProductType Classify(ProductBase* comp);

	static std::string ClassifyToString(ProductBase* comp);

	static ProdBasePtr Create(ProductType prod);
};

using ProductType = ProductHelpers::ProductType;