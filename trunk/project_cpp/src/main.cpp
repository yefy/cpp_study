#include "gtest/gtest.h"
#include "src/lua/skp_lua_test.h"
#include <gmock/gmock.h>

int main(int argc, char *argv[])
{

//    FILE *r_fp = NULL;
//    r_fp = fopen("r.txt", "rb");

//    int size = 0;

//    char buffer[1024] = "";

//    memset(buffer, 0x00, sizeof(buffer));
//    size = fread(buffer, 1, 3, r_fp);
//    printf("size = %d, buffer = [%s] \n", size, buffer);

//    memset(buffer, 0x00, sizeof(buffer));
//    size = fread(buffer, 1, 3, r_fp);
//    printf("size = %d, buffer = [%s] \n", size, buffer);

//    memset(buffer, 0x00, sizeof(buffer));
//    size = fread(buffer, 1, 3, r_fp);
//    printf("size = %d, buffer = [%s] \n", size, buffer);

//    memset(buffer, 0x00, sizeof(buffer));
//    size = fread(buffer, 1, 3, r_fp);
//    printf("size = %d, buffer = [%s] \n", size, buffer);


//    fclose(r_fp);
//    r_fp = NULL;


//    return 0;

    testing::AddGlobalTestEnvironment(new LuaEnvironment());
    testing::GTEST_FLAG(output) = "xml:gtest.xml";
    //testing::GTEST_FLAG(filter) = "Test";
    //testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
