#include "skp_AES.h"
#include "openssl/aes.h"
#include "gtest/gtest.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


SKP_TEST(openssl, opensll_AES1)
{
    AES_KEY aes;
    unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16
    unsigned char iv[AES_BLOCK_SIZE];        // init vector
    unsigned char* input_string;
    unsigned char* encrypt_string;
    unsigned char* decrypt_string;
    unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)
    unsigned int i;

    int argc = 2;
    char *argv[] = {"opensll_AES1", "123456133232331321321321321321312321321321321312312321321321312321321321312"
                    "31312321321321321321"
                    "3213123213213213213123"
                    "21321312312312331313123"};

    // check usage
    if (argc != 2) {
        fprintf(stderr, "%s <plain text>\n", argv[0]);
        exit(-1);
    }

    // set the encryption length
    len = 0;
    if ((strlen(argv[1]) + 1) % AES_BLOCK_SIZE == 0) {
        len = strlen(argv[1]) + 1;
    } else {
        len = ((strlen(argv[1]) + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    }

    // set the input string
    input_string = (unsigned char*)calloc(len, sizeof(unsigned char));
    if (input_string == NULL) {
        fprintf(stderr, "Unable to allocate memory for input_string\n");
        exit(-1);
    }
    strncpy((char*)input_string, argv[1], strlen(argv[1]));

    // Generate AES 128-bit key
    for (i=0; i<16; ++i) {
        key[i] = 32 + i;
    }

    // Set encryption key
    for (i=0; i<AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }
    if (AES_set_encrypt_key(key, 128, &aes) < 0) {
        fprintf(stderr, "Unable to set encryption key in AES\n");
        exit(-1);
    }

    // alloc encrypt_string
    encrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));
    if (encrypt_string == NULL) {
        fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
        exit(-1);
    }

    // encrypt (iv will change)
    AES_cbc_encrypt(input_string, encrypt_string, len, &aes, iv, AES_ENCRYPT);

    // alloc decrypt_string
    decrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));
    if (decrypt_string == NULL) {
        fprintf(stderr, "Unable to allocate memory for decrypt_string\n");
        exit(-1);
    }

    // Set decryption key
    for (i=0; i<AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }
    if (AES_set_decrypt_key(key, 128, &aes) < 0) {
        fprintf(stderr, "Unable to set decryption key in AES\n");
        exit(-1);
    }

    // decrypt
    AES_cbc_encrypt(encrypt_string, decrypt_string, len, &aes, iv,
                    AES_DECRYPT);

    // print
    printf("input_string = \n%s\n", input_string);
    printf("encrypted string = ");
    for (i=0; i<len; ++i) {
        printf("%x%x", (encrypt_string[i] >> 4) & 0xf,
               encrypt_string[i] & 0xf);
    }
    printf("\n");
    printf("decrypted string = \n%s\n", decrypt_string);

    ASSERT_STREQ((char *)input_string, (char *)decrypt_string);
}


SKP_TEST(openssl, opensll_AES2)
{
    char *data = "123456";
    printf("原始数据：\n%s\n",data);
    int length = ((strlen(data)+AES_BLOCK_SIZE-1)/AES_BLOCK_SIZE)*AES_BLOCK_SIZE;  //对齐分组

    unsigned char userkey[AES_BLOCK_SIZE];
    unsigned char *encrypt_result = (unsigned char *)malloc(length);
    unsigned char *decrypt_result = (unsigned char *)malloc(length);
    AES_KEY en_key;
    AES_KEY de_key;

    memset((void*)userkey,'k',AES_BLOCK_SIZE);
    memset((void*)encrypt_result, 0, length);
    memset((void*)decrypt_result, 0, length);

    AES_set_encrypt_key(userkey, AES_BLOCK_SIZE*8, &en_key);

    int len = 0;
    /*循环加密，每次只能加密AES_BLOCK_SIZE长度的数据*/
    while(len < length) {
        AES_encrypt((unsigned char *)data+len, encrypt_result+len, &en_key);
        len += AES_BLOCK_SIZE;
    }
    printf("AES_encrypt : \n%s\n",encrypt_result);

    AES_set_decrypt_key(userkey, AES_BLOCK_SIZE*8, &de_key);

    len = 0;
    /*循环解密*/
    while(len < length) {
        AES_decrypt(encrypt_result+len, decrypt_result+len, &de_key);
        len += AES_BLOCK_SIZE;
    }
    printf("AES_decrypt : \n%s\n",decrypt_result);
}
