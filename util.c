#include "util.h"
unsigned char* create_data_from_file(const char *filename) {
    FILE *fp;
    long filesize = get_read_file_size(filename);
    if((fp = fopen(filename, "rb")) == NULL){
        return NULL;
    }
    unsigned char *data = (unsigned char*)malloc(filesize + 1);
    memset(data, 0, filesize);
    fread(data, filesize, 1, fp);
    data[filesize] = '\0';
    fclose(fp);
    return data;
}

void destroy_data(unsigned char *data) {
    free(data);
    return ;
}

long get_read_file_size(const char *in_fname)
{
    FILE *fp;
    long file_size;
    struct stat stbuf;
    int fd;
    fd = open(in_fname, O_RDONLY);
    if (fd == -1)
        printf("a:error");
    fp = fdopen(fd, "rb");
    if (fp == NULL)
        printf("b:error");
    if (fstat(fd, &stbuf) == -1)
        printf("c:error");
    file_size = stbuf.st_size;
    if (fclose(fp) != 0)
        printf("d:error");
    return file_size;
}

int isDelimiter(char p, char delim){
    return p == delim;
}

int split(char *src, const char delim,char *out[]){
    int count = 0;
    while(1){
        while (isDelimiter(*src, delim)){
            src++;
        }
        if (*src == '\0') break;
        out[count++] = src;
        while (*src && !isDelimiter(*src, delim)) {
            src++;
        }
        if (*src == '\0') break;
        *src++ = '\0';
    }
    return count;
}

