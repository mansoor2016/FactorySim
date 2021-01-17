#pragma once

#include <ostream>
#include <utility>
#include <unordered_map>

#include "ISlotItem.h"

class ItemOutputStatistics final
{
	using ItemVector = std::vector<ISlotItemPtr>;

	std::unordered_map<std::string, ItemVector> count;
	
	// ProcessData should only be invoked once and must be called before PrintCount 
	bool dataHasBeenProcessed = false;
	
	size_t finishedProductsCount = 0;
	size_t unusedComponentsCount = 0;

public:
	void IngestItem(ISlotItemPtr item);

	void ProcessData();

	void PrintCount(std::ostream& os) const;
};
