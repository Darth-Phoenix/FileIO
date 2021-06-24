#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void main(int argc, char **argv){
    char *buf;
    int fd_in, fd_out;
    int fileSize;
    if (argc != 3){
        fprintf(stderr, "usage: %s sourceFile targetfile\n", argv[0]);
        exit(1);
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0){
        fprintf(stderr, "open error: %s\n", argv[1]);
        exit(1);
    }

    fileSize = lseek(fd_in, 0, SEEK_END);
    buf = (char*)malloc(fileSize+1);
    lseek(fd_in, 0, SEEK_SET);

    fd_out = open(argv[2], O_CREAT | O_WRONLY, 0600);
    if (fd_out < 0){
        fprintf(stderr, "open error: %s\n", argv[2]);
        exit(1);
    }

    read(fd_in, buf, fileSize);
    buf[fileSize] = '\0';
    write(fd_out, buf, fileSize);
}
