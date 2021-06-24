#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void main(int argc, char **argv){
    char *buf, *result;
    int fd;
    int fileSize;
    if (argc != 2){
        fprintf(stderr, "usage: %s targetfile\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        fprintf(stderr, "open error: %s\n", argv[1]);
        exit(1);
    }

    fileSize = lseek(fd, 0, SEEK_END);
    buf = (char*)malloc(fileSize+1);
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, fileSize);
    buf[fileSize] = '\0';

    result = (char*)malloc(fileSize+1);
    for (int i=0; i<fileSize; i++){
        result[i]=buf[fileSize-i-1];
    }
    result[fileSize]='\0';

    fd = open(argv[1], O_WRONLY);
    write(fd, result, fileSize);

}
