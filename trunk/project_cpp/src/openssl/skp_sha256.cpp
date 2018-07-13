#include "skp_sha256.h"
#include "gtest/gtest.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include <openssl/ssl.h>

std::string sha256(const std::string str)
{
    char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::string newString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf,"%02x",hash[i]);
        newString = newString + buf;
    }
    return newString;
}

SKP_TEST(openssl, openssl_sha256)
{
    START_INFO_TOP(openssl_sha256);
    std::string str = "Hello World";
    log_print("%s(sha256) = %s \n", str.c_str(), sha256(str).c_str());
}

