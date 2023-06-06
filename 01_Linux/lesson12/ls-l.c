#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
//-rwxrwxr-x 1 headong headong 8520 6月   6 08:50 a.out

int main(int argc, char *argv[]){
    struct stat statbuf;
    //1、判断输入的参数是否正确，并给出提示
    if (argc<1){
        printf("%s filename\n", argv[0]);
        return -1;
    }

    //2、通过stat获取文件传入的信息
    int ret = stat(argv[1], &statbuf);
    if (ret == -1 ){
        perror("stat");
        return -1;
    }

    //3、获取文件类型和访问权限
    char perms[11] = {0}; //用于保存文件类型和文件权限的字符串

    switch(statbuf.st_mode & __S_IFMT){
        case __S_IFLNK:
            perms[0] = 'l';
            break;
        case __S_IFDIR:
            perms[0] = 'd';
            break;
        case __S_IFREG:
            perms[0] = '-';
            break;
        case __S_IFBLK:
            perms[0] = 'b';
            break;        
        case __S_IFCHR:
            perms[0] = 'c';
            break;
        case __S_IFIFO:
            perms[0] = 'p';
            break;
        case __S_IFSOCK:
            perms[0] = 's';
            break;
        default:
            perms[0] = '?';
            break;
    }
    // 判断文件的访问权限
    //文件的所有者
    perms[1] = (statbuf.st_mode & S_IRUSR)? 'r' : '-';
    perms[2] = (statbuf.st_mode & S_IWUSR)? 'w' : '-';
    perms[3] = (statbuf.st_mode & S_IXUSR)? 'x' : '-';

    //文件所在组
    perms[4] = (statbuf.st_mode & S_IRGRP)? 'r' : '-';
    perms[5] = (statbuf.st_mode & S_IWGRP)? 'w' : '-';
    perms[6] = (statbuf.st_mode & S_IXGRP)? 'x' : '-';

    //其他呀用户
    perms[7] = (statbuf.st_mode & S_IROTH)? 'r' : '-';
    perms[8] = (statbuf.st_mode & S_IWOTH)? 'w' : '-';
    perms[9] = (statbuf.st_mode & S_IXOTH)? 'x' : '-';
    
    //硬链接数
    int linknum = statbuf.st_nlink;

    //文件所有者
    char *fileusr = getpwuid(statbuf.st_uid)->pw_name;

    //文件所有组
    //getgrgid返回的是一个指向结构体的指针
    char *fileGrp = getgrgid(statbuf.st_gid)->gr_name;

    //文件大小
    long int fileSize = statbuf.st_size;

    //获取修改的时间
    char * time = ctime(&statbuf.st_mtime);
    char mtime[512] = {0};
    strncpy(mtime, time, strlen(time) -1);

    char buf[1024];
    sprintf(buf, "%s %d %s %s %ld %s %s \n", perms, linknum, fileusr,fileGrp, fileSize, mtime, argv[1]);

    printf("%s\n", buf);
    return 0;
}