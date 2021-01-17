#pragma once

#include <ostream>

class ITimeStepping
{
public:
	virtual ~ITimeStepping() = default;

	virtual void Step() = 0;

	virtual void PostProcess(std::ostream& os) = 0;
};