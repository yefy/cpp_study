#include "skp_cpp.h"
#include "src/common.h"


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
    std::cout << "lvalue ref" << std::endl;
    x = 10;
}

void fun(int &&x)
{
    std::cout << "rvalue ref" << std::endl;
    x = 11;
}

void fun(const int &x)
{
    std::cout << "const lvalue ref" << std::endl;
}
void fun(const int &&x)
{
    std::cout << "const rvalue ref" << std::endl;
}

template<typename T>
void fun_1(T &x)
{
    std::cout << "lvalue ref" << std::endl;
    x = 20;
}

template<typename T>
void fun_1(T &&x)
{
    std::cout << "rvalue ref" << std::endl;
    x = 21;
}

template<typename T>
void fun_1(const T &x)
{
    std::cout << "const lvalue ref" << std::endl;
}

template<typename T>
void fun_1(const T &&x)
{
    std::cout << "const rvalue ref" << std::endl;
}


template<typename T>
void fun_test(T &&t)
{
    log_print("in t = %d", t);
    func_run(fun(t));
    log_print("out t = %d", t);
}

template<typename T>
void fun_forward_test(T &&t)
{
    log_print("in t = %d", t);
    func_run(fun(std::forward<T>(t)));
    log_print("out t = %d", t);
}

template<typename T>
void fun_test_1(T &&t)
{
    log_print("in t = %d", t);
    func_run(fun_1(t));
    log_print("out t = %d", t);
}

template<typename T>
void fun_forward_test_1(T &&t)
{
    log_print("in t = %d", t);
    func_run(fun_1(std::forward<T>(t)));
    log_print("out t = %d", t);
}

int && gaaa = 1;
int && gfaaa()
{
    return static_cast<int &&>(gaaa);
}

void move_forward_test()
{
    func_run(fun_test(1));
    func_run(fun_forward_test(1));
    func_run(fun_test_1(1));
    func_run(fun_forward_test_1(1));

    int n = 2;
    func_run(fun_test(n));
    func_run(fun_forward_test(n));
    func_run(fun_test_1(n));
    func_run(fun_forward_test_1(n));

    func_run(fun_test(std::move(n)));
    func_run(fun_forward_test(std::move(n)));
    func_run(fun_test_1(std::move(n)));
    func_run(fun_forward_test_1(std::move(n)));

    const int m = 3;
    func_run(fun_test(m));
    func_run(fun_forward_test(m));
    func_run(fun_test_1(m));
    func_run(fun_forward_test_1(m));

    func_run(fun_test(std::move(m)));
    func_run(fun_forward_test(std::move(m)));
    func_run(fun_test_1(std::move(m)));
    func_run(fun_forward_test_1(std::move(m)));

    int &&a = std::move(1);
    int &&b = std::move(n);
    const int &&c = std::move(m);
}

#include "project_cpp_lib_test.h"

void cpp_lib_test()
{
    Project_cpp_lib_test cpplib;
    (void)cpplib;
}


#include "skp_allocator.h"

void allocator_test()
{
    std::list<int, std::allocator<int>> alloc_list;
    alloc_list.push_back(1);
    alloc_list.push_back(2);
}

void allocator_make_test()
{
    std::list<int> *make_list = NULL;
    assert_ret((make_list = skp::make_data<std::list<int>>()) != NULL);
}

void cpp_test()
{
    func_run(cpp_lib_test());
    func_run(allocator_test());
    func_run(allocator_make_test());
    func_run(move_forward_test());
}
