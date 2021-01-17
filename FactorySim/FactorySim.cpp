#include <memory>
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
        for (size_t step = 0; step < SP::Steps; ++step)
        {
            isDebug ? [&] { os << "Steps: " << step << std::endl; }() : (void)(0);

            productionLine->Step();
            isDebug ? productionLine->PrintConveyerBelt(os) : (void)(0);

            std::for_each(workers.begin(), workers.end(), 
                [&](auto& worker) 
                {
                    worker->Step();
                    isDebug ? worker->PrintWorker(os) : (void)(0);
                });
        }

        productionLine->PostProcess(os);
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