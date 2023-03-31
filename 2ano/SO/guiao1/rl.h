#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 4096

//#define MAX_READ_BUFFER 2048
//char raed_buffer[MAX_READ_BUFFER];
//int read_buffer_pos = 0;
//int read_buffer_end = 0;
//int read_buffer_end;

ssize_t readln(int fd, char* buf, size_t size);
int readc(int fd, char* c);
