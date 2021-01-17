#include "ProductHelpers.h"


ProductType ProductHelpers::Classify(ProductBase* comp)
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

std::string ProductHelpers::ClassifyToString(ProductBase* comp)
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

ProdBasePtr ProductHelpers::Create(ProductType prod)
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
		throw std::invalid_argument("Unexpected product type, could not create");
		break;
	}
};