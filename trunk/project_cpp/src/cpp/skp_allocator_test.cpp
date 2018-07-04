#include "skp_allocator_test.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include "gtest/gtest.h"

#include <iostream>
#include <list>
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <map>
#include <set>
#include <memory>

#include "skp_allocator.h"

SKP_TEST(cpp, cpp_std_allocator)
{
    START_INFO_TOP(cpp_std_allocator);

    std::list<int, std::allocator<int>> alloc_list;
    alloc_list.push_back(1);
    alloc_list.push_back(2);
}

SKP_TEST(cpp, cpp_skp_allocator)
{
    START_INFO_TOP(cpp_skp_allocator);

    std::list<int, skp::allocator<int>> alloc_list;
    alloc_list.push_back(1);
    alloc_list.push_back(2);
}

SKP_TEST(cpp, cpp_skp_make_data1)
{
    START_INFO_TOP(cpp_skp_make_data1);

    std::list<int> *make_list = NULL;
    ASSERT_TRUE(make_list = skp::make_data<std::list<int>>());
}

class CMakeDataTest
{
public:
    CMakeDataTest() : m_arg1(0), m_arg2(0)
    {
        printf("CMakeDataTest() \n");
    }


    CMakeDataTest(int &&arg1) : m_arg1(arg1), m_arg2(0)
    {
        printf("CMakeDataTest(int &&arg1) : arg = %d \n", arg1);
    }

    CMakeDataTest(int &&arg1, int &&arg2) : m_arg1(arg1), m_arg2(arg2)
    {
        printf("CMakeDataTest(int &&arg1, int &&arg2) : arg1 = %d, arg2 = %d \n", arg1, arg2);
    }

    int m_arg1;
    int m_arg2;
};

SKP_TEST(cpp, cpp_skp_make_data2)
{
    START_INFO_TOP(cpp_skp_make_data2);

    CMakeDataTest *data = NULL;
    ASSERT_TRUE(data = skp::make_data<CMakeDataTest>());

    ASSERT_EQ(data->m_arg1, 0);
    ASSERT_EQ(data->m_arg2, 0);
}

SKP_TEST(cpp, cpp_skp_make_data3)
{
    START_INFO_TOP(cpp_skp_make_data3);

    CMakeDataTest *data = NULL;
    ASSERT_TRUE(data = skp::make_data<CMakeDataTest>(1));

    ASSERT_EQ(data->m_arg1, 1);
    ASSERT_EQ(data->m_arg2, 0);
}

SKP_TEST(cpp, cpp_skp_make_data4)
{
    START_INFO_TOP(cpp_skp_make_data4);

    CMakeDataTest *data = NULL;
    ASSERT_TRUE(data = skp::make_data<CMakeDataTest>(1, 2));

    ASSERT_EQ(data->m_arg1, 1);
    ASSERT_EQ(data->m_arg2, 2);
}


SKP_TEST(cpp, cpp_skp_make_unique1)
{
    START_INFO_TOP(cpp_skp_make_unique1);

    std::unique_ptr<CMakeDataTest> data;
    data = skp::make_unique<CMakeDataTest>();

    ASSERT_EQ(data->m_arg1, 0);
    ASSERT_EQ(data->m_arg2, 0);
}

SKP_TEST(cpp, cpp_skp_make_unique2)
{
    START_INFO_TOP(cpp_skp_make_unique2);

    std::unique_ptr<CMakeDataTest> data;
    data = skp::make_unique<CMakeDataTest>(1);

    ASSERT_EQ(data->m_arg1, 1);
    ASSERT_EQ(data->m_arg2, 0);
}


SKP_TEST(cpp, cpp_skp_make_unique3)
{
    START_INFO_TOP(cpp_skp_make_unique3);

    std::unique_ptr<CMakeDataTest> data;
    data = skp::make_unique<CMakeDataTest>(1, 2);

    ASSERT_EQ(data->m_arg1, 1);
    ASSERT_EQ(data->m_arg2, 2);
}
