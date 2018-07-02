#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>
#include <string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include <unistd.h>
#include <vector>

#define uint16 unsigned int

class LogFile
{
public:
    LogFile(const std::string &path);
    ~LogFile();
    void openLog(const std::string &path);
    void writeLog(const char *str);
    void writeLog(const std::string &str);
    void clear();
    void closeLog();
private:
    int m_fd;
};


void write_log(const char *file, uint16 line, const char *function, const char * format, ...);
void write_log(const char *file, uint16 line, const char *function, LogFile *logFile, const char * format, ...);


#define log_print(msg, ...) write_log(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)

#define assert_ret(ret) do {assert(ret);} while(false)
#define check_ret(ret) do {if(!(ret)) log_print("%s \n", #ret);} while(false)
#define func_run(func) do {log_print(" ========== start %s ========== ", #func); func; log_print(" ========== end %s ========== ", #func);} while(false)



#endif // COMMON_H
