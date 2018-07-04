#include "skp_log.h"
#include <stdarg.h>
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

LogFile g_logfile("test.log");

LogFile::LogFile(const std::string &path) :
    m_fd(-1)
{
    openLog(path);
}

LogFile::~LogFile()
{
    //clear();
    closeLog();
}

void LogFile::openLog(const std::string &path)
{
    //m_fd = ::open(path.c_str(), O_APPEND|O_WRONLY|O_CREAT, S_IRWXU);
    m_fd = ::open(path.c_str(), O_WRONLY|O_TRUNC|O_CREAT, S_IRWXU);
    assert(m_fd > 0);

//    /* 重定向 */
//    assert(dup2(m_fd, STDOUT_FILENO) != -1);
//    assert(dup2(m_fd, STDERR_FILENO) != -1);
}

void LogFile::writeLog(const char *str)
{
    ::write(m_fd, str, strlen(str));
}

void LogFile::writeLog(const std::string &str)
{
    ::write(m_fd, str.c_str(), str.size());
}

void LogFile::clear()
{
    /* 清空文件 */
    ftruncate(m_fd,0);

    /* 重新设置文件偏移量 */
    lseek(m_fd,0,SEEK_SET);
}

void LogFile::closeLog()
{
    ::close(m_fd);
}

void do_write_log(const char *file, uint16_t line, const char *function, LogFile *logFile, const char *logmsg)
{
    char fullLogMsg[4096] = "";
    //snprintf(fullLogMsg, sizeof(fullLogMsg), "%s:%d:%s|%s \n", file, line, function, logmsg);

    const char *p = file + strlen(file);
    while((--p) >= file)
    {
        if(*p == '/' || *p == '\\')
            break;
    }
    ++p;

    snprintf(fullLogMsg, sizeof(fullLogMsg), "%s:%d:%s|%s \n", p, line, function, logmsg);
    //printf(fullLogMsg);
    logFile->writeLog(fullLogMsg);
}


void write_log(const char *file, uint16_t line, const char *function, const char * format, ...)
{
    char logmsg[4096] = "";

    va_list args;
    va_start(args, format);

#ifdef _WIN32
    _vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#else
    vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#endif

    va_end(args);


    do_write_log(file, line, function, &g_logfile, logmsg);
}


void write_log(const char *file, uint16_t line, const char *function, LogFile *logFile, const char * format, ...)
{
    char logmsg[4096] = "";

    va_list args;
    va_start(args, format);

#ifdef _WIN32
    _vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#else
    vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#endif

    va_end(args);


    do_write_log(file, line, function, logFile, logmsg);
}
