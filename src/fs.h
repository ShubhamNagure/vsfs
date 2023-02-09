//this is header file for FS.

/*meta information about File system 
1. no of inodes 
2.no of disk blocks
3.size of the disk blocks
 */

#define BLOCKSIZE 512
struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    int size;
    int first_block;
    char name[8];

};

struct disk_block {
    int next_block_num;
    char data[BLOCKSIZE];

};

// operation

void create_fs(); //to intialize new FS
void mount_fs();    // load FS
void sync_fs();     //write the FS
void print_fs();    //to print all the information of FS

//allocate the file to the FS
int allocate_file(char name[8]);
//set filesize
void set_filesize(int filenum,int size);
//write the data to the File
void write_byte(int filenum,int pos,char *data);
//read the data from th file
void read_byte(int filenum,int pos);
//delete the data / delete the file from FS




