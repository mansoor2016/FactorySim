#include "ComponentRandomGenerator.h"

ComponentRandomGenerator::ComponentRandomGenerator()
{
	for (const auto& comp : components)
	{
		upperLimit += comp->SpawnProbability();
	}
	assert(upperLimit > 0.0);

	std::default_random_engine gen(rd());
	this->gen = gen;

	uniform_dist = std::uniform_real_distribution<double>{ 0.0, upperLimit };
}

CompBasePtr ComponentRandomGenerator::Generate()
{
	const auto val = uniform_dist(gen);

	double range = 0;
	for (auto& comp : components)
	{
		if (val < (range + comp->SpawnProbability()))
		{
			if (!comp->IsNull())
			{
				return ComponentHelpers::Create(ComponentHelpers::Classify(comp.get()));
			}
		}

		range += comp->SpawnProbability();
	}

	return nullptr;
}