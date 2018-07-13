#include "skp_DES.h"
#include "gtest/gtest.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include <openssl/des.h>


SKP_TEST(openssl, openssl_des1)
{

    DES_cblock key;
    //随机密钥
    DES_random_key(&key);

    DES_key_schedule schedule;
    //转换成schedule
    DES_set_key_checked(&key, &schedule);

    const_DES_cblock input = "hehehe";
    DES_cblock output;

    printf("cleartext: %s\n", input);

    //加密
    DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
    printf("Encrypted!\n");

    printf("ciphertext: ");
    int i;
    for (i = 0; i < sizeof(input); i++)
        printf("%02x", output[i]);
    printf("\n");

    const_DES_cblock out = "";

    //解密
    DES_ecb_encrypt(&output, &out, &schedule, DES_DECRYPT);
    printf("Decrypted!\n");
    printf("cleartext:%s\n", input);
    printf("cleartext:%s\n", out);

    ASSERT_STREQ((char *)input, (char *)out);

}

SKP_TEST(openssl, openssl_des2)
{

    char *keystring = "this is my key";
    DES_cblock key;
    DES_key_schedule key_schedule;

    //生成一个 key
    DES_string_to_key(keystring, &key);
    if (DES_set_key_checked(&key, &key_schedule) != 0) {
        printf("convert to key_schedule failed.\n");
    }

    //需要加密的字符串
    unsigned char input[] = "this is a text being encrypted by openssl";
    unsigned char input2[1024] = "";
    size_t len = (sizeof(input)+7)/8 * 8;
    unsigned char *output = (unsigned char *)malloc(len+1);
    //IV
    DES_cblock ivec;

    //IV设置为0x0000000000000000
    memset((char*)&ivec, 0, sizeof(ivec));

    //加密
    DES_ncbc_encrypt(input, output, sizeof(input), &key_schedule, &ivec, DES_ENCRYPT);

    //输出加密以后的内容
    int i = 0;
    for (; i < len; ++i)
        printf("%02x", output[i]);
    printf("\n");

    memset((char*)&ivec, 0, sizeof(ivec));

    //解密
    DES_ncbc_encrypt(output, input2, len, &key_schedule, &ivec, 0);

    printf("%s\n", input2);

    free(output);

    ASSERT_STREQ((char *)input, (char *)input2);

}
