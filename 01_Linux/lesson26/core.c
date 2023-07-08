#include <stdio.h>
#include <string.h>

int main(){
    char *buf;//指针没有初始化，是个野指针

    strcpy(buf, "hello");
     
    return 0;
}