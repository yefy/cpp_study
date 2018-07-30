/**
 * Copyright(C): 2012 by Huawei Technologies Co. Ltd
 * @file   crypt.c
 * @brief 安全红线加解密函数实现
 *
 *
 * @author  : null
 * @version
 * @date   2013-01-17
 * @主要分为三大类
    Aes加密算法，分为Ecb和Cbc两种，密钥使用Aes128Ecb再次加密，保存
在文件gen_aes.key。
    Ecb使用接口encryptECB，decryptECB。
    Cbc使用接口encryptCBC，decryptCBC
    密文在原文长度为16的整数倍时，假设为16*n，则密文长度 16*n + 16。
    在不足16整数倍情况下，假设为16*n+m，则密文长度为 16*(n+1)+16。


    RSA加密算法
    调用encryptRSA，decryptRSA。
    RSA数字签名
    encryptSign，decryptVerify


    不可逆加密算法
    SHA 加密，使用encodeSHA256，encodeSHA512，加密后分别生成64字节128字节
的十六进制密文。
    Md5 加密，使用encodeMD5，不能用来加密密码等关键信息，主要作为
摘要和验证使用。加密后为16字节二进制字符串。
 * @bug
 * @warning
 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
//#include <openssl/rsa.h>
#include <openssl/md5.h>
#include "crypt.h"


//using namespace lspublic::library::util;

//lint -save -e801 -e1762
char CCrypt::HexToChar(char sbyte) const
{
    sbyte &= 0x0F;
    if (sbyte < 0x0A) return (sbyte + '0');
    else return (sbyte + ('A' - 0x0A));
}

int32_t CCrypt::HexToAscii(char *dptr, const char *sptr, int32_t len)
{
    int32_t i;
    char  stemp;

    for (i = 1; i <= len; i++)
    {
        if (NULL == sptr)
        {
            return -1;
        }
        stemp = *sptr++;
        if (NULL == dptr)
        {
            return -1;
        }
        *dptr++ = HexToChar(stemp >> 4); //lint !e701 !e702
        if (NULL == dptr)//lint !e774
        {
            return -1;
        }
        *dptr++ = HexToChar(stemp & 0x0F);
    }
    return (2 * len);
}

char CCrypt::CharToHex(char schar) const
{
    if (schar >= '0' && schar <= '9') return (schar - '0');
    else if (schar >= 'A' && schar <= 'F') return ((schar - 'A') + 0x0A);
    else if (schar >= 'a' && schar <= 'f') return ((schar - 'a') + 0x0A);
    else return 0;
}

int32_t CCrypt::AsciiToHex(char *dptr, const char *sptr, int32_t len)
{
    int32_t i=0;
    char  dtemp=0, stemp=0;

    if (len % 2) return 0;
    len /= 2;
    for (i = 1; i <= len; i++)
    {
        if (NULL == sptr)
        {
            return -1;
        }
        stemp   = CharToHex(*sptr++);
        dtemp   = stemp << 4; //lint !e701
        if (NULL == sptr || NULL == dptr)//lint !e774 !e944
        {
            return -1;
        }
        *dptr++ = CharToHex(*sptr++) | dtemp;
    }
    return len;
}

CCrypt::CCrypt()
{
    m_pAesInKey = NULL;
    m_pInitVector = NULL;
    memset(m_szLastErrMsg, 0, sizeof(m_szLastErrMsg));
}


CCrypt::~CCrypt()
{
    if(m_pAesInKey != NULL)
    {
        free(m_pAesInKey);
        m_pAesInKey = NULL;
    }
    if(m_pInitVector != NULL)
    {
        free(m_pInitVector);
        m_pInitVector = NULL;
    }
}

int32_t CCrypt:: setAesKey(const char *key)
{
    if(NULL != m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, InKey has been load once!", sizeof(m_szLastErrMsg));
        return -1;
    }

    const char *defKey = "1234567891234567";
    if(key)
    {
        if(strlen(key) != AES_KEY_SIZE_BYTE)
        {
            strncpy(m_szLastErrMsg,"Error in loadAesInKey, InKey size != AES_KEY_SIZE_BYTE", sizeof(m_szLastErrMsg));
            return -1;
        }
    }
    else
    {
        key = defKey;
    }



    m_pAesInKey = (unsigned char*)calloc(AES_KEY_SIZE_BYTE, sizeof(unsigned char));
    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, m_pAesInKey calloc error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    memcpy(m_pAesInKey, key, AES_KEY_SIZE_BYTE);

    return 0;
}

int32_t CCrypt:: setInitVectorKey(const char *key)
{
    if(NULL != m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, InKey has been load once!", sizeof(m_szLastErrMsg));
        return -1;
    }

    const char *defKey = "1234567891234567";
    if(key)
    {
        if(strlen(key) != AES_KEY_SIZE_BYTE)
        {
            strncpy(m_szLastErrMsg,"Error in loadAesInKey, InKey size != AES_KEY_SIZE_BYTE", sizeof(m_szLastErrMsg));
            return -1;
        }
    }
    else
    {
        key = defKey;
    }



    m_pInitVector = (unsigned char*)calloc(AES_KEY_SIZE_BYTE, sizeof(unsigned char));
    if(NULL == m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, m_pInitVector calloc error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    memcpy(m_pInitVector, key, AES_KEY_SIZE_BYTE);

    return 0;
}

int32_t CCrypt:: loadAesInKey()
{
    FILE *file = NULL;

    //wx156570 begin  去掉'AES_IN_KEY"，换成到etc/aesin.key/读取文件配置

    char szFilePath[256] = "../../../cpp_study/trunk/project_cpp/src/openssl/aesin.key";
    //(void)snprintf(szFilePath,sizeof(szFilePath),"%s/cfg/aesin.key",getenv("IBAS_HOME"));
    //wx156570 end 2013-3-25

    if(NULL != m_pAesInKey || NULL != m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, InKey has been load once!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if((file = fopen(szFilePath, "rb")) == NULL)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, fopen fail!", sizeof(m_szLastErrMsg));
        return -1;
    }
    m_pAesInKey = (unsigned char*)calloc(AES_KEY_SIZE_BYTE, sizeof(unsigned char));
    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, m_pAesInKey calloc error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(fread(m_pAesInKey, AES_KEY_SIZE_BYTE, 1, file) != 1) //读取一块16字节，作为固定密钥。
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, fread error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    m_pInitVector = (unsigned char*)calloc(AES_KEY_SIZE_BYTE, sizeof(unsigned char));
    if(NULL == m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, m_pInitVector calloc error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(fread(m_pInitVector, AES_KEY_SIZE_BYTE, 1, file) != 1) //读取一块16字节，作为固定cbc初始化变量。
    {
        strncpy(m_szLastErrMsg,"Error in loadAesInKey, fread error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    fclose(file);
    return 0;
}

int32_t CCrypt:: getNewAesKey(unsigned char *pAesKeyEncrypt, int32_t nAesKeyEncryptLen)
{
    unsigned char szAesKeyRandom[AES_KEY_SIZE_BYTE];

    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in getNewAesKey, m_pAesInKey == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if (1 != RAND_bytes(szAesKeyRandom, AES_KEY_SIZE_BYTE))
    {
        strncpy(m_szLastErrMsg,"Error in getNewAesKey, RAND_bytes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(encryptEcbByInKey(pAesKeyEncrypt, nAesKeyEncryptLen, szAesKeyRandom, AES_KEY_SIZE_BYTE) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in getNewAesKey, encryptEcbByInKey return error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    return 0;
}

int32_t CCrypt:: encryptEcbByInKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText)
    {
        strncpy(m_szLastErrMsg,"Error input para pClearText=NULL, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if((nRet = encryptAes(pCipherText, nCipherTextLen, NULL, m_pAesInKey, pClearText, nClearTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptEcbByInKey, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: encryptCbcByKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = encryptAes(pCipherText, nCipherTextLen, m_pInitVector, pKeyStr, pClearText, nClearTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptCbcByKey, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: decryptCbcByKey(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char* pCipherText, int32_t nCipherTextLen)
{
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = decryptAes(pClearText, nClearTextLen, m_pInitVector, pKeyStr, pCipherText, nCipherTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptCbcByKey, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: encryptEcbByKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = encryptAes(pCipherText, nCipherTextLen, NULL, pKeyStr, pClearText, nClearTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptEcbByKey, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: decryptEcbByKey(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen)
{
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = decryptAes(pClearText, nClearTextLen, NULL, pKeyStr, pCipherText, nCipherTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptEcbByKey, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: encryptECB(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;
    unsigned char pClearKey[32]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(decryptEcbByKey(pClearKey, sizeof(pClearKey), m_pAesInKey, pKeyStr, AES_KEY_ECB_ENCRYPT_LEN) != AES_KEY_SIZE_BYTE)
    {
        strncpy(m_szLastErrMsg,"Error in encryptECB, decryptEcbByKey error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = encryptAes(pCipherText, nCipherTextLen, NULL, pClearKey, pClearText, nClearTextLen, AES_KEY_SIZE_128))  < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptECB, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: decryptECB(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen)
{
    int32_t nRet = 0;
    unsigned char pClearKey[32]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(decryptEcbByKey(pClearKey, sizeof(pClearKey), m_pAesInKey, pKeyStr, AES_KEY_ECB_ENCRYPT_LEN) != AES_KEY_SIZE_BYTE)
    {
        strncpy(m_szLastErrMsg,"Error in encryptECB, decryptEcbByKey error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if((nRet = decryptAes(pClearText, nClearTextLen, NULL, pClearKey, pCipherText, nCipherTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptECB, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: encryptCBC(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;
    unsigned char pClearKey[32]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(NULL == m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in getNewAesKey, m_pInitVector == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(decryptEcbByKey(pClearKey, sizeof(pClearKey), m_pAesInKey, pKeyStr, AES_KEY_ECB_ENCRYPT_LEN) != AES_KEY_SIZE_BYTE)
    {
        strncpy(m_szLastErrMsg,"Error in encryptECB, decryptEcbByKey error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = encryptAes(pCipherText, nCipherTextLen, m_pInitVector, pClearKey, pClearText, nClearTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptCBC, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: decryptCBC(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen)
{
    int32_t nRet = 0;
    unsigned char pClearKey[32]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKeyStr)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(NULL == m_pInitVector)
    {
        strncpy(m_szLastErrMsg,"Error in getNewAesKey, m_pInitVector == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if(decryptEcbByKey(pClearKey, sizeof(pClearKey), m_pAesInKey, pKeyStr, AES_KEY_ECB_ENCRYPT_LEN) != AES_KEY_SIZE_BYTE)
    {
        strncpy(m_szLastErrMsg,"Error in encryptECB, decryptEcbByKey error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if((nRet = decryptAes(pClearText, nClearTextLen, m_pInitVector, pClearKey, pCipherText, nCipherTextLen, AES_KEY_SIZE_128)) < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptCBC, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    return nRet;
}

int32_t CCrypt:: encryptAes(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pInitVectorStr, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen, int32_t nKeySize)
{
    AES_KEY stAesKey;
    unsigned char szKey[AES_BLOCK_SIZE]="";        // AES_BLOCK_SIZE = 16
    unsigned char szInitVector[AES_BLOCK_SIZE]="";        // init vector
    unsigned char* pEncryptString = NULL;
    unsigned char* pPadedText = NULL;	//text after padding
    int32_t nEncryptLen = 0;        // encrypt length (in multiple of AES_BLOCK_SIZE)
    int32_t nPaddingLen = 0; //padding length
    int32_t i = 0;
    unsigned char szSplitData[AES_BLOCK_SIZE]=""; //ecb split data
    int32_t nSplitCount = 0;	//ecb split count
    unsigned char szResultData[AES_BLOCK_SIZE]=""; //ecb split result data
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    //set key
    if(NULL  != pKeyStr)
    {
        memcpy((char*)szKey, (char*)pKeyStr, AES_BLOCK_SIZE);
    }
    else
    {
        strncpy(m_szLastErrMsg,"Error in encryptAes,pKeyStr == NULL!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    if(NULL  != pInitVectorStr)
    {
        memcpy((char*)szInitVector, (char*)pInitVectorStr, AES_BLOCK_SIZE);
    }

    if(nClearTextLen % AES_BLOCK_SIZE == 0)
    {
        nPaddingLen = nClearTextLen;
    }
    else
    {
        nPaddingLen = (nClearTextLen / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    }

    nEncryptLen = nPaddingLen + AES_BLOCK_SIZE; //填充完之后在后面再补一块16字节

    // set the input string
    pPadedText = (unsigned char*)calloc(nEncryptLen, sizeof(unsigned char));
    if (NULL == pPadedText)
    {
        strncpy(m_szLastErrMsg,"Error in encryptAes,pPadedText calloc error!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    memcpy((char *)pPadedText, (char*)pClearText, nClearTextLen);

    for(i = nClearTextLen; i < nPaddingLen; i++)
    {
        pPadedText[i] = '\0';
    }
    for(i = nPaddingLen; i < nEncryptLen; i++)
    {
        pPadedText[i] = nPaddingLen - nClearTextLen;  //最后16个字节填充为不满整块的数值，解密时根据这个算出明文的长度。
    }

    if (AES_set_encrypt_key(szKey, nKeySize, &stAesKey) < 0)
    {
        strncpy(m_szLastErrMsg,"Unable to set encryption key in encryptAes!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }

    // alloc encrypt_string
    pEncryptString = (unsigned char*)calloc(nEncryptLen, sizeof(unsigned char));
    if (pEncryptString == NULL)
    {
        strncpy(m_szLastErrMsg,"Error in encryptAes,pEncryptString calloc error!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }

    // ecb must split
    if(NULL == pInitVectorStr)
    {
        nSplitCount = nEncryptLen / AES_BLOCK_SIZE;
        int32_t nTempSeek;
        for(i=0; i < nSplitCount; i++)
        {
            nTempSeek = i*AES_BLOCK_SIZE;
            if(nTempSeek + AES_BLOCK_SIZE > nEncryptLen)
            {
                nRet = -1;
                goto RETURN_FLAG;
            }
            memcpy(szSplitData, pPadedText+nTempSeek, AES_BLOCK_SIZE);
            AES_ecb_encrypt(szSplitData, szResultData, &stAesKey, AES_ENCRYPT);
            memcpy(pEncryptString+nTempSeek, szResultData, AES_BLOCK_SIZE);
        }
    }
    else
    {
        AES_cbc_encrypt(pPadedText, pEncryptString, nEncryptLen, &stAesKey, szInitVector, AES_ENCRYPT);
    }
    if(nCipherTextLen < nEncryptLen*2)
    {
        strncpy(m_szLastErrMsg,"Error in encryptAes, nCipherTextLen is too short!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    nRet = HexToAscii((char*)pCipherText, (char*)pEncryptString, nEncryptLen);

RETURN_FLAG:
    if(NULL != pPadedText)
    {
        free(pPadedText);
        pPadedText = NULL;
    }
    if(NULL != pEncryptString)
    {
        free(pEncryptString);
        pEncryptString = NULL;
    }
    return nRet;
}

int32_t CCrypt:: decryptAes(unsigned char* pClearText , int32_t nClearTextLen, const unsigned char* pInitVectorStr, const unsigned char *pKeyStr, const unsigned char* pCipherText, int32_t nCipherTextLen, int32_t nKeySize)
{
    AES_KEY stAesKey;
    unsigned char szKey[AES_BLOCK_SIZE]="";        // AES_BLOCK_SIZE = 16
    unsigned char szInitVector[AES_BLOCK_SIZE]="";        // init vector
    int32_t nDecryptLen = 0;        // decrypt length (in multiple of AES_BLOCK_SIZE)
    int32_t i = 0;
    int32_t nBinData = 0;
    unsigned char* pBinData = NULL;	//bin text
    unsigned char szSplitData[AES_BLOCK_SIZE]=""; //ecb split data
    int32_t nSplitCount = 0;	//ecb split count
    unsigned char szResultData[AES_BLOCK_SIZE]=""; //ecb split result data
    int32_t nRet = 0;

    if (NULL == pClearText || NULL == pCipherText)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptAes error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    //set key
    if(NULL != pKeyStr)
    {
        memcpy((char*)szKey, (char*)pKeyStr, AES_BLOCK_SIZE);
    }
    else
    {
        strncpy(m_szLastErrMsg,"Error in encryptAes,pKeyStr == NULL!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    if(NULL != pInitVectorStr)
    {
        memcpy((char*)szInitVector, (char*)pInitVectorStr, AES_BLOCK_SIZE);
    }

    // set the encryption length
    nDecryptLen = 0;
    if (nCipherTextLen % (AES_BLOCK_SIZE*2) == 0)
    {
        nDecryptLen = nCipherTextLen / 2;
    }
    else
    {
        strncpy(m_szLastErrMsg,"Error in decryptAes, nCipherTextLen is error!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }

    pBinData = (unsigned char*)calloc(nDecryptLen, sizeof(unsigned char));
    if(NULL == pBinData)
    {
        strncpy(m_szLastErrMsg,"Error in decryptAes, pBinData calloc error!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    nBinData = AsciiToHex((char*)pBinData, (char*)pCipherText, nCipherTextLen);
    if (nBinData <= 0)
    {
        strncpy(m_szLastErrMsg,"Error input para, AsciiToHex error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    if (AES_set_decrypt_key(szKey, nKeySize, &stAesKey) < 0)
    {
        strncpy(m_szLastErrMsg,"Unable to set decryption key in decryptAes!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    if (nClearTextLen < nDecryptLen)
    {
        strncpy(m_szLastErrMsg,"Error in decryptAes, nClearTextLen is too short!", sizeof(m_szLastErrMsg));
        nRet = -1;
        goto RETURN_FLAG;
    }
    // ecb must split
    if (NULL == pInitVectorStr)
    {
        nSplitCount = nDecryptLen/AES_BLOCK_SIZE;
        int32_t nTempSeek;
        for(i=0; i < nSplitCount; i++)
        {
            nTempSeek = i*AES_BLOCK_SIZE;
            if(nTempSeek + AES_BLOCK_SIZE > nDecryptLen)
            {
                nRet = -1;
                goto RETURN_FLAG;
            }
            memcpy(szSplitData, pBinData+nTempSeek, AES_BLOCK_SIZE);
            AES_ecb_encrypt(szSplitData, szResultData, &stAesKey, AES_DECRYPT);
            memcpy(pClearText+nTempSeek, szResultData, AES_BLOCK_SIZE);
        }
    }
    else
    {
        AES_cbc_encrypt(pBinData, pClearText, nDecryptLen, &stAesKey, szInitVector, AES_DECRYPT);
    }
    nRet = (nDecryptLen - AES_BLOCK_SIZE) - pClearText[nDecryptLen-1];


RETURN_FLAG:
    if(NULL != pBinData)
    {
        free(pBinData);
        pBinData = NULL;
    }
    return nRet;
}

#ifdef OPENSSL_RSA
int32_t CCrypt:: getNewRsaKey(TRSAKeyPrivate *pPrivateKey, int32_t nBit)
{

    BIGNUM *be = NULL;
    RSA *pRsa = NULL;
    int32_t nNLen, nELen, nDLen;
    TRSAKeyPrivate  stBnKey;

    pRsa = RSA_new();
    be=BN_new();
    if (1 != BN_set_word(be,RSA_F4))
    {
        strncpy(m_szLastErrMsg,"Error in getNewRsaKey, BN_set_word error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    (void)RSA_generate_key_ex(pRsa, nBit, be, NULL);//lint !e658

    nNLen = BN_bn2bin(pRsa->n, (unsigned char*)stBnKey.m_szRSA_N);
    nELen = BN_bn2bin(pRsa->e, (unsigned char*)stBnKey.m_szRSA_E);
    nDLen = BN_bn2bin(pRsa->d, (unsigned char*)stBnKey.m_szRSA_D);
    RSA_free(pRsa);

    if(NULL == m_pAesInKey || NULL == pPrivateKey)
    {
        strncpy(m_szLastErrMsg,"Error in getNewRsaKey, m_pAesInKey == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }

    memset(pPrivateKey->m_szRSA_N, 0x00, sizeof(pPrivateKey->m_szRSA_N));
    memset(pPrivateKey->m_szRSA_E, 0x00, sizeof(pPrivateKey->m_szRSA_E));
    memset(pPrivateKey->m_szRSA_D, 0x00, sizeof(pPrivateKey->m_szRSA_D));
    if(encryptEcbByInKey((unsigned char*)pPrivateKey->m_szRSA_N, sizeof(pPrivateKey->m_szRSA_N), (unsigned char*)stBnKey.m_szRSA_N, nNLen) < 0
            || encryptEcbByInKey((unsigned char*)pPrivateKey->m_szRSA_E, sizeof(pPrivateKey->m_szRSA_E), (unsigned char*)stBnKey.m_szRSA_E, nELen) < 0
            || encryptEcbByInKey((unsigned char*)pPrivateKey->m_szRSA_D, sizeof(pPrivateKey->m_szRSA_D), (unsigned char*)stBnKey.m_szRSA_D, nDLen)< 0)
    {
        strncpy(m_szLastErrMsg,"Error in getNewRsaKey, encrypt rsa key error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    return 0;
}

int32_t CCrypt:: encryptRSA(unsigned char *pCipherText, int32_t nCipherTextLen, const unsigned char *pClearText, int32_t nClearTextLen, const TRSAKeyPrivate *pKey)
{

    RSA *pRsa;
    TRSAKeyPrivate stClearTextKey;
    int32_t nNLen, nELen;
    int32_t nEncryptRet = 0;

    unsigned char szEncryptResult[1024]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKey)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptRSA error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa = RSA_new();

    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in encryptRSA, m_pAesInKey == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nNLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_N, sizeof(stClearTextKey.m_szRSA_N), m_pAesInKey, (unsigned char*)pKey->m_szRSA_N, strlen(pKey->m_szRSA_N));
    nELen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_E, sizeof(stClearTextKey.m_szRSA_E), m_pAesInKey, (unsigned char*)pKey->m_szRSA_E, strlen(pKey->m_szRSA_E));
    if(nNLen < 0 || nELen < 0 )
    {
        strncpy(m_szLastErrMsg,"Error in encryptRSA, decrypt rsa key error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(nClearTextLen > (nNLen - 11)) //填充之后大于这个长度会出错。
    {
        strncpy(m_szLastErrMsg,"Error in encryptRSA, pClearText is too long!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa->n = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_N, nNLen, pRsa->n);
    pRsa->e = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_E, nELen, pRsa->e);

    nEncryptRet = RSA_public_encrypt(nClearTextLen, pClearText, szEncryptResult, pRsa, RSA_PKCS1_PADDING);
    if(nEncryptRet != nNLen)
    {
        strncpy(m_szLastErrMsg,"Error in encryptRSA, RSA_public_encrypt error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    RSA_free(pRsa);
    if(nCipherTextLen < nEncryptRet*2)
    {
        strncpy(m_szLastErrMsg,"Error in encryptRSA, nCipherTextLen is too short!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nEncryptRet = HexToAscii((char*)pCipherText, (char*)szEncryptResult, nEncryptRet);

    return nEncryptRet;
}

int32_t CCrypt::decryptRSA(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pCipherText, int32_t nCipherTextLen, const TRSAKeyPrivate *pKey)
{

    int32_t nDecryptRet = 0;
    TRSAKeyPrivate stClearTextKey;
    RSA *pRsa;
    int32_t nNLen, nELen, nDLen;
    unsigned char szCipherHex[1024]="";

    if (NULL == pClearText || NULL == pCipherText || NULL == pKey)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptRSA error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa = RSA_new();

    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, m_pAesInKey  == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nNLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_N, sizeof(stClearTextKey.m_szRSA_N), m_pAesInKey, (unsigned char*)pKey->m_szRSA_N, strlen(pKey->m_szRSA_N));
    nELen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_E, sizeof(stClearTextKey.m_szRSA_E), m_pAesInKey, (unsigned char*)pKey->m_szRSA_E, strlen(pKey->m_szRSA_E));
    nDLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_D, sizeof(stClearTextKey.m_szRSA_D), m_pAesInKey, (unsigned char*)pKey->m_szRSA_D, strlen(pKey->m_szRSA_D));
    if(nNLen < 0 || nELen < 0 || nDLen < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, decrypt rsa key error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(nCipherTextLen != nNLen*2)
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, nCipherTextLen is error!", sizeof(m_szLastErrMsg));
        return -1;
    }


    pRsa->n = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_N, nNLen, pRsa->n);
    pRsa->e = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_E, nELen, pRsa->e);
    pRsa->d = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_D, nDLen, pRsa->d);

    nDecryptRet = AsciiToHex((char*)szCipherHex, (char*)pCipherText, nCipherTextLen);

    if(nClearTextLen < nNLen)
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, nClearTextLen is too short!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nDecryptRet = RSA_private_decrypt(nDecryptRet, szCipherHex, pClearText, pRsa, RSA_PKCS1_PADDING);
    if(nDecryptRet < 0 )
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, RSA_private_decrypt  error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    RSA_free(pRsa);

    return nDecryptRet;
}

int32_t CCrypt::encryptSign(int32_t nType, const unsigned char *pInfoText,  int32_t nInfoTextLen,
                            unsigned char *pSigRet, int32_t *pSigLen, const TRSAKeyPrivate *pKey)
{
    RSA *pRsa;
    int32_t nNLen, nELen, nDLen;
    TRSAKeyPrivate stClearTextKey;
    unsigned char pHexSigRet[1024]="";

    if (NULL == pInfoText || NULL == pSigRet || NULL == pKey || NULL == pSigLen)
    {
        strncpy(m_szLastErrMsg,"Error input para, encryptSign error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa = RSA_new();

    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in decryptRSA, m_pAesInKey  == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nNLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_N, sizeof(stClearTextKey.m_szRSA_N), m_pAesInKey, (unsigned char*)pKey->m_szRSA_N, strlen(pKey->m_szRSA_N));
    nELen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_E, sizeof(stClearTextKey.m_szRSA_E), m_pAesInKey, (unsigned char*)pKey->m_szRSA_E, strlen(pKey->m_szRSA_E));
    nDLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_D, sizeof(stClearTextKey.m_szRSA_D), m_pAesInKey, (unsigned char*)pKey->m_szRSA_D, strlen(pKey->m_szRSA_D));
    if(nNLen < 0 || nELen < 0 || nDLen < 0)
    {
        strncpy(m_szLastErrMsg,"Error in encryptSign, decrypt rsa key error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(nInfoTextLen > (nNLen -11))
    {
        strncpy(m_szLastErrMsg,"Error in encryptSign, nInfoTextLen is too long!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa->n = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_N, nNLen, pRsa->n);
    pRsa->e = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_E, nELen, pRsa->e);
    pRsa->d = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_D, nDLen, pRsa->d);

    if (RSA_sign(nType, pInfoText, nInfoTextLen, pHexSigRet, (unsigned int*)pSigLen, pRsa) > 0 )
    {
        if (pRsa != NULL)
        {
            RSA_free(pRsa);
            pRsa = NULL;
        }
        *pSigLen = HexToAscii((char*)pSigRet, (char*)pHexSigRet, *pSigLen);
        return *pSigLen;
    }
    else
    {
        if (pRsa != NULL)
        {
            RSA_free(pRsa);
            pRsa = NULL;
        }
        return -1;
    }
}

int32_t CCrypt::decryptVerify(int32_t nType, const unsigned char *pInfoText, int32_t nInfoTextLen,
                              const unsigned char *pSigbuf, int32_t nSigLen, const TRSAKeyPrivate *pKey)
{

    RSA *pRsa;
    int32_t nNLen, nELen;
    TRSAKeyPrivate stClearTextKey;
    unsigned char szAsciiSigRet[1024] = "";

    if (NULL == pInfoText || NULL == pSigbuf || NULL == pKey)
    {
        strncpy(m_szLastErrMsg,"Error input para, decryptVerify error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa = RSA_new();

    if(NULL == m_pAesInKey)
    {
        strncpy(m_szLastErrMsg,"Error in decryptVerify, m_pAesInKey  == NULL!", sizeof(m_szLastErrMsg));
        return -1;
    }
    nNLen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_N, sizeof(stClearTextKey.m_szRSA_N), m_pAesInKey, (unsigned char*)pKey->m_szRSA_N, strlen(pKey->m_szRSA_N));
    nELen = decryptEcbByKey((unsigned char*)stClearTextKey.m_szRSA_E, sizeof(stClearTextKey.m_szRSA_E), m_pAesInKey, (unsigned char*)pKey->m_szRSA_E, strlen(pKey->m_szRSA_E));
    if(nNLen < 0 || nELen < 0)
    {
        strncpy(m_szLastErrMsg,"Error in decryptVerify, decrypt rsa key error!", sizeof(m_szLastErrMsg));
        return -1;
    }
    if(nSigLen != nNLen*2)
    {
        strncpy(m_szLastErrMsg,"Error in decryptVerify, nSigLen error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    pRsa->n = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_N, nNLen, pRsa->n);
    pRsa->e = BN_bin2bn((const unsigned char*)stClearTextKey.m_szRSA_E, nELen, pRsa->e);

    nSigLen = AsciiToHex((char*)szAsciiSigRet, (char*)pSigbuf, nSigLen);

    if (RSA_verify(nType, pInfoText, nInfoTextLen, szAsciiSigRet, nSigLen, pRsa) > 0 )
    {
        if (pRsa != NULL)
        {
            RSA_free(pRsa);
            pRsa = NULL;
        }
        return nSigLen;
    }
    else
    {
        if (pRsa != NULL)
        {
            RSA_free(pRsa);
            pRsa = NULL;
        }
        return -1;
    }
}
#endif
int32_t CCrypt:: encodeSHA256(char *pCipherText, const char *pClearText, int32_t nClearTextLen)
{
    unsigned char szResultData[SHA256_DIGEST_LENGTH] = "";
    int32_t nRet = 0;

    if (NULL == pCipherText || NULL == pClearText)
    {
        strncpy(m_szLastErrMsg,"Error input para, encodeSHA256 error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    (void)SHA256((unsigned char*)pClearText, nClearTextLen, szResultData);
    nRet = HexToAscii(pCipherText, (char*)szResultData, SHA256_DIGEST_LENGTH);

    return nRet;
}

int32_t CCrypt:: encodeSHA512(char *pCipherText, const char *pClearText, int32_t nClearTextLen)
{
    unsigned char szResultData[SHA512_DIGEST_LENGTH] = "";
    int32_t nRet = 0;

    if (NULL == pCipherText || NULL == pClearText)
    {
        strncpy(m_szLastErrMsg,"Error input para, encodeSHA512 error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    (void)SHA512((unsigned char*)pClearText, nClearTextLen, szResultData);
    nRet = HexToAscii(pCipherText, (char*)szResultData, SHA512_DIGEST_LENGTH);

    return nRet;
}

int32_t CCrypt:: encodeMD5(char *pCipherText, const char *pClearText, int32_t nClearTextLen)
{
    int32_t nRet = 0;

    if (NULL == pCipherText || NULL == pClearText)
    {
        strncpy(m_szLastErrMsg,"Error input para, encodeMD5 error!", sizeof(m_szLastErrMsg));
        return -1;
    }

    (void)MD5((const unsigned char*)pClearText, nClearTextLen, (unsigned char*)pCipherText);
    nRet = MD5_DIGEST_LENGTH;

    return nRet;
}

//lint -restore

