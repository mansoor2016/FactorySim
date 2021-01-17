#pragma once

#include <optional>
#include <stdexcept>

#include "Components.h"
#include "ComponentHelpers.h"

#include "ProductP.h"
#include "ProductQ.h"
#include "ProductHelpers.h"

// If there were more than 2 types of products, would use decision tables instead
// (conditional branch approach would become unmanagable)
struct CombineComponents
{
	static std::optional<ProductType> ConstructType(ComponentType comp1, ComponentType comp2);
	
	static ProdBasePtr Construct(ComponentType comp1, ComponentType comp2);
};