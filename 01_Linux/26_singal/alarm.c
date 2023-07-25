#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int seconds = alarm(5);
    printf("seconds = %d\n", seconds);//返回0
    sleep(2);
    seconds = alarm(10);
    printf("seconds = %d\n", seconds);//返回3,5-2=3
    for (int i = 1; i <= 10; i++){
        sleep(1);
        printf("过了%d秒\n", i);
    }
    return 0;
}
