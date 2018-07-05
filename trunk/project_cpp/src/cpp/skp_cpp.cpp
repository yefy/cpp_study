#include "skp_cpp.h"
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
