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
#include "ComponentHelpers.h"

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
	ComponentRandomGenerator();

	CompBasePtr Generate();
};