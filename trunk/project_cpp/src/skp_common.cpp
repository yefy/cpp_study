#include "skp_common.h"
#include <string.h>

const char *binaryToStr(char *buffer, int bufferSize, const char *msg, int msgSize)
{
    int size = bufferSize;
    if(size <= msgSize)
    {
        --size;
    }
    else
    {
        size = msgSize;
    }
    memcpy(buffer, msg, size);
    for(int i = 0; i < size; ++i)
    {
        if('\0' == buffer[i])\
        {
            buffer[i] = '~';\
        }
    }
    buffer[size] = '\0';
    return buffer;
}
