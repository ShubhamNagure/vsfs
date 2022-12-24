#include "fs.h"
#include<stdio.h>
void main()
{
    // create_fs();
   
    mount_fs();
    // int file=allocate_file("file");
    // set_filesize(file,100);
   
    print_fs();
    // int i;
    // char data='j';
    // for ( i = 0; i <49; i++){
    //     write_byte(file ,i*100,&data);

    // }
    //to read the data
    //  printf("file%d",file);
    sync_fs();
    // read_byte(1);
    printf("done\n");

}//main





