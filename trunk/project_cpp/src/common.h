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
#include <functional>

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

const char *getBinary(char *buffer, int bufferSize, const char *msg, int msgSize);


#define assert_null(ret) do {assert((ret) != 0);} while(false)
#define assert_func(ret) do {assert((ret) == 0);} while(false)
#define check_func(ret) do {if((ret) != 0) log_print("error %s \n", #ret);} while(false)


#endif // COMMON_H
