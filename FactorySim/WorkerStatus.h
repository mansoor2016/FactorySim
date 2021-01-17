#pragma once

enum class WorkerStatus : size_t
{
	PickUpItem1,
	PickUpItem2,
	CombiningComponents,
	PlaceProductOnConveyorBelt,
};

static std::string WorkerStatusToString(WorkerStatus status)
{
	switch (status)
	{
	case WorkerStatus::PickUpItem1: 
		return "Picking up Item 1";
		break;
	case WorkerStatus::PickUpItem2:
		return "Picking up Item 2";
		break;
	case WorkerStatus::CombiningComponents:
		return "Constructing product.";
		break;
	case WorkerStatus::PlaceProductOnConveyorBelt:
		return "Finding free slot to place product.";
		break;
	default:
		throw std::invalid_argument("Unable to find free slot to place product");
	}
}