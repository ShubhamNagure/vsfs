#include "fs.h"
#include<stdio.h>
void main()
{
    // create_fs();
   
    mount_fs();
    int file=allocate_file("another");
    set_filesize(file,5000);
    print_fs();
    int i;
    char data='b';
    for ( i = 0; i <49; i++){
        write_byte(file ,i*100,&data);

    }
    sync_fs();
    printf("done\n");

}//main





