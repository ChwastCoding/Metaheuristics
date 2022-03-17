#include "visualization/Visualization.h"
#include "tsp_data/ProblemFactory.h"
#include "solver/DummySolver.h"
#include "util.h"

#include <iostream>

int main()
{
    auto instance = ProblemFactory::createEuc2DInstance(100, 50);
    DummySolver solver(instance);

    Visualization vis;
    vis.setInstance(instance, 100);
    
    while (vis.isOpen())
    {
        solver.step();
        vis.setSolution(solver.getSolution());
        vis.draw();
    }

    return 0;
}