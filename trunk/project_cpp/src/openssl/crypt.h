/**
* Copyright(C): 2012 by Huawei Technologies Co. Ltd
* @file   crypt.h
* @brief  加解密公共库头文件
*
*
* @author  : null
* @version
* @date   2013-01-16
* @详细描述,简单描述与详细描述之间用一个空行分隔,每一个方面成为一段。
* @bug
* @warning
*
*/

#ifndef HEADER_OCSCRYPT_H
#define HEADER_OCSCRYPT_H

#define AES_KEY_SIZE_128 128  //AES密钥的位数
#define AES_KEY_SIZE_BYTE 16  //AES密钥的字节长度

#define AES_KEY_ECB_ENCRYPT_LEN  64 //AES密钥经过ECB加密后长度

typedef int int32_t;

//#define AES_IN_KEY         "/app/ibas85/ib85dev/user/lrj/crypt/aesin.key"      //内部用来加密密钥使用

//Rsa私钥结构体
typedef struct
{
    char      m_szRSA_N[1024];
    char      m_szRSA_D[1024];
    char      m_szRSA_E[128];
} TRSAKeyPrivate;

/*
namespace lspublic
{
namespace library
{
namespace util
{
*/
/**
* @brief 描述类 CCrypt 功能
*
*
* @return  0-成功 !0-失败
* @attention 对注意事项进行说明
*
*/
class CCrypt
{
public:

    CCrypt();

    ~CCrypt();

    /**
    * @brief 描述方法原型 CCrypt.HexToAscii 功能
    * 将 二进制字符串转换成ascii码字符串
    *
    * @param [out] char *dptr  转换后的字符串
    * @param [in] char *sptr 转换前的字符串
    * @param [in] int32_t len 转换的字符串长度
    * @return  转换后字符串的长度>0-成功
    * @attention 对注意事项进行说明
    *
    */
    int32_t HexToAscii(char *dptr, const char *sptr, int32_t len);

    /**
    * @brief 描述方法原型 CCrypt.AsciiToHex 功能
    * 将ascii码转换成二进制字符串
    *
    * @param [out] char *dptr  转换后的字符串
    * @param [in] char *sptr 转换前的字符串
    * @param [in] int32_t len 转换的字符串长度
    * @return  转换后字符串的长度>0-成功
    * @attention 对注意事项进行说明
    *
    */
    int32_t AsciiToHex(char *dptr, const char *sptr, int32_t len);

    /**
    * @brief 描述方法原型 CCrypt.getNewAesKey 功能
    * 生成 Aes的密钥，并用Aes128Ecb加密.
    *
    * @param [out] unsigned char *pAesKeyEncrypt 加密后的AES密钥
    * @param [in] int32_t nAesKeyEncryptLen 保存密钥的空间大小，检查是否超出范围。
    * @return  获取到的密钥密文的长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * 调用后尽量在字符串末尾添加\0 结束符
    nAesKeyEncryptLen 大小最小为64，建议为128.
    */
    int32_t getNewAesKey(unsigned char *pAesKeyEncrypt, int32_t nAesKeyEncryptLen);

    /**
    * @brief 描述方法原型 CCrypt.loadAesInKey 功能
    * 从文件中加载固定因子，包括Aes密钥和CBC的初始化变量
    *
    * @return  0-成功 -1-失败
    * @attention 对注意事项进行说明
    * 在使用类的Aes和Rsa算法前都需要先执行这个函数。
    */
    int32_t loadAesInKey();

    /**
    * @brief 描述方法原型 CCrypt.encryptEcbByInKey 功能
    * 调用固定因子的密钥进行ECB加密，提供给外部对从外部获取的明文密钥进行
    加密，因为只有经过固定因子加密的密钥才能在这个库的接口中使用。
    *
    * @param [out] unsigned char* pCipherText  加密后的密文
    * @param [in] int32_t nCipherTextLen  保存密文的空间大小
    * @param [in] unsigned char* pClearText 需要加密的明文
    * @param [in] int32_t nClearTextLen 需要加密的明文长度
    * @return  加密后的密文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nCipherTextLen 大小建议为(nClearTextLen+32) * 2
    调用后尽量在字符串末尾添加\0 结束符
    */
    int32_t  encryptEcbByInKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pClearText, int32_t nClearTextLen);

    /**
    * @brief 描述方法原型 CCrypt.encryptECB 功能
    * Aes128Ecb加密接口
    *
    * @param [out] unsigned char* pCipherText 加密后的密文
    * @param [in] int32_t nCipherTextLen  保存密文的空间长度，检查是否超范围
    * @param [in] unsigned char *pKeyStr 密钥
    * @param [in] unsigned char* pClearText 需要加密的明文
    * @param [in] int32_t nClearTextLen 加密明文的长度
    * @return  加密的密文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nCipherTextLen 大小建议大于(nClearTextLen+32) * 2
    调用后尽量在字符串末尾添加\0 结束符
    */
    int32_t encryptECB(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen);

    /**
    * @brief 描述方法原型 CCrypt.decryptECB 功能
    * Aes128Ecb解密接密
    *
    * @param [out] unsigned char *pClearText 解密后的明文
    * @param [in] int32_t nClearTextLen 保存明文的空间的长度，用来检查是否超出范围
    * @param [in] unsigned char *pKeyStr 密钥
    * @param [in] unsigned char *pCipherText 需要解密的密文
    * @param [in] int32_t nCipherTextLen 密文长度
    * @return  解密后明文的长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nClearTextLen 大小建议大于nCipherTextLen/2
    调用后尽量在字符串末尾添加\0 结束符
    */
    int32_t decryptECB(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen);

    /**
    * @brief 描述方法原型 CCrypt.encryptCBC 功能
    *Aes128Cbc加密接口
    * @param [out] unsigned char* pCipherText 加密后的密文
    * @param [in] int32_t nCipherTextLen 保存密文的长度，用来检查是否超出范围
    * @param [in] unsigned char *pKeyStr 密钥
    * @param [in] unsigned char* pClearText 需要加密的字串
    * @return  返回密文的长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nCipherTextLen 大小建议为(nClearTextLen+32) * 2
    调用后尽量在字符串末尾添加\0 结束符
    */
    int32_t encryptCBC(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char *pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen);

    /**
    * @brief 描述方法原型 CCrypt.decryptCBC 功能
    * Aes128Cbc解密接口
    *
    * @param [out] unsigned char *pClearText 解密后的明文
    * @param [in] int32_t nClearTextLen 保存明文的长度，用来检查是否超出范围。
    * @param [in] unsigned char *pKeyStr 密钥
    * @param [in] unsigned char *pCipherText 需要解密的密文
    * @param [in] int32_t nCipherTextLen 密文长度
    * @return  返回明文的长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nClearTextLen 大小建议大于nCipherTextLen/2
    调用后尽量在字符串末尾添加\0 结束符
    */
    int32_t decryptCBC(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen);

    /**
    * @brief 描述方法原型 CCrypt.getNewRsaKey 功能
    * 获取一个随机的Rsa密钥
    *
    * @param [out] TRSAKeyPrivate *pPrivateKey 返回密钥的n e d 三个值的结构体
    * @param [in] int32_t nBit 生成密钥的位数
    * @return  0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t getNewRsaKey(TRSAKeyPrivate *pPrivateKey, int32_t nBit);

    /**
    * @brief 描述方法原型 CCrypt.encryptRSA 功能
    *  用指定的公钥钥进行RSA加密，使用公钥为N E两个字符串
    的密文组成。
    *
    * @param [out] unsigned char *pCipherText 加密后的密文指针
    * @param [in] int32_t nCipherTextLen 保存加密密文的空间大小
    * @param [in] unsigned char *pClearText   明文
    * @param [in] int32_t nClearTextLen 需要加密的明文长度
    * @param [in] TRSAKeyPrivate *pKey 密钥
    * @return    加密后的密文长度>0 -成功 -1-失败
    * @attention 对注意事项进行说明
    * nCipherTextLen长度建议大于密钥的位数对应的字节数的两倍。比如RSA密钥
    使用的1024位，则对应128字节，则nCipherTextLen长度应大于256为好。
    调用后尽量在字符串末尾添加\0 结束符。
    */
    int32_t encryptRSA(unsigned char *pCipherText, int32_t nCipherTextLen, const unsigned char *pClearText, int32_t nClearTextLen, const TRSAKeyPrivate *pKey);

    /**
    * @brief 描述方法原型 CCrypt.decryptRSA 功能
    * 用指定的公钥钥进行RSA解密，私钥为N E D三个字符串
    的密文组成。
    *
    * @param [in] unsigned char *pClearText 解密后的明文
    * @param [in] int32_t nClearTextLen 保存明文的空间大小
    * @param [in] unsigned char *pCipherText 需解密的密文
    * @param [in] int32_t nCipherTextLen 需解密的密文长度
    * @param [in] TRSAKeyPrivate *pKey 密钥
    * @return  解密出来的明文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    * nClearTextLen大小应大于密钥位数。比如密钥使用1024为，则大小应大于
    128较好。
    调用后尽量在字符串末尾添加\0 结束符。
    */
    int32_t decryptRSA(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pCipherText, int32_t nCipherTextLen, const TRSAKeyPrivate *pKey);

    /**
    * @brief 描述方法原型 CCrypt.encryptSign 功能
    * 数字签名接口
    *
    * @param [in] int32_t nType 加密的类型 ,常用NID_md5
    * @param [in] const unsigned char *pInfoText 被nType加密过后的签名信息
    * @param [in] int32_t nInfoTextLen 签名信息的长度
    * @param [out] unsigned char *pSigRet 签名信息加密的密文
    * @param [out] int32_t *pSigLen 返回加密的密文的长度
    * @param [in] TRSAKeyPrivate *pKey 密钥
    * @return  加密的密文大小>0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t encryptSign(int32_t nType, const unsigned char *pInfoText,  int32_t nInfoTextLen, unsigned char *pSigRet, int32_t *pSigLen, const TRSAKeyPrivate *pKey);

    /**
    * @brief 描述方法原型 CCrypt.decryptVerify 功能
    * 数字签名的验证接口
    *
    * @param [in] int32_t nType 加密的类型 ,常用NID_md5
    * @param [in] const unsigned char *pInfoText 被nType加密过后的签名信息
    * @param [in] int32_t nInfoTextLen 签名信息的长度
    * @param [in] const unsigned char *pSigbuf 签名信息加密的密文
    * @param [in] int32_t nSigLen 密文的长度
    * @param [in] TRSAKeyPrivate *pKey 密钥
    * @return  >0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t decryptVerify(int32_t nType, const unsigned char *pInfoText, int32_t nInfoTextLen, const unsigned char *pSigbuf, int32_t nSigLen, const TRSAKeyPrivate *pKey);

    /**
    * @brief SHA256位加密算法
    * 密文长度固定为64字节ascii码。
    *
    * @param [out] char* pCiPherText  加密后的密文
    * @param [in] char *pClearText  需要加密的字串
    * @param [in] int32_t nClearTextLen  需要加密的字串长度
    * @return   密文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t encodeSHA256(char *pCipherText, const char *pClearText, int32_t nClearTextLen);

    /**
    * @brief SHA512位加密算法
    *  密文长度固定为128字节ascii码
    *
    * @param [out] char* pCiPherText  加密后的密文
    * @param [in] char *pClearText  需要加密的字串
    * @param [in] int32_t nClearTextLen  需要加密的字串长度
    * @return  密文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t encodeSHA512(char *pCipherText, const char *pClearText, int32_t nClearTextLen);

    /**
    * @brief MD5加密算法
    * 密文长度固定为16字节二进制码
    *
    * @param [out] char* pCipherText  加密后的密文
    * @param [in] char *pClearText 需要加密的字串
    * @param [in] int32_t nClearTextLen  需要加密的字串长度
    * @return  密文长度>0-成功 -1-失败
    * @attention 对注意事项进行说明
    *
    */
    int32_t encodeMD5(char *pCipherText, const char *pClearText, int32_t nClearTextLen);


    const char* getlasterr() const
    {
        return m_szLastErrMsg;
    }

private:
    char HexToChar(char sbyte) const;
    char CharToHex(char schar) const;
    int32_t encryptEcbByKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen);
    int32_t decryptEcbByKey(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char *pCipherText, int32_t nCipherTextLen);
    int32_t encryptCbcByKey(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen);
    int32_t decryptCbcByKey(unsigned char *pClearText, int32_t nClearTextLen, const unsigned char *pKeyStr, const unsigned char* pCipherText, int32_t nCipherTextLen);
    int32_t encryptAes(unsigned char* pCipherText, int32_t nCipherTextLen, const unsigned char* pInitVectorStr, const unsigned char* pKeyStr, const unsigned char* pClearText, int32_t nClearTextLen, int32_t nKeySize);
    int32_t decryptAes(unsigned char* pClearText , int32_t nClearTextLen, const unsigned char* pInitVectorStr, const unsigned char *pKeyStr, const unsigned char* pCipherText, int32_t nCipherTextLen, int32_t nKeySize);

    unsigned char *m_pAesInKey; //固定因子长度为16字节
    unsigned char *m_pInitVector; //CBC初始化变量
    char m_szLastErrMsg[1024];
};

/*
}
}
}
*/
#endif



