#ifndef PROJECT_CPP_LIB_TEST_H
#define PROJECT_CPP_LIB_TEST_H

//#define _LIB_EXPORT_

//#ifdef _LIB_EXPORT_
//#define LIB_API __declspec(dllexport)
//#else
//#define LIB_API __declspec(dllimport)
//#endif

#define LIB_API

class LIB_API Project_cpp_lib_test
{

public:
    Project_cpp_lib_test();
};

#endif // PROJECT_CPP_LIB_TEST_H
