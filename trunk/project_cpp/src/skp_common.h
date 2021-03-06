#ifndef SKP_COMMON_H
#define SKP_COMMON_H

#include "skp_log.h"



class CStartInfo
{
public:
    CStartInfo(const char *info, const char *line) : m_info(info), m_line(line)
    {
        log_print("                     start : %s", m_info);
    }

    ~CStartInfo()
    {
        log_print("                     return  : %s %s", m_info, m_line);
    }
    const char *m_info;
    const char *m_line;
};

#define START_INFO(info) CStartInfo _info_tmp_##info(#info, "");
#define START_INFO_TOP(info) CStartInfo _info_tmp_##info(#info, "\n\n\n\n");

#define SKP_TEST(x, y) TEST(x, y)
#define SKP_TEST_F(x, y) TEST_F(x, y)
#define SKP_TEST_ONECE(x, y) TEST(x, y)
#define SKP_TEST_ONECE_F(x, y) TEST_F(x, y)
#define SKP_TEST_ALL

#ifndef SKP_TEST_ALL
#undef SKP_TEST
#undef SKP_TEST_F

#define SKP_TEST(x, y) void x##y()
#define SKP_TEST_F(x, y) class x##y : public x {public: void y();}; void x##y::y()
#endif

#define cmd_error -1
#define cmd_success 0

#define check_false(condition) do { if(condition) { log_print("error : %s", #condition); return cmd_error;} }while(false)
#define check_true(condition) do { if(!(condition)) { log_print("error : %s", #condition); return cmd_error;} }while(false)
#define check_error(condition, msg, ...) do { if(condition) { log_print(msg, ##__VA_ARGS__); return cmd_error;} }while(false)
#define check_success(condition) do { if(condition) return cmd_success;}while(false)
#define check_func(condition) check_false(condition)

const char *binaryToStr(char *buffer, int bufferSize, const char *msg, int msgSize);

#endif // SKP_COMMON_H
