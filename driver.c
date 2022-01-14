#include<stdio.h>
#include"warehouseSystem.h"


int main(void)
{

    char filename[]="Product List.bin";
    FileInit(filename);
    request temp = InputNewRequest();
    PrintRequest(temp);
}
