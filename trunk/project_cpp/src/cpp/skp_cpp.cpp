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




void fun(int &x)
{
    log_print("lvalue ref");
    x = 10;
}

void fun(int &&x)
{
    log_print("rvalue ref");
    x = 11;
}

void fun(const int &x)
{
    log_print("const lvalue ref");
}
void fun(const int &&x)
{
    log_print("const rvalue ref");
}

template<typename T>
void fun_t(T &x)
{
    log_print("lvalue ref");
    x = 20;
}

template<typename T>
void fun_t(T &&x)
{
    log_print("rvalue ref");
    x = 21;
}

template<typename T>
void fun_t(const T &x)
{
    log_print("const lvalue ref");
}

template<typename T>
void fun_t(const T &&x)
{
    log_print("const rvalue ref");
}


template<typename T>
void fun_test(T &&t)
{
    log_print("in t = %d", t);
    fun(t);
    log_print("out t = %d", t);
}

template<typename T>
void fun_forward_test(T &&t)
{
    log_print("in t = %d", t);
    fun(std::forward<T>(t));
    log_print("out t = %d", t);
}

template<typename T>
void fun_t_test(T &&t)
{
    log_print("in t = %d", t);
    fun_t(t);
    log_print("out t = %d", t);
}

template<typename T>
void fun_t_forward_test(T &&t)
{
    log_print("in t = %d", t);
    fun_t(std::forward<T>(t));
    log_print("out t = %d", t);
}

int && gaaa = 1;
int && gfaaa()
{
    return static_cast<int &&>(gaaa);
}

void move_forward_test()
{
    fun_test(1);
    fun_forward_test(1);
    fun_t_test(1);
    fun_t_forward_test(1);

    int n = 2;
    fun_test(n);
    fun_forward_test(n);
    fun_t_test(n);
    fun_t_forward_test(n);

    fun_test(std::move(n));
    fun_forward_test(std::move(n));
    fun_t_test(std::move(n));
    fun_t_forward_test(std::move(n));

    const int m = 3;
    fun_test(m);
    fun_forward_test(m);
    fun_t_test(m);
    fun_t_forward_test(m);

    fun_test(std::move(m));
    fun_forward_test(std::move(m));
    fun_t_test(std::move(m));
    fun_t_forward_test(std::move(m));

    int &&a = std::move(1);
    int &&b = std::move(n);
    const int &&c = std::move(m);
}


#include "project_cpp_lib_test.h"

SKP_TEST(cpp, cpp_lib)
{
    START_INFO_TOP(cpp_lib);

    Project_cpp_lib_test cpplib;
    (void)cpplib;
}
