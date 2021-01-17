#pragma once

#include <string>
#include <stdexcept>

#include "ISlotItem.h"
#include "ComponentBase.h"

#include "ComponentA.h"
#include "ComponentB.h"
#include "ComponentC.h"
#include "ComponentNull.h"


struct ComponentHelpers
{
	enum class ComponentType : size_t
	{
		A,
		B,
		C,
		Count,		// Number of valid component types
		Null,		// Null component (empty slot)
		Undefined,	// Component not classified yet (uninit)
	};

	static bool IsComponent(const ISlotItem* item);

	static ComponentType Classify(const ComponentBase* comp);

	static std::string ClassifyToString(ComponentBase* comp);

	static std::string ClassifyToString(ComponentType comp);

	static CompBasePtr Create(ComponentType comp);
};

using ComponentType = ComponentHelpers::ComponentType;