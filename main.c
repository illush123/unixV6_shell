#include <stdio.h>
#include "util.h"
#include "inode.h"


//void command(char *str,unsigned char *img,inode_t *current_node)

void ls(unsigned char *img, inode_t* current_inode,char *option){
    for(int i=0;i<8 && current_inode->i_addr[i] != 0; i++){
        unsigned char storage_block[BLOCKSIZE];
        read_block(img,current_inode->i_addr[i],storage_block);
        size_t offset = 0;
        dir_t *dir;
        while(offset < BLOCKSIZE){
            dir = (dir_t *)&storage_block[offset];
            if(dir->ino == 0) break;
            offset += sizeof(dir_t);
            if(option != NULL){
                if(!strcmp(option,"-l")){
                    inode_t inode;
                    read_inode(img,dir->ino,&inode);
                    print_inode_info(&inode);
                }
            }
            printf("%s\n",dir->name);
        }
    }
}


void cd(unsigned char *img, inode_t *current_inode,char *dir_name){
    for(int i=0;i<8 && current_inode->i_addr[i] != 0; i++){
        unsigned char storage_block[BLOCKSIZE];
        read_block(img,current_inode->i_addr[i],storage_block);
        size_t offset = 0;
        dir_t *dir;
        while(offset < BLOCKSIZE){
            dir = (dir_t *)&storage_block[offset];
            if(dir->ino == 0) break;
            offset += sizeof(dir_t);
            if(!strcmp(dir->name,dir_name)){
                inode_t inode;
                read_inode(img,dir->ino,&inode);
                if((inode.i_mode & IFDIR) == IFDIR) {
                    *current_inode = inode;
                    return;
                }
            }
        }
    }
    printf("no such directory: %s\n",dir_name);
}
int main(int argc, const char * argv[]) {
    unsigned char *img = create_data_from_file("v6root");
    inode_t *current_inode;
    inode_t root;
    read_inode(img, 1, &root);
    current_inode = &root;
    while(1){
        printf("v6sh:");
        char str[64];
        char *commands[2];
        fgets(str,sizeof(str),stdin);
        str[strlen(str) - 1] = ' ';
        split(str, ' ',commands);
        if(!strcmp(str, "exit")) break;
        else if(!strcmp(commands[0], "ls")) {
            ls(img, current_inode,commands[1]);
        }
        else if(!strcmp(commands[0],"cd")){
            cd(img,current_inode,commands[1]);
        }
        else{
            printf("command not found: %s\n",commands[0]);
        }
    }
    destroy_data(img);
    return 0;
}
