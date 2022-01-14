#include<stdio.h>
#include"warehouseSystem.h"
void PrintList(node *li)
{
    if(li == NULL)
        return;
    node *head = li;
    do
    {
        PrintRequest(li->val);
        li=li->next;
        printf("\n");
    }while(li != head);
}
int main(void)
{

    char filename[]="Product List.bin";
    FileInit("Request List.bin");
    FileInit(filename);
    node *requestQueue = NULL;
//    for(int i = 0; i < 1; ++i)
//        enqueue(&requestQueue, InputNewRequest());
//    SaveRequest(&requestQueue);
    LoadRequest(&requestQueue);
    PrintList(requestQueue);
}
