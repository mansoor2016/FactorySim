#include <utility>
#include <iomanip>
#include <ostream>
#include <cassert>
#include <algorithm>

#include "ISlotItem.h"
#include "ItemOutputStatistics.h"


void ItemOutputStatistics::IngestItem(ISlotItemPtr item)
{
	this->count[item->ToString()].emplace_back(std::move(item));
}

void ItemOutputStatistics::ProcessData()
{
	assert(!dataHasBeenProcessed);

	for (const auto& itemType : count)
	{
		for (const auto& item : itemType.second)
		{
			if (item->IsProduct())
			{
				++finishedProductsCount;
			}
			else
			{
				++unusedComponentsCount;
			}
		}
	}

	dataHasBeenProcessed = true;
}

void ItemOutputStatistics::PrintCount(std::ostream& os) const
{
	assert(dataHasBeenProcessed);

	os << std::setw(20);
	os << "Items coming of the production Line: " << std::endl;

	os << "Counts:" << std::endl;
	for (const auto& itemType : count)
	{
		os	<< itemType.first
			<< " " 
			<< itemType.second.size() 
			<< std::endl;
	}

	os << std::endl;

	os << "Summary: " << std::endl;
	os << "Finished products: "			<< finishedProductsCount << std::endl;
	os << "Unused (wasted) components " << unusedComponentsCount << std::endl;	
}
