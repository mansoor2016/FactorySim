#pragma once

#include <memory>
#include <string>

/// <summary>
/// Define the interface for any item that can occupy a slot on the
/// conveyor belt
/// </summary>
class ISlotItem
{
public:
	virtual ~ISlotItem() = default;

	virtual std::string ToString() const = 0;

	virtual bool IsProduct() const = 0;
};

using ISlotItemPtr = std::unique_ptr<ISlotItem>;