#include "ComponentHelpers.h"

bool ComponentHelpers::IsComponent(const ISlotItem* item)
{
	auto ptr = dynamic_cast<const ComponentBase*>(item);
	return ptr;
}

ComponentType ComponentHelpers::Classify(const ComponentBase* comp)
{
	if (dynamic_cast<const ComponentA*>(comp))
	{
		return ComponentType::A;
	}
	else if (dynamic_cast<const ComponentB*>(comp))
	{
		return ComponentType::B;
	}
	else if (dynamic_cast<const ComponentC*>(comp))
	{
		return ComponentType::C;
	}
	else if (dynamic_cast<const ComponentNull*>(comp))
	{
		return ComponentType::Null;
	}

	throw std::invalid_argument("Unexpected component type, unable to classify.");
}

std::string ComponentHelpers::ClassifyToString(ComponentBase* comp)
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

std::string ComponentHelpers::ClassifyToString(ComponentType comp)
{
	switch (comp)
	{
	case ComponentType::A:
		return "A";
		break;
	case ComponentType::B:
		return "B";
		break;
	case ComponentType::C:
		return "C";
		break;
	case ComponentType::Null:
		return "Null";
		break;
	default:
		throw std::invalid_argument("Unexpected component type, unable to classify.");
	}
}

CompBasePtr ComponentHelpers::Create(ComponentType comp)
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
		throw std::invalid_argument("Unexpected product type, could not create");
		break;
	}
};