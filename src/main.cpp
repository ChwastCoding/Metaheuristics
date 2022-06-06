#include "solver/DummySolver.h"
#include "solver/ExtNearestNeighbour.h"
#include "solver/K_RandomSolver.h"
#include "solver/NearestNeighbour.h"
#include "solver/TwoOptSolver.h"
#include "tsp_data/Parser.h"
#include "tsp_data/ProblemFactory.h"
#include "util.h"
#include "visualization/Visualization.h"

#include "experiments/testRandomTS.h"

#include "solver/genetic/Genetic.h"

std::shared_ptr<Solver> getSolver(std::shared_ptr<TSPInstance> instance,
                                  int argc,
                                  char** argv) {
  std::string mode = util::getCmdOption(argc, argv, "--solver");

  if (mode == "2Opt")
    return std::make_shared<TwoOptSolver>(instance);
  if (mode == "2Opt-NN")
    return std::make_shared<TwoOptSolver>(instance, true);
  if (mode == "NN") {
    return std::make_shared<NearestNeighbour>(
        instance, std::stoi(util::getCmdOption(argc, argv, "--starting-node")));
  }
  if (mode == "ExtNN")
    return std::make_shared<ExtNearestNeighbour>(instance);
  if (mode == "kRandom") {
    return std::make_shared<K_RandomSolver>(
        instance, std::stoi(util::getCmdOption(argc, argv, "--k")));
  } else
    throw std::runtime_error("unknown value of --solver");
}

std::shared_ptr<TSPInstance> getInstance(int argc, char** argv) {
  if (util::cmdOptionExists(argc, argv, "--from-file")) {
    return Parser::getInstance(util::getCmdOption(argc, argv, "--from-file"));
  }
  if (util::cmdOptionExists(argc, argv, "--seed")) {
    util::initializeRNG(std::stoi(util::getCmdOption(argc, argv, "--seed")));
  } else {
    util::initializeRNG();
  }

  int size;
  if (util::cmdOptionExists(argc, argv, "--size"))
    size = std::stoi(util::getCmdOption(argc, argv, "--size"));
  else
    size = 100;

  if (util::cmdOptionExists(argc, argv, "--matrix")) {
    return ProblemFactory::createMatrixInstance(
        std::stoi(util::getCmdOption(argc, argv, "--martrix")), size);
  }
  if (util::cmdOptionExists(argc, argv, "--euc2d")) {
    return ProblemFactory::createEuc2DInstance(
        std::stoi(util::getCmdOption(argc, argv, "--euc2d")), size);
  }
  throw std::runtime_error(
      "invalid parameter combination, can't create instance");
}

int main(int argc, char** argv) {
  if (false) {
      // testAllNeighbourhoodsTime();
      //testInvertTimeLT("invert_with_aspiration_time_lt_1000.csv", 1000);
      //testSingleNeighbourhoodTime(1, "invert_with_aspiration_time_no_lt_1000.csv", 1000);
  }
  else if (true || util::cmdOptionExists(argc, argv, "--graphic")) {
    util::initializeRNG();
    // auto instance = std::dynamic_pointer_cast<Euc2DInstance>(
    //     Parser::getInstance("../tests/ch130.tsp"));
    auto instance = ProblemFactory::createEuc2DInstance(100, 300);
    //TwoOptSolver solver(instance);
    Genetic solver(instance, Genetic::Operator::Order1, Genetic::InitialSolution::Random, 
    Genetic::MutationType::TwoOptM, Genetic::SelectionMethod::RandomSelection, .3, 50,
    30, 3, 10);
    Visualization vis;
    vis.setInstance(instance);

    while (vis.isOpen()) {
      solver.step();
      vis.setSolution(solver.getSolution());
      vis.draw(solver.calculateObjectiveFunction());
    }
  } else {
    auto instance = getInstance(argc, argv);
    auto solver = getSolver(instance, argc, argv);
    int stepLimit;
    if (util::cmdOptionExists(argc, argv, "--step-limit"))
      stepLimit = std::stoi(util::getCmdOption(argc, argv, "--step-limit"));
    else
      stepLimit = 0;

    int iterations = 0;
    while (solver->step() && (iterations < stepLimit || !stepLimit))
      iterations++;
    std::cout << solver->calculateObjectiveFunction() << " " << iterations
              << std::endl;
  }
  return 0;
}