#include "gtest/gtest.h"
#include "src/lua/skp_lua.h"

int main(int argc, char *argv[])
{

    testing::AddGlobalTestEnvironment(new LuaEnvironment());
    testing::GTEST_FLAG(output) = "xml:gtest.xml";
    //testing::GTEST_FLAG(filter) = "Test";
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
