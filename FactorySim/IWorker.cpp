#include "IWorker.h"

IWorker::IWorker(CurrentProductionLine pl) :
	productionLine(pl)
{
};

void IWorker::Step()
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

void IWorker::ResetHeldComponents()
{
	comp1.first = nullptr;
	comp1.second = ComponentType::Undefined;

	comp2.first = nullptr;
	comp2.second = ComponentType::Undefined;
}

void IWorker::ResetHeldProduct()
{
	constructedProduct = nullptr;
}

void IWorker::PrintWorker(std::ostream& os) const
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

void IWorker::PostProcess(std::ostream&) 
{
};