#pragma once

struct SimulationParameters
{
	// These parameters could be read in from a configuration
	// file/command line (for simplicity hard coded)
	inline static const size_t NSlots = 5;
	inline static const size_t Steps = 100;
	inline static const size_t NWorkers = 3;
};

using SP = SimulationParameters;