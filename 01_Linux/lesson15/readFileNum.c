/*
    #include <sys/types.h>
    #include <dirent.h>

    DIR *opendir(const char *name);
    功能：打开一个目录
    参数：
        -name 需要打开目录的名称
    返回值：
        DIR * 类型：理解为目录
        错误返回NULL


    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
    功能：读取目录中的数据
    参数：
        -dirp 是opendir()函数返回的结果
    返回值：
        -成功： 返回struct dirent 代表读取到的文件的信息
        -失败： 读取到末尾或失败，返回NULL
                如果失败errno会被设置，读到末尾errno不会被设置。

    sturct dirent{
        //此目录进入点的inode
        ino_t d_ino;
        //目录文件开头到此目录进入点的位移
        off_t d_off;
        //d_name的长度，不包含NULL字符
        unsigned short int d_recled;
        //d_name 所指的文件类型
        unsingned char d_type;
        //文件名
        char d_name[256];
    };

    #include <sys/types.h>
    #include <dirent.h>

    int closedir(DIR *dirp);
    功能：关闭dir
*/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int getFileNum(const char*);

//读取某个目录下所有普通文件的个数
int main(int argc, char const *argv[])
{
    //./z.out lesson15
    //判断是否正常传入参数
    if (argc < 2){
        printf("请按正确的格式输入:%s path\n", argv[0]);
        return -1;
    }

    int result = getFileNum(argv[1]);

    printf("%s中普通文件的个数为:%d\n", argv[1], result);
    return 0;
}


//用于获取目录下所有普通文件的个数
int getFileNum(const char* path){
    //1.打开目录
    DIR *dir = opendir(path);
    if (dir==NULL){
        perror("opendir");
        return -1;
    }

    struct dirent *ptr;

    //记录普通文件的个数
    int total = 0;
    while ((ptr = readdir(dir)) != NULL){
        // 获取名称，如果是.和..忽略掉
        char * dname = ptr->d_name;
        

        //忽略掉.和..
        if (strcmp(dname, ".")==0 || strcmp(dname, "..")==0){
            continue;
        }
        
        //判断是普通文件还是目录
        if(ptr->d_type == DT_DIR){
            //目录,需要继续这个目录
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getFileNum(newpath);
        }

        if (ptr->d_type == DT_REG){
            total++;
        }
    }
    
    close(dir);
    return total;
}