#include<stdio.h>
#include<stdlib.h>
/*
    read about C macro
*/
#define COPY_CMD(FILE_NAME, TARGET_FILE) "copy "#FILE_NAME" "#TARGET_FILE
#define retrival
int main()
{
    #ifdef backup
        system(COPY_CMD("Inbound Request List.bin", "Inbound Request List Backup.bin"));
        system(COPY_CMD("Outbound Request List.bin", "Outbound Request List Backup.bin"));
        system(COPY_CMD("Product List.bin", "Product List Backup.bin"));
        system("PAUSE");
    #endif
    #ifdef retrival
        system(COPY_CMD("Inbound Request List Backup.bin", "Inbound Request List.bin"));
        system(COPY_CMD("Outbound Request List Backup.bin", "Outbound Request List.bin"));
        system(COPY_CMD("Product List Backup.bin", "Product List.bin"));
        system("PAUSE");
    #endif
    
    return 0;
}