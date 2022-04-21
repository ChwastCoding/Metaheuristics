#include <gtest/gtest.h>
#include "../src/tsp_data/Euc2DInstance.h"
#include "../src/tsp_data/MatrixInstance.h"
#include "../src/tsp_data/Parser.h"
#include "../src/util.h"
#include "../src/tsp_data/ProblemFactory.h"
#include "../src/solver/K_RandomSolver.h"
#include "../src/solver/NearestNeighbour.h"
#include "../src/solver/ExtNearestNeighbour.h"
#include "../src/neighborhoods/Neighborhood.h"
#include "../src/neighborhoods/Invert.h"
#include "../src/solver/TabuSearch.h"
#include "../src/solver/TwoOptSolver.h"
#include "../src/neighborhoods/Swap.h"
#include "../src/neighborhoods/Insert.h"

typedef std::pair<int, int> intPair;
const std::string pathToOriginalEuclidian = "../../tests/ch130.tsp";
const std::string pathToCopyEuclidian = "ch130_copy.tsp";
const std::string pathToOriginalMatrix = "../../tests/br17.atsp";
const std::string pathToBrg180 = "../../tests/brg180.tsp";
const std::string pathToBrg180Copy = "brg180_copy.tsp";
const std::string pathToCopyMatrix = "br17_copy.atsp";
const std::string pathToRandomEuclid = "random_euclid.tsp";
const std::string pathToRandomMatrix = "random_matrix.atsp";


TEST(setup_test, test_1) {
    std::string s = "lorem ipsum";
    ASSERT_EQ(s, s.substr(0, s.find(':')));
    Euc2DInstance e(10);
    ASSERT_TRUE(true);
}

TEST(util, test_trim_whitespace) {
    std::string s = "lorem ipsum   ", s2 = "test", s3 = "    test";
    ASSERT_EQ(util::trimWhitespace(s), "lorem ipsum");
    ASSERT_EQ(s2, util::trimWhitespace(s2));
    ASSERT_EQ(s2, util::trimWhitespace(s3));
}

TEST(parser_test, loading_euclidian) {
    auto instance = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginalEuclidian));
    ASSERT_EQ(instance->getSize(), 130);
    ASSERT_EQ(instance->getName(), "ch130");
    ASSERT_EQ(instance->getCoords(0), intPair(335, 162));
}

TEST(parser_test, saving_euclidian) {
    auto instance = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginalEuclidian));
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToCopyEuclidian));

    auto instance_copy = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginalEuclidian));
    ASSERT_EQ(instance->getSize(), instance_copy->getSize());
    ASSERT_EQ(instance->getName(), instance_copy->getName());
    for (int i = 0; i < instance->getSize(); i++ ) {
        ASSERT_EQ(instance->getCoords(i), instance_copy->getCoords(i));
    }
}

TEST(parser_test, loading_matrix) {
    auto instance = std::dynamic_pointer_cast<MatrixInstance>(Parser::getInstance(pathToOriginalMatrix));
    ASSERT_EQ(instance->getSize(), 17);
    ASSERT_EQ(instance->getName(), "br17");
    ASSERT_EQ(instance->getCost(0, 1), 3);
}

TEST(parser_test, saving_matrix) {
    auto instance = std::dynamic_pointer_cast<MatrixInstance>(Parser::getInstance(pathToOriginalMatrix));
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToCopyMatrix));

    auto instance_copy = std::dynamic_pointer_cast<MatrixInstance>(Parser::getInstance(pathToOriginalMatrix));
    ASSERT_EQ(instance->getSize(), instance_copy->getSize());
    ASSERT_EQ(instance->getName(), instance_copy->getName());
    for(int i = 0; i < instance->getSize(); i ++) {
        for(int j = 0; j < instance->getSize(); j ++) {
            ASSERT_EQ(instance->getCost(i, j), instance_copy->getCost(i, j));
        }
    }
}

TEST(parset_test, loading_upper_row) {
    std::shared_ptr<TSPInstance> instance;
    int infty = MatrixInstance::infty;

    ASSERT_NO_THROW(instance = Parser::getInstance(pathToBrg180));
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToBrg180Copy));
    ASSERT_EQ(instance->getCost(0, 1), 20);
    ASSERT_EQ(instance->getCost(1, 1), infty);
    ASSERT_EQ(instance->getCost(1, 3), 10000);
}

TEST(problem_factory, create_euclid) {
    auto instance = ProblemFactory::createEuc2DInstance(100, 20);
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToRandomEuclid));
}


TEST(problem_factory, create_matrix) {
    auto instance = ProblemFactory::createMatrixInstance(100, 20);
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToRandomMatrix));
}

TEST(k_random_solver, solve){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalEuclidian));
    K_RandomSolver kRandomSolver(instance, 1000);
    while(kRandomSolver.step()){}
    ASSERT_TRUE(kRandomSolver.getSolution().size() == instance->getSize());
    TSPInstance::solution s;
    s.resize(instance->getSize());
    std::iota(s.begin(), s.end(), 0);
    ASSERT_FALSE(kRandomSolver.getSolution() == s);
    for(int i = 0; i < kRandomSolver.getSolution().size(); i++){
        ASSERT_TRUE(std::find(kRandomSolver.getSolution().begin(), kRandomSolver.getSolution().end(), i) != kRandomSolver.getSolution().end());
    }
}

TEST(nearest_neighbour_solver, solve){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalEuclidian));
    NearestNeighbour nn(instance, 1);
    while(nn.step()){}
    ASSERT_TRUE(nn.getSolution().size() == instance->getSize());
    for(int i = 0; i < nn.getSolution().size(); i++){
        ASSERT_TRUE(std::find(nn.getSolution().begin(), nn.getSolution().end(), i) != nn.getSolution().end());
    }
}

TEST(ext_nearest_neighbour_solver, solve){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalEuclidian));
    ExtNearestNeighbour extNearestNeighbour(instance);
    while(extNearestNeighbour.step());
    ASSERT_TRUE(extNearestNeighbour.getSolution().size() == instance->getSize());
    for(int i = 0; i < extNearestNeighbour.getSolution().size(); i++){
        ASSERT_TRUE(std::find(extNearestNeighbour.getSolution().begin(), extNearestNeighbour.getSolution().end(), i) != extNearestNeighbour.getSolution().end());
    }
}

TEST(tabu_search, solve_krandom_invert){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = ProblemFactory::createEuc2DInstance(100,100));
    K_RandomSolver kRandomSolver(instance, 100);
    while(kRandomSolver.step());
    Invert two_opt(instance);
    std::shared_ptr<Neighborhood> n = std::make_shared<Invert>(two_opt);

    TSPInstance::solution s(kRandomSolver.getSolution());
    TabuSearch tabu(instance, s, n);
    while(tabu.step());
    ASSERT_TRUE(tabu.calculateObjectiveFunction() <= kRandomSolver.calculateObjectiveFunction());
}

TEST(tabu_search, solve_twoopt_invert){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = ProblemFactory::createEuc2DInstance(100,100));
    TwoOptSolver solver(instance);
    while(solver.step());
    Invert two_opt(instance);
    std::shared_ptr<Neighborhood> n = std::make_shared<Invert>(two_opt);

    TSPInstance::solution s(solver.getSolution());
    TabuSearch tabu(instance, s, n);
    while(tabu.step());
    ASSERT_TRUE(tabu.calculateObjectiveFunction() <= solver.calculateObjectiveFunction());
}

TEST(neighborhood, swap){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalMatrix));
    TSPInstance::solution s(instance->getSize());
    std::iota(s.begin(), s.end(), 0);
    Swap swap(instance);

    //testowanie zwykłego ruchu
    std::vector<int> move(2);
    move[0] = 1, move[1] = 4;
    int res = swap.getObjectiveFunction(s, move);
    TSPInstance::solution newSolution = swap.getNewSolution(s, move);
    ASSERT_TRUE(newSolution[1] == 4 && newSolution[4] == 1);
    int res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

    //testowanie ruchu obok siebie wychodzącego poza zakres wektora
    move[0] = 0, move[1] = instance->getSize() - 1;
    res = swap.getObjectiveFunction(s, move);
    newSolution = swap.getNewSolution(s, move);
    ASSERT_TRUE(newSolution[0] == instance->getSize() - 1 && newSolution[instance->getSize() - 1] == 0);
    res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

    move[1] = 1, move[0] = 2;
    res = swap.getObjectiveFunction(s, move);
    newSolution = swap.getNewSolution(s, move);
    ASSERT_TRUE(newSolution[1] == 2 && newSolution[2] == 1);
    res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);
}

TEST(neighborhood, invert){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalEuclidian));
    TSPInstance::solution s(instance->getSize());
    std::iota(s.begin(), s.end(), 0);
    Invert swap(instance);
    std::vector<int> move(2);
    move[0] = 1, move[1] = 4;
    int res = swap.getObjectiveFunction(s, move);
    TSPInstance::solution newSolution = swap.getNewSolution(s, move);
    int res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);
}

TEST(neighborhood, insert){
    std::shared_ptr<TSPInstance> instance;
    ASSERT_NO_THROW(instance = Parser::getInstance(pathToOriginalMatrix));
    TSPInstance::solution s(instance->getSize());
    std::iota(s.begin(), s.end(), 0);
    Insert insert(instance);
    std::vector<int> move(2);

    //testowanie zwykłego ruchu
    move[0] = 1, move[1] = 4;
    int res = insert.getObjectiveFunction(s, move);
    TSPInstance::solution newSolution = insert.getNewSolution(s, move);
    ASSERT_TRUE(newSolution[1] == 2 && newSolution[2] == 3 && newSolution[3] == 1);
    int res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

    //testowanie ruchu na odwrót
    move[0] = 4, move[1] = 1;
    res = insert.getObjectiveFunction(s, move);
    newSolution = insert.getNewSolution(s, move);
    ASSERT_TRUE(newSolution[1] == 4 && newSolution[2] == 1 && newSolution[3] == 2 && newSolution[4] == 3);
    res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

    //testowanie ruchu obok siebie
    move[0] = instance->getSize() - 1, move[1] = 0;
    res = insert.getObjectiveFunction(s, move);
    newSolution = insert.getNewSolution(s, move);
    for(int i = 0; i < instance->getSize(); i++)
        ASSERT_TRUE(newSolution[i] == s[(instance->getSize() + i-1) % instance->getSize()]);
    res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

    //testowanie ruchu obok siebie, który nie zmienia wektora
    move[0] = 2, move[1] = 2;
    res = insert.getObjectiveFunction(s, move);
    newSolution = insert.getNewSolution(s, move);
    ASSERT_TRUE(newSolution == s);
    res_with_objective_function = Solver::calculateObjectiveFunction(newSolution, instance);
    ASSERT_TRUE(res_with_objective_function == res);

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
