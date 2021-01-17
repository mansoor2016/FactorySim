#pragma once

#include <array>
#include <memory>
#include <random>
#include <cassert>
#include <numeric>

#include "Components.h"
#include "ComponentA.h"
#include "ComponentB.h"
#include "ComponentC.h"
#include "ComponentNull.h"

class ComponentRandomGenerator
{
	std::array<CompBasePtr, 4> components {
		std::make_unique<ComponentA>(),
		std::make_unique<ComponentB>(),
		std::make_unique<ComponentC>(),
		std::make_unique<ComponentNull>(),
	};

	std::random_device rd;
	std::default_random_engine gen;
	std::uniform_real_distribution<double> uniform_dist;

	double upperLimit = 0.0;

public:
	ComponentRandomGenerator()
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

	CompBasePtr Generate() 
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
};