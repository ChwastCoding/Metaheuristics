#include "../solver/TabuSearch.h"
#include "../tsp_data/Parser.h"
#include "../tsp_data/ProblemFactory.h"
#include "../util.h"
#include "../solver/K_RandomSolver.h"
#include "../neighborhoods/Invert.h"
#include "../neighborhoods/Insert.h"
#include "../neighborhoods/Swap.h"
#include "../neighborhoods/Neighborhood.h"
#include "../solver/TS_long_term_mem.h"

#include <fstream>
#include <chrono>

TSPInstance::solution getRandomSolution(int size) {
    static std::default_random_engine rng;
    
    TSPInstance::solution solution(size);
    std::iota(solution.begin(), solution.end(), 0);
    std::shuffle(solution.begin(), solution.end(), rng);
    return solution;
}

// Invert Insert Swap
void testSingleNeighbourhood(int n_index, std::string filename, int steps = 200, int size = 100, int range = 100) {
    std::ofstream file;
    file.open(filename);
    
    int bar = 20;
    for (int j = 1; j <= bar; j ++) {
        util::initializeRNG(j);
        auto instance = ProblemFactory::createEuc2DInstance(range, size);
        auto solution = getRandomSolution(size);
        std::shared_ptr<Neighborhood> n;
        if (n_index == 1) {
            n = std::make_shared<Invert>(instance);
        } else if (n_index == 2) {
            n = std::make_shared<Insert>(instance);
        } else {
            n = std::make_shared<Swap>(instance);
        }

        TabuSearch solver(instance, solution, n, TabuSearch::NO_CONDITION, true);

        std::cout << j << std::endl;
        for (int i = 1; i <= steps; i++) {
          solver.step();
          if (i == 50 || i == 100 || i == 200) {
              file << solver.calculateObjectiveFunction() << ",";
          }
        }
        file << "\n";
    }
    file.close();
}

void testSingleNeighbourhoodTime(int n_index, std::string filename, int size = 100, int range = 100) {
    std::ofstream file;
    file.open(filename);
    
    int bar = 20;
    for (int j = 1; j <= bar; j ++) {
        util::initializeRNG(j);
        auto instance = ProblemFactory::createEuc2DInstance(range, size);
        auto solution = getRandomSolution(size);
        std::shared_ptr<Neighborhood> n;
        if (n_index == 1) {
            n = std::make_shared<Invert>(instance);
        } else if (n_index == 2) {
            n = std::make_shared<Insert>(instance);
        } else {
            n = std::make_shared<Swap>(instance);
        }

        TabuSearch solver(instance, solution, n, TabuSearch::NO_CONDITION, true);

        std::cout << j << " timed" << std::endl;
        auto previous = std::chrono::high_resolution_clock::now();
        auto current = previous;
        int count = 1;

        while (true) {
          solver.step();
          auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(current - previous).count();
          if (
              diff > count * 1000
              // (count == 0 && diff > 100) ||
              // (count == 1 && diff > 500) ||
              // (count == 2 && diff > 1000) ||
              // (count == 3 && diff > 2000) 
          ) {
              file << solver.calculateObjectiveFunction() << ",";
              if (count == 8) break;
              count ++;
          }
          current = std::chrono::high_resolution_clock::now();
        }
        file << "\n";
    }
    file.close();
}

void testAllNeighbourhoods() {
    testSingleNeighbourhood(1, "invert_with_aspiration.csv");
    testSingleNeighbourhood(2, "insert_with_aspiration.csv");
    testSingleNeighbourhood(3, "swap_with_aspiration.csv");
}

void testAllNeighbourhoodsTime() {
    testSingleNeighbourhoodTime(1, "invert_with_aspiration_time.csv");
    testSingleNeighbourhoodTime(2, "insert_with_aspiration_time.csv");
    testSingleNeighbourhoodTime(3, "swap_with_aspiration_time.csv");
}

// poniewaz invert jest najlepszy w prawie kazdym budzecie tylko on bedzie testoway dalej



void testInvertTimeLT(std::string filename, int size = 100, int range = 100){
    std::ofstream file;
    file.open(filename);
    
    int bar = 20;
    for (int j = 1; j <= bar; j ++) {
        util::initializeRNG(j);
        auto instance = ProblemFactory::createEuc2DInstance(range, size);
        auto solution = getRandomSolution(size);
        std::shared_ptr<Neighborhood> n = std::make_shared<Invert>(instance);

        TS_long_term_mem solver(instance, solution, n, TabuSearch::NO_CONDITION, true);

        std::cout << j << " timed" << std::endl;
        auto previous = std::chrono::high_resolution_clock::now();
        auto current = previous;
        int count = 1;

        while (true) {
          solver.step();
          auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(current - previous).count();
          if (
              diff > count * 1000
          ) {
              file << solver.calculateObjectiveFunction() << ",";
              if (count == 8) break;
              count ++;
          }
          current = std::chrono::high_resolution_clock::now();
        }
        file << "\n";
    }
    file.close();
}