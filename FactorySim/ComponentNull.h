#pragma once

#include <string>

#include "IComparable.h"
#include "ComponentBase.h"

class ComponentNull :	public ComponentBase,
						public IComparable<ComponentNull>
{
public:
	ComponentNull() = default;

	std::string ToString() const override
	{
		return "";
	}

	virtual bool IsNull() const override
	{ 
		return true;
	}

	double SpawnProbability() const override
	{
		return 0.2;
	}
};