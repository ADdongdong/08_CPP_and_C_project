#include <stdio.h>

int main(int argc, char const *argv[])
{
    int ret = rename("aaa", "bbb");
    if (ret == -1){
        perror("rename");
        return -1;
    }
    
    return 0;
}
