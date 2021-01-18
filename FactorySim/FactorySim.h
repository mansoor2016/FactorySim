#pragma once

#include <array>
#include <memory>

#include "Worker.h"
#include "ITimeStepping.h"
#include "ProductionLine.h"
#include "SimulationParameters.h"

#if defined NDEBUG
#define TRACE( statement, ... )
#else
#define TRACE( format, ... )   format
#endif


class FactorySim
{
public:
    using CurrentProductionLine = ProductionLine<SP::NSlots>;

    int RunSimulations(std::ostream& os);

    void ExecuteProductionLine(std::ostream& os);

private:
    std::shared_ptr<CurrentProductionLine> productionLine =
        std::make_shared<CurrentProductionLine>();

    std::array<std::unique_ptr<IWorker>, SP::NWorkers> workers =
    {
        std::make_unique<StationaryWorker>(productionLine, 0),
        std::make_unique<StationaryWorker>(productionLine, 2),
        std::make_unique<StationaryWorker>(productionLine, 4)
    };
};