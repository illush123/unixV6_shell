#define BLOCKSIZE 512
#include "inode.h"
#include "string.h"

void read_block(unsigned char* img,int block_num,unsigned char *block_data){
    unsigned char *head = &img[BLOCKSIZE * block_num];
    memcpy(block_data, head, BLOCKSIZE);
}
void print_inode_info(inode_t *inode){
    printf("%c",inode->i_mode & IFDIR ? 'd' : '-');
    printf("%c",inode->i_mode & 0400 ? 'r' : '-');
    printf("%c",inode->i_mode & 0200 ? 'w' : '-');
    printf("%c",inode->i_mode & 0100 ? 'x' : '-');
    printf("%c",inode->i_mode & 040 ? 'r' : '-');
    printf("%c",inode->i_mode & 020 ? 'w' : '-');
    printf("%c",inode->i_mode & 010 ? 'x' : '-');
    printf("%c",inode->i_mode & 04 ? 'r' : '-');
    printf("%c",inode->i_mode & 02 ? 'w' : '-');
    printf("%c",inode->i_mode & 01 ? 'x' : '-');
    printf(" %8d ", inode->i_size1 + (inode->i_size0 << 8));
    
    
    
}

bool read_inode(unsigned char* img,int ino, inode_t *inode){
    if(ino <= 0) return false;
    unsigned char block_data[BLOCKSIZE];
    int block_number = (ino + 31)/ 16; // ブロック番号計算
    read_block(img, block_number, block_data);
    int offset = 32 * ((ino + 31) % 16);
    memcpy(inode, block_data + offset, sizeof(inode_t));
    return true;
}

void debug_inode(inode_t *inode){
    printf("i_nlink = %02x\n",inode->i_nlink);
    printf("i_uid = %02x\n",inode->i_uid);
    printf("i_gid = %02x\n",inode->i_gid);
    printf("\n");
}
