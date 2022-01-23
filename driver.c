#include<stdio.h>
#include"warehouseSystem.h"
void InvalidInputWarn()
{
    printf("\nInvalid Input, enter any key to proceed: ");
    getchar();fflush(stdin);
}
int main(void)
{
    char InReqFileName[] ="Inbound Request List.bin";
    char OutReqFileName[] ="Outbound Request List.bin";
    node* InRequestList = NULL;
    node* OutRequestList = NULL;
    LoadRequest(&InRequestList, InReqFileName);
    //LoadRequest(&OutRequestList, OutReqFileName);
    char MenuSelInput = 1;
    while(MenuSelInput != 'q')
    {
        printf("WAREHOUSE SYSTEM MANAGEMENT\n"
               "Enter the number to nagvigate\n");
        printf("1)\t View Product List\n"
               "2)\t View Request\n"
               "3)\t Add Product\n"
               "4)\t Edit and Delete Product\n"
               "5)\t Add Request\n"
               "6)\t Fulfil Request\n"
               "q)\t Quit\n"
               );
        product *ProductList = NULL;
        int CurrProdNum = LoadProduct(&ProductList);
        MenuSelInput=getchar();fflush(stdin);
        switch(MenuSelInput)
        {
        case 'q':
            break;
        case '1':
            SortedProduct(ProductList, CurrProdNum);
            PrintAllProductRow(ProductList, CurrProdNum);
            break;
        case '2':
            input("Enter the direction of request(0=Outbound/1=INBOUND): ", "%d", &MenuSelInput);
            if(MenuSelInput==OUTBOUND)
                PrintRequestQueue(OutRequestList);
            else if(MenuSelInput==INBOUND)
                PrintRequestQueue(InRequestList);
            else
                InvalidInputWarn();
            break;
        case '3':
            CurrProdNum=AppendRegisteredProduct();
            break;
        case '4':
            ProductModification(ProductList, &CurrProdNum);
            break;
        case '5':
            input("Enter the direction of request(0=Outbound/1=INBOUND): ", "%d", &MenuSelInput);
            if(MenuSelInput==OUTBOUND)
            {
                enqueue(&OutRequestList, InputNewRequest(OUTBOUND));
                SaveRequest(&OutRequestList, OutReqFileName);
            }
            else if(MenuSelInput==INBOUND)
            {
                enqueue(&InRequestList, InputNewRequest(INBOUND));
                SaveRequest(&InRequestList, InReqFileName);
            }
            else
                InvalidInputWarn();
            break;
        case '6':
            input("Enter the direction of request(0=Outbound/1=INBOUND): ", "%d", &MenuSelInput);
            if(MenuSelInput==OUTBOUND)
            {
                PrintRequest(dequeue(&OutRequestList));
                SaveRequest(&OutRequestList, OutReqFileName);
            }
            else if(MenuSelInput==INBOUND)
            {
                PrintRequest(dequeue(&InRequestList));
                SaveRequest(&InRequestList, InReqFileName);
            }
            else
                InvalidInputWarn();
            break;
        }
    }
}
