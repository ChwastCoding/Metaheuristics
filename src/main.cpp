#include "visualization/Visualization.h"
#include "tsp_data/ProblemFactory.h"
#include "solver/DummySolver.h"
#include "solver/NearestNeighbour.h"
#include "util.h"

#include <iostream>

int main()
{
    auto instance = ProblemFactory::createEuc2DInstance(100, 2050);
    NearestNeighbour solver(instance, 12);

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