#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //htons 转换端口
    unsigned short a = 0x0102;

    printf("a : %x\n", a);
    unsigned short b = htons(a);//转换为网络字节序,大端

    printf("b : %x\n", b);

    printf("---------------------------\n");
    //htonl 转换IP
    char buf[4] = {192,168,1,100};
    int num = *(int *)buf;
    int sum = htonl(num); //转换为网络字节字序，为大端
    unsigned char *p = (char *)&sum;

    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

    printf("---------------------------\n");

    //ntohl
    unsigned char buf1[4] = {1, 1, 168, 192};//主机字节序，小端
    int num1 = *(int *)buf1;
    int sum1 = ntohl(num1);
    unsigned char * p1 = (unsigned char *)&sum1;
    printf("%d, %d, %d, %d \n", *p1, *(p1+1), *(p1+2), *(p1+3));

    //ntohs
    //网络字节序列到主机字节序列 大端->小端
    unsigned short num2 = 0x0102;
    printf("num2 : 0x0%x\n", num2);

    //转换为主机字节序列
    int num3 = ntohs(num2);
    printf("num3 : 0x0%x\n", num3);


    return 0;
}
