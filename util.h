#ifndef util_h
#define util_h
#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
unsigned char *create_data_from_file(const char *filename);
void destroy_data(unsigned char *data);
long get_read_file_size(const char *in_fname);
int split(char *str,const char delim,char *outlist[]);
#endif /* util_h */
