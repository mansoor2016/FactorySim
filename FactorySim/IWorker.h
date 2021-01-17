#pragma once

#include <memory>
#include <cassert>
#include <ostream>

#include "Components.h"
#include "WorkerStatus.h"
#include "ITimeStepping.h"
#include "ProductionLine.h"
#include "SimulationParameters.h"

class IWorker : public ITimeStepping
{
protected:
	using CompPtrEnum = std::pair<CompBasePtr, ComponentType>;

	CurrentProductionLine productionLine;
	WorkerStatus status = WorkerStatus::PickUpItem1;

	CompPtrEnum comp1 = { nullptr, ComponentType::Undefined };
	CompPtrEnum comp2 = { nullptr, ComponentType::Undefined };
	ProdBasePtr constructedProduct = nullptr;

	virtual void PickItem1() = 0;
	virtual void PickItem2() = 0;
	virtual void CombineComponents() = 0;
	virtual void PlaceProductOnConveyorBelt() = 0;

public:
	IWorker(CurrentProductionLine pl);

	void Step() override;
	
	void ResetHeldComponents();

	void ResetHeldProduct();

	void PrintWorker(std::ostream& os) const;

	void PostProcess(std::ostream&) override;

	virtual ~IWorker() = default;
};