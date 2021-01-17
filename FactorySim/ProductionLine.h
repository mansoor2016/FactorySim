#pragma once

// Implementation is in the header file because this is a template class

#include <array>
#include <memory>
#include <ostream>
#include <algorithm>

#include "SlotItems.h"
#include "ITimeStepping.h"
#include "ItemOutputStatistics.h"
#include "SimulationParameters.h"

template <size_t NSlots>
class ProductionLine : public ITimeStepping
{
	// Could implement this as a circular buffer
	std::array<ISlotItemPtr, NSlots> productionLine = { nullptr };

	ItemOutputStatistics outputStats;

	void ProcessItemInFinalSlot()
	{
		if (!productionLine.back().get())
		{
			return;
		}

		ISlotItemPtr item{ productionLine.back().release() };
		outputStats.IngestItem(std::move(item));
	}

	void MoveBeltAlong()
	{
		for (size_t idx = (NSlots-1); idx > 0; --idx)
		{
			auto ptr = productionLine[idx - 1].release();
			productionLine[idx].reset(std::move(ptr));
		}
	}

	void SpawnItemFirstSlot()
	{
		ComponentRandomGenerator generator;
		productionLine[0].reset(generator.Generate().release());
	}

public:
	ProductionLine() = default;

	const static size_t NumberOfSlots = NSlots;

	void Step() override
	{
		ProcessItemInFinalSlot();
		MoveBeltAlong();
		SpawnItemFirstSlot();
	};

	void PostProcess(std::ostream& os)
	{
		outputStats.ProcessData();
		return outputStats.PrintCount(os);
	}

	bool IsPositionEmpty(size_t slotPosition)
	{
		return productionLine[slotPosition] == nullptr;
	}

	const ISlotItemPtr& ViewItemAtPosition(size_t slotPosition)
	{
		return productionLine[slotPosition];
	}

	CompBasePtr RemoveComponentFromSlot(size_t slotPosition)
	{
		ISlotItemPtr& item = productionLine[slotPosition];
		
		if (ComponentHelpers::IsComponent(item.get()))
		{
			ComponentBase* removedComponent = dynamic_cast<ComponentBase*>(item.release());
			return std::unique_ptr<ComponentBase>(removedComponent);
		}

		return nullptr;
	}

	void PlaceProductAtLocation(
		ProdBasePtr product,
		size_t slotPosition)
	{
		productionLine[slotPosition].reset(product.release());
	}

	// For debugging purposes
	void PrintConveyerBelt(std::ostream& os)
	{
		os << " | ";
		
		for (size_t idx = 0; idx < productionLine.size(); ++idx)
		{
			if (!IsPositionEmpty(idx))
			{
				auto item = productionLine[idx].get();
				if (ComponentHelpers::IsComponent(item))
				{
					ComponentBase* comp = dynamic_cast<ComponentBase*>(item);
					if (comp)
					{
						os << comp->ToString();
					}
				}
				else
				{
					ProductBase* prod = dynamic_cast<ProductBase*>(item);
					if (prod)
					{
						os << prod->ToString();
					}
				}
			}

			os << " | ";
		}

		os << std::endl;
	}
};

using CurrentProductionLine = std::shared_ptr<ProductionLine<SP::NSlots>>;
