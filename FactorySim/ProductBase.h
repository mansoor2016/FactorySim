#pragma once

#include <memory>
#include <utility>

#include "ISlotItem.h"

class ProductBase : public ISlotItem
{
public:
	virtual ~ProductBase() = default;

	virtual bool IsProduct() const override { return true; }
};

// Aliases for convenience
using ProdBasePtr = std::unique_ptr<ProductBase>;