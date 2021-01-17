#include "StationaryWorker.h"

void StationaryWorker::PickItem1()
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

void StationaryWorker::PickItem2()
{
	if (productionLine->IsPositionEmpty(position))
	{
		return;
	}

	const ISlotItem* item = productionLine->ViewItemAtPosition(position).get();
	if (ComponentHelpers::IsComponent(item))
	{
		auto currentComp = dynamic_cast<const ComponentBase*>(item);
		auto currentCompType = ComponentHelpers::Classify(currentComp);

		if (CombineComponents::ConstructType(comp1.second, currentCompType).has_value())
		{
			auto currentComp = productionLine->RemoveComponentFromSlot(position);
			comp2 = std::make_pair(std::move(currentComp), currentCompType);
			status = WorkerStatus::CombiningComponents;
		}
	}
};

void StationaryWorker::CombineComponents()
{
	// This step could be made more generic (take more than 1 step)
	constructedProduct = CombineComponents::Construct(comp1.second, comp2.second);
	ResetHeldComponents();
	status = WorkerStatus::PlaceProductOnConveyorBelt;
};

void StationaryWorker::PlaceProductOnConveyorBelt()
{
	if (productionLine->IsPositionEmpty(position))
	{
		productionLine->PlaceProductAtLocation(std::move(constructedProduct), position);
		status = WorkerStatus::PickUpItem1;
	}
};

StationaryWorker::StationaryWorker(CurrentProductionLine pl, size_t ConveyerBeltPosition) :
	IWorker(pl), position(ConveyerBeltPosition)
{
	assert(position < CurrentProductionLine::element_type::NumberOfSlots);
}
