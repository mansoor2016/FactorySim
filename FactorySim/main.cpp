#include <iostream>

#include "FactorySim.h"

int main(int argc, char** argv)
{
	FactorySim factory;

	return factory.RunSimulations(std::cout);
}
