//this is header file for FS.

/*meta information about File system 
1. no of inodes 
2.no of disk blocks
3.size of the disk blocks
 */
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
    char data[512];

};

// operation

void create_fs(); //to intialize new FS
void mount_fs();    // load FS
void sync_fs();     //write the FS
void print_fs();    //to print all the information of FS



