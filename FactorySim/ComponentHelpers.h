#pragma once

#include <string>
#include <stdexcept>

#include "ISlotItem.h"
#include "Components.h"

struct ComponentHelpers
{
	enum class ComponentType : size_t
	{
		A,
		B,
		C,
		Count,		// Number of valid component types
		Null,		// Null component (empty slot)
		Undefined,	// Component not classified yet
	};

	static bool IsComponent(const ISlotItem* item)
	{
		auto ptr = dynamic_cast<const ComponentBase*>(item);
		return ptr;
	}

	static ComponentType Classify(ComponentBase* comp)
	{
		if (dynamic_cast<ComponentA*>(comp))
		{
			return ComponentType::A;
		}
		else if (dynamic_cast<ComponentB*>(comp))
		{
			return ComponentType::B;
		}
		else if (dynamic_cast<ComponentC*>(comp))
		{
			return ComponentType::C;
		}
		else if (dynamic_cast<ComponentNull*>(comp))
		{
			return ComponentType::Null;
		}
		
		throw std::invalid_argument("Unexpected component type, unable to classify.");		
	}

	static std::string ClassifyToString(ComponentBase* comp)
	{
		if (dynamic_cast<ComponentA*>(comp))
		{
			return "A";
		}
		else if (dynamic_cast<ComponentB*>(comp))
		{
			return "B";
		}
		else if (dynamic_cast<ComponentC*>(comp))
		{
			return "C";
		}
		else if (dynamic_cast<ComponentNull*>(comp))
		{
			return "Null";
		}

		throw std::invalid_argument("Unexpected component type, unable to classify.");
	}

	static CompBasePtr Create(ComponentType comp)
	{
		switch (comp)
		{
		case ComponentType::A:
			return std::make_unique<ComponentA>();
			break;
		case ComponentType::B:
			return std::make_unique<ComponentB>();
			break;
		case ComponentType::C:
			return std::make_unique<ComponentC>();
			break;
		default:
			throw std::invalid_argument("Unexpectd product type, could not create");
			break;
		}
	};
};

using ComponentType = ComponentHelpers::ComponentType;