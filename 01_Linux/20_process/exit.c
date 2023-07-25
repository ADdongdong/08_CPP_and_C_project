#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("hello\n");//有\n会自动刷新缓冲区，所以，能展示出来
    printf("world");//没有\n所以，不会刷新缓冲区，所以，world不会展示出来
    //如果使用c库的exit会刷新缓冲区，就算没有\n也能刷新出来
    //_exit则不能刷新

    //exit执行成功后，return 0就不会执行了
    //exit(0);
    _exit(0);

    return 0;
}
