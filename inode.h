#ifndef inode_h
#define inode_h

#include <stdio.h>
#include <stdbool.h>

#define BLOCKSIZE 512

#define IALLOC 0100000 
#define IFMT   060000
#define IFDIR  040000
#define IFCHR  020000
#define IFBLK  060000
#define ILARG  010000
#define ISUID  04000
#define ISGID  02000
#define ISVTX  01000
#define IREAD  0400
#define IWRITE 0200
#define IEXEC  0100


typedef struct {
    unsigned short i_mode;
    char i_nlink;
    char i_uid;
    char i_gid;
    unsigned char i_size0;
    unsigned short i_size1;
    unsigned short i_addr[8]; //block number
    unsigned short i_atime[2];
    unsigned short i_mtime[2];
} inode_t;

typedef struct {
    unsigned short ino;
    char name[14];
} dir_t;

bool read_inode(unsigned char* img,int ino, inode_t *inode);
void debug_inode(inode_t *inode);
void read_block(unsigned char* img,int block_num,unsigned char *block_data);
void print_inode_info(inode_t *inode);
#endif /* inode_h */
