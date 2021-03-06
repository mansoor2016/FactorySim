#include "ConstructProduct.h"

// If there were more than 2 types of products, would use decision tables instead
std::optional<ProductType> CombineComponents::ConstructType(ComponentType comp1, ComponentType comp2)
{
	if ((comp1 == ComponentType::A && comp2 == ComponentType::B) ||
		(comp1 == ComponentType::B && comp2 == ComponentType::A))
	{
		return ProductType::P;
	}
	else if ((comp1 == ComponentType::A && comp2 == ComponentType::C) ||
		(comp1 == ComponentType::C && comp2 == ComponentType::A))
	{
		return ProductType::Q;
	}

	return {};
}

ProdBasePtr CombineComponents::Construct(ComponentType comp1, ComponentType comp2)
{
	auto prod = CombineComponents::ConstructType(comp1, comp2);

	if (prod.has_value())
	{
		return ProductHelpers::Create(prod.value());
	}

	throw std::logic_error("Tried to construct product from components: "
		+ ComponentHelpers::ClassifyToString(comp1) + ", " +
		ComponentHelpers::ClassifyToString(comp2));
}