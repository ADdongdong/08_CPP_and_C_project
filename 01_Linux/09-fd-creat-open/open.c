#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd = open("a.out", O_RDONLY);
	if (fd == -1){
		perror("a.out");
		return -1;
	}
	close(fd);
	return 0;
}
