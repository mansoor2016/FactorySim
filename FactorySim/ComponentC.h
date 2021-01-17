#pragma once

#include <string>

#include "IComparable.h"
#include "ComponentBase.h"

class ComponentC :	public ComponentBase,
					public IComparable<ComponentC>
{
public:
	ComponentC() = default;

	std::string ToString() const override
	{
		return "C";
	}

	double SpawnProbability() const override
	{
		return 0.2;
	}
};