#include "skp_cpp_test.h"
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



struct AAA
{
    int a;
};

SKP_TEST(cpp, cpp_ptr)
{
    START_INFO_TOP(cpp_ptr);

    AAA *aaa = (AAA *)0x10000;

    ASSERT_EQ(int64_t(aaa + 0x10) ,  0x10000 + sizeof(AAA) * 0x10);
    ASSERT_EQ(int64_t((char *)aaa + 0x10) ,  0x10000  + 0x10);
    ASSERT_EQ(int64_t((int *)aaa + 0x10) ,  0x10000 + sizeof(int) * 0x10);
}


enum _arg_ref
{
    arg_lvalue_ref = 0,
    arg_rvalue_ref = 1,
    arg_const_lvalue_ref = 2,
    arg_const_rvalue_ref = 3,
};

char *_arg_ref_info[] =
{
    "lvalue ref",
    "rvalue ref",
    "const lvalue ref",
    "const rvalue ref"
};


//======================================
int32_t fun(int &x)
{
    log_print(_arg_ref_info[arg_lvalue_ref]);
    return arg_lvalue_ref;
}

int32_t fun(int &&x)
{
    log_print(_arg_ref_info[arg_rvalue_ref]);
    return arg_rvalue_ref;
}

int32_t fun(const int &x)
{
    log_print(_arg_ref_info[arg_const_lvalue_ref]);
    return arg_const_lvalue_ref;
}
int32_t fun(const int &&x)
{
    log_print(_arg_ref_info[arg_const_rvalue_ref]);
    return arg_const_rvalue_ref;
}
//========================================
template<typename T>
int32_t fun_t(T &x)
{
    log_print(_arg_ref_info[arg_lvalue_ref]);
    return arg_lvalue_ref;
}

template<typename T>
int32_t fun_t(T &&x)
{
   log_print(_arg_ref_info[arg_rvalue_ref]);
   return arg_rvalue_ref;
}

template<typename T>
int32_t fun_t(const T &x)
{
    log_print(_arg_ref_info[arg_const_lvalue_ref]);
    return arg_const_lvalue_ref;
}

template<typename T>
int32_t fun_t(const T &&x)
{
    log_print(_arg_ref_info[arg_const_rvalue_ref]);
    return arg_const_rvalue_ref;
}
//========================================

template<typename T>
int32_t fun_test(T &&t)
{
    return fun(t);
}

template<typename T>
int32_t fun_forward_test(T &&t)
{
    return fun(std::forward<T>(t));
}

//========================================
template<typename T>
int32_t fun_t_test(T &&t)
{
    return fun_t(t);
}

template<typename T>
int32_t fun_t_forward_test(T &&t)
{
    return fun_t(std::forward<T>(t));
}
//========================================

SKP_TEST(cpp, cpp_fun_ref)
{
    START_INFO_TOP(cpp_fun_ref);

    int n = 1;
    const int const_n = 1;
    ASSERT_EQ(fun_test(1), arg_lvalue_ref);
    ASSERT_EQ(fun_test(n), arg_lvalue_ref);
    ASSERT_EQ(fun_test(const_n), arg_const_lvalue_ref);
    ASSERT_EQ(fun_test(std::move(n)), arg_lvalue_ref);
    ASSERT_EQ(fun_test(std::move(const_n)), arg_const_lvalue_ref);

    ASSERT_EQ(fun_forward_test(1), arg_rvalue_ref);
    ASSERT_EQ(fun_forward_test(n), arg_lvalue_ref);
    ASSERT_EQ(fun_forward_test(const_n), arg_const_lvalue_ref);
    ASSERT_EQ(fun_forward_test(std::move(n)), arg_rvalue_ref);
    ASSERT_EQ(fun_forward_test(std::move(const_n)), arg_const_rvalue_ref);

    ASSERT_EQ(fun_t_test(1), arg_lvalue_ref);
    ASSERT_EQ(fun_t_test(n), arg_lvalue_ref);
    ASSERT_EQ(fun_t_test(const_n), arg_const_lvalue_ref);
    ASSERT_EQ(fun_t_test(std::move(n)), arg_lvalue_ref);
    ASSERT_EQ(fun_t_test(std::move(const_n)), arg_const_lvalue_ref);

    ASSERT_EQ(fun_t_forward_test(1), arg_rvalue_ref);
    ASSERT_EQ(fun_t_forward_test(n), arg_lvalue_ref);
    ASSERT_EQ(fun_t_forward_test(const_n), arg_const_lvalue_ref);
    ASSERT_EQ(fun_t_forward_test(std::move(n)), arg_rvalue_ref);
    ASSERT_EQ(fun_t_forward_test(std::move(const_n)), arg_const_rvalue_ref);

    int &&a1 = std::move(1);
    const int &&a2 = std::move(1);
    int &&b1 = std::move(n);
    const int &&b2 = std::move(n);
    //int &&c1 = std::move(const_n); //error
    const int &&c2 = std::move(const_n);
}


#include "project_cpp_lib_test.h"

SKP_TEST(cpp, cpp_lib)
{
    START_INFO_TOP(cpp_lib);

    Project_cpp_lib_test cpplib;
    (void)cpplib;
}

SKP_TEST(cpp, cpp_zero)
{
    START_INFO_TOP(cpp_zero);

    const char *str = "\0";
    char c = '\0';
    int n = 0;
    ASSERT_EQ((int)str[0], (int)c);
    ASSERT_EQ((int)str[0], n);
    ASSERT_EQ((int)c, n);

    char buffer1[] = "123\0";
    ASSERT_EQ(5, sizeof(buffer1));

    char buffer2[] = "\0";
    ASSERT_EQ(2, sizeof(buffer2));

    char buffer3[] = {'1'};
    ASSERT_EQ(1, sizeof(buffer3));
}




#include <string>
#include <cstdlib>
#include <gmock/gmock.h>

class Bar
{
public:
    int num;
};

class FooInterface {
public:
        virtual ~FooInterface() {}

public:
        virtual std::string getArbitraryString() = 0;
        virtual void setValue(std::string& value) = 0;
        virtual void setDoubleValues(int x, int y) = 0;
        virtual int get(Bar &bar) = 0;
};


class MockFoo: public FooInterface {
public:
        MOCK_METHOD0(getArbitraryString, std::string());
        MOCK_METHOD1(setValue, void(std::string& value));
        MOCK_METHOD2(setDoubleValues, void(int x, int y));
        MOCK_METHOD1(get, int(Bar &bar));
};

using ::testing::Assign;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Field;
using ::testing::Return;

SKP_TEST(cpp, cpp_gmock)
{
    START_INFO_TOP(cpp_gmock);

    std::string value = "Hello World!";
    MockFoo mockFoo;

    EXPECT_CALL(mockFoo, setValue(testing::_)).Times(2);
    mockFoo.setValue(value);
    mockFoo.setValue(value);


    EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));
    mockFoo.setDoubleValues(1, 2);


    EXPECT_CALL(mockFoo, getArbitraryString()).Times(2).
            WillOnce(Return(value)).WillOnce(Return(""));
    //std::string returnValue = mockFoo.getArbitraryString();

    ASSERT_STREQ(value.c_str(), mockFoo.getArbitraryString().c_str());
    ASSERT_STREQ("", mockFoo.getArbitraryString().c_str());

    Bar bar;
    bar.num = 1;
    EXPECT_CALL(mockFoo, get(Field(&Bar::num, Ge(0)))).Times(1);
    mockFoo.get(bar);
}
