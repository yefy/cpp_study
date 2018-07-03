#include "skp_cpp.h"
#include "src/common.h"
#include "src/common.h"
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



///    struct AAA
///    {
///        int a;
///    };

///    AAA *aaa = (AAA *)0x10000;
////    aaa + 0x10 =  0x10000 + sizeof(AAA) * 0x10;
////    (char *)aaa + 0x10 =  0x10000  + 0x10;
////    (int *)aaa + 0x10 =  0x10000 + sizeof(int) * 0x10;

//     std::cout << "  AAA  " << (int)(aaa + 0x10) << "  AAA  " << (int)(0x10000 + sizeof(AAA) * 0x10) << std::endl;
//     std::cout << "  AAA  " << (int)((char *)aaa + 0x10)<< "  AAA  " <<  (int)(0x10000  + 0x10) << std::endl;
//     std::cout << "  AAA  " << (int)((int *)aaa + 0x10)<< "  AAA  "<< (int)(0x10000 + sizeof(int) * 0x10) << std::endl;


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
void fun_1(T &x)
{
    log_print("lvalue ref");
    x = 20;
}

template<typename T>
void fun_1(T &&x)
{
    log_print("rvalue ref");
    x = 21;
}

template<typename T>
void fun_1(const T &x)
{
    log_print("const lvalue ref");
}

template<typename T>
void fun_1(const T &&x)
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
void fun_test_1(T &&t)
{
    log_print("in t = %d", t);
    fun_1(t);
    log_print("out t = %d", t);
}

template<typename T>
void fun_forward_test_1(T &&t)
{
    log_print("in t = %d", t);
    fun_1(std::forward<T>(t));
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
    fun_test_1(1);
    fun_forward_test_1(1);

    int n = 2;
    fun_test(n);
    fun_forward_test(n);
    fun_test_1(n);
    fun_forward_test_1(n);

    fun_test(std::move(n));
    fun_forward_test(std::move(n));
    fun_test_1(std::move(n));
    fun_forward_test_1(std::move(n));

    const int m = 3;
    fun_test(m);
    fun_forward_test(m);
    fun_test_1(m);
    fun_forward_test_1(m);

    fun_test(std::move(m));
    fun_forward_test(std::move(m));
    fun_test_1(std::move(m));
    fun_forward_test_1(std::move(m));

    int &&a = std::move(1);
    int &&b = std::move(n);
    const int &&c = std::move(m);
}

#include "project_cpp_lib_test.h"

TEST(cpp, lib)
{
    Project_cpp_lib_test cpplib;
    (void)cpplib;
}


#include "skp_allocator.h"

TEST(cpp, allocator)
{
    std::list<int, std::allocator<int>> alloc_list;
    alloc_list.push_back(1);
    alloc_list.push_back(2);
}

TEST(cpp, allocator_make)
{
    std::list<int> *make_list = NULL;
    assert_null(make_list = skp::make_data<std::list<int>>());
}
