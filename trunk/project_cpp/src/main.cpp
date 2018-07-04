#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    testing::GTEST_FLAG(output) = "xml:gtest.xml";
    //testing::GTEST_FLAG(filter) = "Test";
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
