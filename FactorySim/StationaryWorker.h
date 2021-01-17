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
	
	void PickItem1() override;
	void PickItem2() override;
	void CombineComponents() override;

	void PlaceProductOnConveyorBelt() override;

public:
	StationaryWorker(CurrentProductionLine pl, size_t ConveyerBeltPosition);
};