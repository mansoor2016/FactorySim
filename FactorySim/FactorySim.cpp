#include <memory>
#include <future>
#include <vector>
#include <utility>
#include <ostream>
#include <iostream>
#include <algorithm>

#include "FactorySim.h"
#include "ProductionLine.h"

int FactorySim::RunSimulations(std::ostream& os)
{
    try
    {
        ExecuteProductionLine(os);
        return 0;
    }
    catch (std::exception& ex)
    {
        std::cerr << "Expection occured in RunSimulation"
                  << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Encountered unhandled exception in RunSimulations."
                  << std::endl;
    }

    return -1;
}

void FactorySim::ExecuteProductionLine(std::ostream& os)
{
    for (size_t step = 0; step < SP::Steps; ++step)
    {
        TRACE(os << "Steps: " << step << std::endl;);

        productionLine->Step();
        TRACE(productionLine->PrintConveyerBelt(os));

        std::vector<std::future<void>> futures;
        futures.reserve(SP::NWorkers);

        for (auto& worker : workers)
        {
            futures.push_back(
                std::async(
                    std::launch::async,
                    [&]
                    {
                        worker->Step();
                        TRACE(worker->PrintWorker(os));
                    }));
        }

        std::for_each(futures.begin(), futures.end(),
            [&](auto& future) 
            { 
                future.wait();
            });
    }

    productionLine->PostProcess(os);
}
