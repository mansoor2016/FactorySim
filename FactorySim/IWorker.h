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
	IWorker(CurrentProductionLine pl) : productionLine(pl) {  }

	void Step() override
	{
		switch (status)
		{
		case WorkerStatus::PickUpItem1:
		{
			PickItem1();
			break;
		}
		case WorkerStatus::PickUpItem2:
		{
			PickItem2();
			break;
		}
		case WorkerStatus::CombiningComponents:
		{
			CombineComponents();
			break;
		}
		case WorkerStatus::PlaceProductOnConveyorBelt:
		{
			PlaceProductOnConveyorBelt();
			break;
		}
		default:
			assert(false && "Unexpected worker status, no implementation");
			break;
		}
	}
	
	void ResetHeldComponents()
	{
		comp1.first = nullptr;
		comp1.second = ComponentType::Undefined;

		comp2.first = nullptr;
		comp2.second = ComponentType::Undefined;
	}

	void ResetHeldProduct()
	{
		constructedProduct = nullptr;
	}

	void PrintWorker(std::ostream& os) const
	{
		os << "Worker status: " << WorkerStatusToString(status) << std::endl;

		if (comp1.first)
		{
			os << "Item 1: "
				<< ComponentHelpers::ClassifyToString(comp1.first.get())
				<< std::endl;
		}

		if (comp2.first)
		{
			os << "Item 2: "
				<< ComponentHelpers::ClassifyToString(comp2.first.get())
				<< std::endl;
		}

		if (constructedProduct)
		{
			os << "Product: "
				<< ProductHelpers::ClassifyToString(constructedProduct.get())
				<< std::endl;
		}
	}


	void PostProcess(std::ostream&) override {};

	virtual ~IWorker() = default;
};