#pragma once

#include <memory>
#include <string>
#include <utility>

#include "ISlotItem.h"

class ComponentBase : public ISlotItem
{
public:
	virtual ~ComponentBase() = default;

	virtual double SpawnProbability() const = 0;

	virtual bool IsNull() const { return false; }

	bool IsProduct() const override { return false; }
};

using CompBasePtr = std::unique_ptr<ComponentBase>;