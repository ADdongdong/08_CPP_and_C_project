#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
    //1.创建一个共享内存
    int shmid = shmget(100, 4096, IPC_CREAT|0664);
    printf("shmid: %d\n", shmid);

    //2.和当前进程进行关联,返回值是共享内存在虚拟地址空间的首地址
    void *ptr = shmat(shmid, NULL, 0);

    char * str = "hellowrold";
    //3.写数据
    memcpy(ptr, str, strlen(str) + 1);//+1表示把字符传递的结束符也拷贝过去

    printf("按下任意键继续\n");

    getchar();
    //4.解除关联
    shmdt(ptr);

    //5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
