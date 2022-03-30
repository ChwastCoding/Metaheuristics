#include "visualization/Visualization.h"
#include "tsp_data/ProblemFactory.h"
#include "solver/DummySolver.h"
#include "solver/TwoOptSolver.h"
#include "solver/K_RandomSolver.h"
#include "solver/NearestNeighbour.h"
#include "solver/ExtNearestNeighbour.h"
#include "util.h"

int main()
{
    util::initializeRNG();
    auto instance = ProblemFactory::createEuc2DInstance(100, 550);
    ExtNearestNeighbour solver(instance);
    Visualization vis;
    vis.setInstance(instance, 100);

    while (vis.isOpen())
    {
        solver.step();
        vis.setSolution(solver.getSolution());
        vis.draw(solver.calculateObjectiveFunction());
    }

    return 0;
}