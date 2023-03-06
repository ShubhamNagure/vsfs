#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fs.h"

// void create_fs();        //to intialize new FS
// void mount_fs();      // load FS
// void sync_fs();      //write the FS

struct superblock sb;
struct inode *inodes; //pointer variable to point to blocks
struct disk_block *dbs; 

//compailer to know about internal functions
//find an empty inode
int find_empty_inode(){
    int i;
    for(i=0;i<sb.num_inodes;i++){
        if(inodes[i].first_block==-1){
        return i;
        }
    }
    return -1;
}
//find and empty disk block
int find_empty_block(){
int i;
    for(i=0;i<sb.num_blocks;i++){
        if(dbs[i].next_block_num==-1){
        return i;
        }
    }
    return -1;
}

//to shorten a file
void shorten_file(int bn){
    int nn=dbs[bn].next_block_num;
    if (nn>=0)
    {
        shorten_file(nn);
    }
    dbs[bn].next_block_num=-1;
}

//get block number
int get_block_num(int file,int offset){
    int togo=offset;
    int bn=inodes[file].first_block;
    while(togo>0){
        bn=dbs[bn].next_block_num;
        togo--;
    }
    return bn;
}
//to initilaize new Fs
void create_fs(){
    sb.num_inodes=10;
    sb.num_blocks=100;
    sb.size_blocks=sizeof(struct disk_block); 

    //setup inodes and disk blocks
    int i;
    inodes= malloc(sizeof ( struct inode)* sb.num_inodes); //inodes

    //init inodes
    for (i=0; i< sb.num_inodes; i++)
    {
        inodes[i].size=-1;
        inodes[i].first_block=-1;
        strcpy(inodes[i].name,"");
    } 

    dbs=malloc(sizeof (struct disk_block)* sb.num_blocks); //disk block 
    /*what we want is that allocate the space for the disk so to achieve 
    that we malloc() and in that we cal the size of the disk block struct which 
    is multiple by the number of the blocks that are associated for the data block by 
    superblock
    */
    //init dbs
    for (i=0; i< sb.num_blocks; i++){
        dbs[i].next_block_num=-1;
    }
}// create fs


//load the Fs for that we have to mount it.
void mount_fs(){
    FILE *file;
    
    file=fopen("fs_data","r");
    //superblock
    fread(&sb, sizeof(struct superblock),1,file);
    inodes= malloc(sizeof ( struct inode)* sb.num_inodes); //inodes
    dbs=malloc(sizeof (struct disk_block)* sb.num_blocks); //disk block 
    //inodes 
    fread(inodes, sizeof(struct inode),sb.num_inodes,file);
    //disk blocks
    fread(dbs, sizeof(struct disk_block),sb.num_blocks,file);
    fclose(file);
     
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
}

// sync_fs
// print out info about the FS
void print_fs(){

    printf("Superblock info\n");
    printf("\t num inodes %d\n",sb.num_inodes);
    printf("\t num blocks %d\n",sb.num_blocks);
    printf("\t size of block %d\n",sb.size_blocks);

    printf("inodes\n");
    //setup inodes and disk blocks
    int i;
    for (i=0; i< sb.num_inodes; i++)
    {
        printf("\t Size: %d block: %d  name: %s\n",inodes[i].size,inodes[i].first_block,inodes[i].name);

    } //init inodes
    for (i=0; i< sb.num_blocks; i++) 
    {
        printf("\t block num :%d next block:%d\n",i,dbs[i].next_block_num);   
    }//init dbs
    
}//print fs

//allocation of the File
int allocate_file(char name[8])
{
    //find an empty inode
    int empty_inode=find_empty_inode();

    //find an empty disk block
    int empty_block=find_empty_block();

    //claim them
    inodes[empty_inode].first_block=empty_block;
    dbs[empty_block].next_block_num=-2;

    //to fix the 'emptyfile' name issue for inode
    strcpy(inodes[empty_inode].name,name);

    //return the file descriptor
    return empty_inode;

    
}
//set_filesize and add or delete blocks
void set_filesize(int filenum, int size)
{
    //how many block should we have
    int tmp=size+BLOCKSIZE-1;
    int num=tmp/BLOCKSIZE;
    int bn=inodes[filenum].first_block;
    num--;
    //to grow the file is neccessary
    while(num>0){
        //check next block number
        int next_num=dbs[bn].next_block_num;
        if(next_num==-2){
            int empty= find_empty_block(); //it will find the empty block 
            dbs[bn].next_block_num=empty; 
            dbs[empty].next_block_num=-2;
                // at each itratiion each block dbs[] of that
                // file will point to the block which is empty
                //the next_block_num of the current block is -2 
                
                //that loop will till num>0 if it is 0 then it stop the loop
                //
        }
        bn=dbs[bn].next_block_num;
        num--;
    }

    //shortern if neccessary
    shorten_file(bn);
    dbs[bn].next_block_num=-2;
}

//write byte
void write_byte(int filenum, int pos, char *data)
{
    //cal which block
    int relative_block=pos/BLOCKSIZE;

    //find the block number
    int bn=get_block_num(filenum,relative_block);
    //cal the offset of the block
    int offset=pos%BLOCKSIZE;

    //write the data
    dbs[bn].data[offset]=(*data);

}

//read the data from the file
void read_byte(int filenum, int pos)
{
      FILE *f=fopen("fs_data","r");
    char c;
  //loop for each byte to the end
  {
    size_t fread(&c, (size_t)1, (size_t) 1, f);
    array[c]++;
  }
}




