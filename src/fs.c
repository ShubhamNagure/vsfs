#include<fs.h>
#include<stdlib.h>
// void create_fs(); //to intialize new FS
// void mount_fs();    // load FS
// void sync_fs();     //write the FS

struct superblock sb;
struct inodes *inodes; //pointer variable to point to blocks
struct disk_block *dbs; 

//to initilaize new Fs
void create_fs(){
    sb.num_inodes=10;
    sb.num_blocks=100;
    sb.size_blocks=sizeof(struct disk_block); 

    //setup inodes and disk blocks
    int i;
    inodes= malloc(sizeof ( struct inodes )* sb.num_inodes); //inodes
    for (i=0; i< sb.num_inodes; i++)
    {
        inodes[i].size=-1;
        inodes[i].name="";

    } //init inodes

    dbs=malloc(sizeof(struct disk_blocks)* sb.num_blocks); //disk block 
    for (i=0; i< sb.num_blocks; i++)
    {
        inodes[i].next_block_num=-1;
        

    }

}