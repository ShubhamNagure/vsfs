#include "fs.h"
#include<stdio.h>
void main()
{
    // create_fs();
   
    mount_fs();
    // allocate_file("firstfi");
    set_filesize(0,1000);
    print_fs();

    set_filesize(0,5000);
    print_fs();

    set_filesize(0,100);
    print_fs();

    sync_fs();
    printf("done\n");

}//main





