#ifndef SKP_LOG_H
#define SKP_LOG_H

#include <string>

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


void write_log(const char *file, uint16_t line, const char *function, const char * format, ...);
void write_log(const char *file, uint16_t line, const char *function, LogFile *logFile, const char * format, ...);


#define log_print(msg, ...) write_log(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)

#endif // SKP_LOG_H
