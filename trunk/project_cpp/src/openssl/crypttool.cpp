#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypt.h"
#include "gtest/gtest.h"
#include "src/skp_common.h"
#include "src/skp_log.h"

/*
using namespace std;
//using namespace lspublic::library::util;
void cryptHelp()
{
    printf("用法:\n");
    printf("用法1：命令后直接跟16位要进行加密的公钥，结果写入配置文件$HOME/cfg/aes.key\n");
    printf("用法2：命令后跟要加密的明文及64位已加密的公钥(即用法1中生成的密文),顺序不可打乱\n");
}

SKP_TEST(openssl, openssl_tool)
{
    int32_t argc = 2;
    char*argv[] = {"openssl_tool", "123456"};

    CCrypt cCrypt;
    ASSERT_EQ(cCrypt.loadAesInKey(), 0);

    if (2 == argc)
    {
        if (strncmp(argv[1], "-h", sizeof(argv[1])) == 0)
        {
            cryptHelp();
        }
        else
        {
            printf("加密前公钥(16位):[%s]\n", argv[1]);
            char szcryptAesKey[129]="";
            if(-1 == cCrypt.encryptEcbByInKey((unsigned char *) szcryptAesKey, sizeof(szcryptAesKey), (unsigned char *)argv[1], 16))
            {
                printf("加密公钥失败\n");
            }
            printf("请将该加密后的公钥写入相应的配置文件中($HOME/cfg/aes.key)\n");
            printf("加密后公钥:[\n%s\n]\n", szcryptAesKey);
        }   
    }	
    else if (3 == argc)
    {
        printf("加密前:[%s],加密后公钥(64位):[%s]\n", argv[1], argv[2]);
        char szDestStr[129]="";
        if (64 == strlen(argv[2]))
        {
            if (-1 == cCrypt.encryptECB((unsigned char*)szDestStr, sizeof(szDestStr), (unsigned char*)argv[2], (unsigned char*)argv[1], strlen(argv[1])))
            {
                printf("加密[%s]失败\n", argv[1]);
            }     
        }
        else
        {
            printf("请检查输入的加密公钥[%s]是否64位\n", argv[2]);
        }
        
        printf("加密后:[%s]\n", szDestStr);
        
//        char szdeCrypt[129] = "";
//        if (-1 == cCrypt.decryptECB((unsigned char*)szdeCrypt, sizeof(szdeCrypt), (unsigned char*)argv[2], (unsigned char*)szDestStr, strlen(szDestStr)))
//        {
//            return -1;
//        }
//        printf("解密前:[%s],解密后:[%s]\n",szDestStr, szdeCrypt);
    }
    else if (4 == argc)
    {
        if (strncmp(argv[1], "-r", sizeof(argv[1])) == 0)
        {
            char szDestStr[129]="";
            if (64 == strlen(argv[2]))
            {
                if (-1 == cCrypt.decryptECB((unsigned char*)szDestStr, sizeof(szDestStr), (unsigned char*)argv[3], (unsigned char*)argv[2], strlen(argv[3])))
                {
                    printf("解密[%s]失败\n", argv[2]);
                }     
            }
            else
            {
                printf("请检查输入的解密公钥[%s]是否64位\n", argv[3]);
            }
            printf("%s\n", szDestStr);
        }
    }
    else
    {
        cryptHelp();
    }

}




void openssl_tool(int32_t argc, char*argv[], std::string &str)
{
    CCrypt cCrypt;
    if(cCrypt.setAesKey("1234567891234567") != 0)
    {
        printf("cCrypt.setAesKey error \n");
    }
    //cCrypt.setInitVectorKey("1234567891234567");
    //ASSERT_EQ(cCrypt.loadAesInKey(), 0);

    if (2 == argc)
    {
        if (strncmp(argv[1], "-h", sizeof(argv[1])) == 0)
        {
            cryptHelp();
        }
        else
        {
            printf("加密前公钥(16位):[%s]\n", argv[1]);
            char szcryptAesKey[129]="";
            if(-1 == cCrypt.encryptEcbByInKey((unsigned char *) szcryptAesKey, sizeof(szcryptAesKey), (unsigned char *)argv[1], 16))
            {
                printf("加密公钥失败\n");
            }
            printf("请将该加密后的公钥写入相应的配置文件中($HOME/cfg/aes.key)\n");
            printf("加密后公钥:[\n%s\n]\n", szcryptAesKey);

            str = std::string(szcryptAesKey);
        }
    }
    else if (3 == argc)
    {
        printf("加密前:[%s],加密后公钥(64位):[%s]\n", argv[1], argv[2]);
        char szDestStr[4096]="";
        if (64 == strlen(argv[2]))
        {
            if (-1 == cCrypt.encryptECB((unsigned char*)szDestStr, sizeof(szDestStr), (unsigned char*)argv[2], (unsigned char*)argv[1], strlen(argv[1])))
            {
                printf("加密[%s]失败\n", argv[1]);
            }
        }
        else
        {
            printf("请检查输入的加密公钥[%s]是否64位\n", argv[2]);
        }

        printf("加密后:[%s]\n", szDestStr);
        str = std::string(szDestStr);

//        char szdeCrypt[129] = "";
//        if (-1 == cCrypt.decryptECB((unsigned char*)szdeCrypt, sizeof(szdeCrypt), (unsigned char*)argv[2], (unsigned char*)szDestStr, strlen(szDestStr)))
//        {
//            return -1;
//        }
//        printf("解密前:[%s],解密后:[%s]\n",szDestStr, szdeCrypt);
    }
    else if (4 == argc)
    {
        if (strncmp(argv[1], "-r", sizeof(argv[1])) == 0)
        {
            char szDestStr[4096]="";
            if (64 == strlen(argv[3]))
            {
                if (-1 == cCrypt.decryptECB((unsigned char*)szDestStr, sizeof(szDestStr), (unsigned char*)argv[3], (unsigned char*)argv[2], strlen(argv[2])))
                {
                    printf("解密[%s]失败\n", argv[2]);
                }
            }
            else
            {
                printf("请检查输入的解密公钥[%s]是否64位\n", argv[3]);
            }
            printf("%s\n", szDestStr);
            str = std::string(szDestStr);
        }
    }
    else
    {
        cryptHelp();
    }

}

SKP_TEST(openssl, openssl_tool2)
{
    std::string key = "1234567891234567";
    std::string encrypt_key = "";
    if(true)
    {
        int32_t argc = 2;
        char*argv[] = {"", const_cast<char *>(key.c_str())};

        openssl_tool(argc, argv, encrypt_key);
        printf("en_key size = %d \n", encrypt_key.size());
        printf("en_key = %s \n", encrypt_key.c_str());
    }

    std::string data(1601, 'A');
    printf("data size = %d \n", data.size());
    printf("data = %s \n", data.c_str());
    std::string encrypt_data = "";
    if(true)
    {
        int32_t argc = 3;
        char*argv[] = {"", const_cast<char *>(data.c_str()), const_cast<char *>(encrypt_key.c_str())};

        openssl_tool(argc, argv, encrypt_data);
        printf("encrypt_data size = %d \n", encrypt_data.size());
        printf("encrypt_data = %s \n", encrypt_data.c_str());
    }

    std::string decrypt_data = "";
    if(true)
    {
        int32_t argc = 4;
        char*argv[] = {"", "-r", const_cast<char *>(encrypt_data.c_str()), const_cast<char *>(encrypt_key.c_str())};

        openssl_tool(argc, argv, decrypt_data);
        printf("decrypt_data size = %d \n", decrypt_data.size());
        printf("decrypt_data = %s \n", decrypt_data.c_str());
    }

    ASSERT_STREQ(data.c_str(), decrypt_data.c_str());
}
*/

int32_t encryptECB(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    if(strlen((char*)pKeyStr) != AES_KEY_SIZE_BYTE)
    {
        printf("key != 16 error \n");
        return -1;
    }

    int32_t size = 0;

    CCrypt cCrypt;
    if(cCrypt.setAesKey("1234567891234567") != 0)
    {
        printf("cCrypt.setAesKey error \n");
        return -1;
    }

    char szcryptAesKey[129]= "";
    if(-1 == (size = cCrypt.encryptEcbByInKey((unsigned char *) szcryptAesKey, sizeof(szcryptAesKey), pKeyStr, AES_KEY_SIZE_BYTE)))
    {
        printf("cCrypt.encryptEcbByInKey error \n");
        return -1;

    }

    printf("cCrypt.encryptEcbByInKey size = %d \n", size);

    if (-1 ==  (size = cCrypt.encryptECB(pCipherText, nCipherTextLen, (unsigned char *)szcryptAesKey, pClearText, nClearTextLen)))
    {
        printf("encryptECB error \n");
        return -1;
    }

    printf("cCrypt.encryptECB size = %d \n", size);

    return 0;

}

int32_t decryptECB(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    if(strlen((char*)pKeyStr) != AES_KEY_SIZE_BYTE)
    {
        printf("key != 16 error \n");
        return -1;
    }

    int32_t size = 0;

    CCrypt cCrypt;
    if(cCrypt.setAesKey("1234567891234567") != 0)
    {
        printf("cCrypt.setAesKey error \n");
        return -1;
    }

    char szcryptAesKey[129]= "";
    if(-1 == (size = cCrypt.encryptEcbByInKey((unsigned char *) szcryptAesKey, sizeof(szcryptAesKey), pKeyStr, AES_KEY_SIZE_BYTE)))
    {
        printf("cCrypt.encryptEcbByInKey error \n");
        return -1;

    }

    printf("cCrypt.encryptEcbByInKey size = %d \n", size);

    if (-1 ==  (size = cCrypt.decryptECB(pCipherText, nCipherTextLen, (unsigned char *)szcryptAesKey, pClearText, nClearTextLen)))
    {
        printf("encryptECB error \n");
        return -1;
    }

    printf("cCrypt.decryptECB size = %d \n", size);

    return 0;

}



SKP_TEST(openssl, openssl_tool3)
{
    const int maxDataSize = 1601;
    const int encryptDataSize = maxDataSize * 3;
    char *pKeyStr = "1234567891234567";
    std::string data(1601, 'A');
    printf("data size = %d \n", data.size());
    printf("data = %s \n", data.c_str());

    unsigned char* encryptData = (unsigned char*)calloc(encryptDataSize, sizeof(unsigned char));
    unsigned char* decryptData = (unsigned char*)calloc(encryptDataSize, sizeof(unsigned char));

    encryptECB(encryptData, encryptDataSize, (unsigned char*)pKeyStr, (unsigned char*)data.c_str(), data.size());
    decryptECB(decryptData, encryptDataSize, (unsigned char*)pKeyStr, encryptData, strlen((char *)encryptData));

    printf("encrypt_data size = %d \n", std::string((char *)encryptData).size());
    printf("encrypt_data = %s \n", std::string((char *)encryptData).c_str());

    printf("decrypt_data size = %d \n", std::string((char *)decryptData).size());
    printf("decrypt_data = %s \n", std::string((char *)decryptData).c_str());

    if(strcmp(data.c_str(), std::string((char *)decryptData).c_str()) != 0)
    {
        printf("strcmp error \n");
    }

    ASSERT_STREQ(data.c_str(), std::string((char *)decryptData).c_str());
}

