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

	static ProductType Classify(ProductBase* comp)
	{
		if (dynamic_cast<ProductP*>(comp))
		{
			return ProductType::P;
		}
		else if (dynamic_cast<ProductQ*>(comp))
		{
			return ProductType::Q;
		}
		else
		{
			throw std::invalid_argument("Unexpected product type, unable to classify.");
		}
	}

	static std::string ClassifyToString(ProductBase* comp)
	{
		if (dynamic_cast<ProductP*>(comp))
		{
			return "P";
		}
		else if (dynamic_cast<ProductQ*>(comp))
		{
			return "Q";
		}
		else
		{
			throw std::invalid_argument("Unexpected product type, unable to classify.");
		}
	}

	static ProdBasePtr Create(ProductType prod)
	{
		switch (prod)
		{
		case ProductType::P:
			return std::make_unique<ProductP>();
			break;
		case ProductType::Q:
			return std::make_unique<ProductQ>();
			break;
		default:
			throw std::invalid_argument("Unexpectd product type, could not create");
			break;
		}
	};
};

using ProductType = ProductHelpers::ProductType;