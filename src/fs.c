#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fs.h"

// void create_fs(); //to intialize new FS
// void mount_fs();    // load FS
// void sync_fs();     //write the FS

struct superblock sb;
struct inode *inodes; //pointer variable to point to blocks
struct disk_block *dbs; 

//to initilaize new Fs
void create_fs(){
    sb.num_inodes=10;
    sb.num_blocks=100;
    sb.size_blocks=sizeof(struct disk_block); 

    //setup inodes and disk blocks
    int i;
    inodes= malloc(sizeof ( struct inode)* sb.num_inodes); //inodes
    for (i=0; i< sb.num_inodes; i++)
    {
        inodes[i].size=-1;
        strcpy(inodes[i].name,"makefile");

    } //init inodes

    dbs=malloc(sizeof (struct disk_block)* sb.num_blocks); //disk block 
    /*what we want is that allocate the space for the disk so to achieve 
    that we malloc() and in that we cal the size of the disk block struct which 
    is multiple by the number of the blocks that are associated for the data block by 
    superblock
    */
    for (i=0; i< sb.num_blocks; i++) 
    {
          dbs[i].next_block_num=-1;
    }//init dbs
    


}// create fs

//load the Fs for that we have to mount it.
void mount_fs(){

     
} 


//to write something into Fs we need to sync Fs
void sync_fs(){
    FILE *file;
    file=fopen("fs_data","w+");

    //superblock
    fwrite(&sb, sizeof(struct superblock),1,file);

    //inodes 
    int i;
    for (i=0; i< sb.num_inodes; i++)
    {
        fwrite(&(inodes[i]), sizeof(struct inode),1,file);
        

    } //write inodes
    

    for (i=0; i< sb.num_blocks ; i++)
    {
        fwrite(&(dbs[i]), sizeof(struct disk_block),1,file);
        

    }//write data_blocks
    fclose(file);
}//sync_fs 

