/*
    #include <sys/stat.h>
    int chmod(const char *path, mode_t mode);
        功能： 修改当前用户当/当前用户组/其他用户的文件的权限
        参数：
            - pathname：需要修改的文件的路径
            - mode：需要修改的权限值，需要修改的权限值，8进制数
        返回值：
            - 成功 返回0
            - 失败 返回-1
*/      

#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int ret = chmod("a.txt",0775);
    if (ret == -1){
        perror("chmod");
        return -1;
    }
    return 0;
}
