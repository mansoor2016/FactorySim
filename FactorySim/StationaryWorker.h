#pragma once

#include <cassert>

#include "IWorker.h"
#include "ISlotItem.h"
#include "Components.h"
#include "ComponentHelpers.h"
#include "ProductionLine.h"

class StationaryWorker final : public IWorker
{
	const size_t position;
	
	void PickItem1() override 
	{
		if (productionLine->IsPositionEmpty(position))
		{
			return;
		}

		const ISlotItem* item = productionLine->ViewItemAtPosition(position).get();
		
		if (ComponentHelpers::IsComponent(item))
		{
			comp1.first = productionLine->RemoveComponentFromSlot(position);
			comp1.second = ComponentHelpers::Classify(comp1.first.get());
			status = WorkerStatus::PickUpItem2;
		}
	};

	void PickItem2() override 
	{
		if (productionLine->IsPositionEmpty(position))
		{
			return;
		}

		const ISlotItem* item = productionLine->ViewItemAtPosition(position).get();

		if (ComponentHelpers::IsComponent(item))
		{
			auto currentComp = productionLine->RemoveComponentFromSlot(position);
			auto currentCompType = ComponentHelpers::Classify(currentComp.get());

			if (currentCompType != comp1.second)
			{
				comp2 = std::make_pair(std::move(currentComp), currentCompType);
				status = WorkerStatus::CombiningComponents;
			}
		}
	};

	void CombineComponents() override 
	{
		// This step could be made more generic (take more than 1 step)
		constructedProduct = CombineComponents::Construct(comp1.second, comp2.second);
		ResetHeldComponents();
		status = WorkerStatus::PlaceProductOnConveyorBelt;
	};

	void PlaceProductOnConveyorBelt() override 
	{
		if (productionLine->IsPositionEmpty(position))
		{
			productionLine->PlaceProductAtLocation(std::move(constructedProduct), position);
			status = WorkerStatus::PickUpItem1;
		}		
	};

public:
	StationaryWorker(CurrentProductionLine pl, size_t ConveyerBeltPosition) :
		IWorker(pl), position(ConveyerBeltPosition) 
	{
		assert(position < CurrentProductionLine::element_type::NumberOfSlots);
	}
};