#pragma once

#include <string>

#include "IComparable.h"
#include "ComponentBase.h"

class ComponentB :	public ComponentBase,
					public IComparable<ComponentB>
{
public:
	ComponentB() = default;

	std::string ToString() const override
	{
		return "B";
	}

	double SpawnProbability() const override
	{
		return 0.2;
	}
};