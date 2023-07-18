/*
    字节序就是字节在内存中存储的顺序
    小端字节序：数据的高位字节存储在内存的高位地址，低位字节存储在内存的低位地址
    大端字节序：数据的低位字节存储在内存的高位地址，高位字节存储在内存的低位地址
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
    union{
        short value;//2Byte
        char byte[sizeof(short)]; // char[2] 2Byte
    } test;

    test.value = 0x0102;

    if ((test.byte[0] == 1) && (test.byte[1] == 2)){
        printf("此电脑是大端序列\n");
    }else if ((test.byte[0] == 2) && (test.byte[1] == 1)){
        printf("此电脑是小端序列\n");
    }else{
        printf("未知\n");
    }
    return 0;
}
