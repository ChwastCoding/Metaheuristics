#include <gtest/gtest.h>
#include "../src/tsp_data/Euc2DInstance.h"
#include "../src/tsp_data/MatrixInstance.h"
#include "../src/tsp_data/Parser.h"
#include "../src/util.h"
#include "../src/tsp_data/ProblemFactory.h"

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

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
