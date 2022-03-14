#include <gtest/gtest.h>
#include "../src/tsp_data/Euc2DInstance.h"
#include "../src/tsp_data/Parser.h"
#include "../src/util.h"

typedef std::pair<int, int> intPair;
const std::string pathToOriginal = "../../tests/ch130.tsp";
const std::string pathToCopy = "ch130_copy.tsp";

TEST(setup_test, test_1) {
    std::string s = "lorem ipsum";
    ASSERT_EQ(s, s.substr(0, s.find(':')));
    Euc2DInstance e(10);
    ASSERT_TRUE(true);
}

TEST(util, test_trim_whitespace) {
    std::string s = "lorem ipsum   ", s2 = "test";
    ASSERT_EQ(util::trimWhitespace(s), "lorem ipsum");
    ASSERT_EQ(s2, util::trimWhitespace(s2));
}

TEST(parser_test, loading) {
    auto instance = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginal));
    ASSERT_EQ(instance->getSize(), 130);
    ASSERT_EQ(instance->getName(), "ch130");
    ASSERT_EQ(instance->getCoords(0), intPair(335, 162));
}

TEST(parser_test, saving) {
    auto instance = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginal));
    ASSERT_NO_THROW(Parser::saveInstance(instance, pathToCopy));

    auto instance_copy = std::dynamic_pointer_cast<Euc2DInstance>(Parser::getInstance(pathToOriginal));
    ASSERT_EQ(instance->getSize(), instance_copy->getSize());
    ASSERT_EQ(instance->getName(), instance_copy->getName());
    for (int i = 0; i < instance->getSize(); i++ ) {
        ASSERT_EQ(instance->getCoords(i), instance_copy->getCoords(i));
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
