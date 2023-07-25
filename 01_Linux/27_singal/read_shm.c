#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
    //1.获取一个共享内存
    int shmid = shmget(100, 0, IPC_CREAT);
    printf("shmid : %d\n", shmid);

    //2.和当前进程进行关联,返回值是共享内存在虚拟地址空间的首地址
    void *ptr = shmat(shmid, NULL, 0);
    
    //3.从共享内存中读取数据
    printf("%s\n", (char *)ptr);

    printf("按下任意键继续\n");
    getchar();
    //4.解除关联
    shmdt(ptr);

    //5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
