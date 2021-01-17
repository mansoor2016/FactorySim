#pragma once

#include <string>

#include "IComparable.h"
#include "ComponentBase.h"

class ComponentA :	public ComponentBase,
					public IComparable<ComponentA>
{
public:
	ComponentA() = default;

	std::string ToString() const override
	{
		return "A";
	}

	double SpawnProbability() const override
	{
		return 0.4;
	}
};