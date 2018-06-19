#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>

#define uint16 unsigned int


void write_log(const char *file, uint16 line, const char *function, const char * format, ...);


#define log_print(msg, ...) write_log(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)

#define assert_ret(ret) do {assert(ret);} while(false)
#define check_ret(ret) do {if(!(ret)) log_print("%s \n", #ret);} while(false)
#define func_run(func) do {log_print("*****%s start*****", #func); func; log_print("*****%s end*****", #func);} while(false)



#endif // COMMON_H
