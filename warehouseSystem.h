#ifndef WAREHOUSESYSTEM_H_INCLUDED
#define WAREHOUSESYSTEM_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Sort Algorithm.h"
#define BARCODE_MAX_LEN 16
#define PRODUCT_NAME_MAX_LEN 64
#define CATEGORY_NAME_MAX_LEN 32
#define RECEIVER_NAME_MAX_LEN 32
#define DATE_MAX_LEN 12
#define DETAILADDR_MAX_LEN 64
#define STREET_MAX_LEN 32
#define CITY_MAX_LEN 32
#define STATE_MAX_LEN 32
#define POSTCODE_MAX_LEN 16
#define OUTBOUND 0
#define INBOUND 1
//Defining pythonic input
void input(char *prompt, char *format, void* target){
    printf(prompt);
    scanf(format, target);
    fflush(stdin);
}
typedef struct product{
    char barcode[BARCODE_MAX_LEN];
    char name[PRODUCT_NAME_MAX_LEN];
    char category[CATEGORY_NAME_MAX_LEN];
    float price;
}product;
typedef struct RequestRow{
    product self;
    unsigned int qty;
}RequestRow;
//RequestRow will be using the dynamic array
typedef RequestRow ArrT;
#include "C Dynamic Array.h"
//Note that the array here is the array of RequestRow Datatype
typedef struct address{
    char DetailAddr[DETAILADDR_MAX_LEN];
    char street[STREET_MAX_LEN];
    char city[CITY_MAX_LEN];
    char state[STATE_MAX_LEN];
    char postcode[POSTCODE_MAX_LEN];
}address;
typedef struct request{
    unsigned int orderID;
    char receiver[RECEIVER_NAME_MAX_LEN];
    char direction;
    char requestDate[DATE_MAX_LEN];
    array requestList;
    float totalPrice;
    address target;
}request;
//rquest will be using the linked list
typedef request T;
#include "Cir_List.h"
//Define queue structure from circular list after including the circular list
void enqueue(node** queue, request instance)
{
    pushBack(queue, instance);
}
request dequeue(node ** queue)
{
    return popFront(queue);
}
product RegisterNewProduct();
int AppendRegisteredProduct();
request InputNewRequest(char direction);
address InputAddressCustomer();
void InputRequestList(array *CurrList);
double CalTotalPrice(array *CurrList);
void PrintProduct(product product_info);
void PrintRequest(request instance);
void PrintAddress(address address_customer);
void PrintRequestQueue(node *q);
void PrintAllProductRow(product *ProductList, int len);

///File Handling Module
int GetRecordSize(char *filename, size_t elemSize);
void FileInit(char *filename);
void FileLoadSeq(char *filename, void* seq, size_t elemSize);
void FileSaveSeq(char *filename, int length, void *seq, size_t elemSize);
void SaveProduct(product *arr, size_t length);
int LoadProduct(product **arr);
void LoadRequest(node** instance, char *filename);
void SaveRequest(node** instance, char *filename);

product RegisterNewProduct()
{
    struct product product_info;
    input("Enter the barcode of the product: ", "%[^\n]s", product_info.barcode);
    input("Enter the name of the product: ", "%[^\n]s", product_info.name);
    input("Enter the category of the product: ", "%[^\n]s", product_info.category);
    input("Enter the price of the product: ", "%f", &product_info.price);
    return product_info;
};
product InputEditedProduct(product instance)
{
    struct product product_info=instance;
    input("Enter the barcode of the product: ", "%[^\n]s", product_info.barcode);
    input("Enter the name of the product: ", "%[^\n]s", product_info.name);
    input("Enter the category of the product: ", "%[^\n]s", product_info.category);
    input("Enter the price of the product(enter -1 if you're not intended to change): ", "%f", &product_info.price);
    if(product_info.barcode[0] != '\n')
        strcpy(instance.barcode,product_info.barcode);
    if(product_info.name[0] != '\n')
        strcpy(instance.name,product_info.name);
    if(product_info.category[0] != '\n')
        strcpy(instance.category,product_info.category);
    if(product_info.price > 0)
        instance.price = product_info.price;
    return instance;
}
int AppendRegisteredProduct()
{
    char filename[]="Product List.bin";
    FileInit(filename);
    product *ProductList = NULL;
    int len = LoadProduct(&ProductList);
    int CurrLen = len;
    if(len == 0)
        len = 2;
    else
        len = len*2;
    ProductList=(product *)realloc(ProductList, len*sizeof(product));
    int UserInput = 1;
    input("Enter 1 to continue input, or any key to stop", "%d", &UserInput);
    while(UserInput == 1 && CurrLen < len*2)
    {
        ProductList[CurrLen] = RegisterNewProduct();
        ++CurrLen;
        input("Enter 1 to continue input, or any key to stop", "%d", &UserInput);
    }
    SaveProduct(ProductList, CurrLen);
    free(ProductList);
    return CurrLen;
}
request InputNewRequest(char direction)
{
    struct request newrequest;
    newrequest.requestList=array_init;
    newrequest.direction = direction;
    input("Enter the orderID of the request: ", "%u", &newrequest.orderID);
    input("Enter the receiver name of the request: ", "%[^\n]s", newrequest.receiver);
    input("Enter the date of request(DD/MM/YY): ", "%s", newrequest.requestDate);
    InputRequestList(&newrequest.requestList);
    newrequest.totalPrice = CalTotalPrice(&newrequest.requestList);
    return newrequest;
};
address InputAddressCustomer()
{
    struct address address_customer;
    input("Enter the detail address of the customer address: ", "%[^\n]s", address_customer.DetailAddr);
    input("Enter the street of the customer address: ", "%[^\n]s", address_customer.street);
    input("Enter the city of the customer address: ", "%[^\n]s", address_customer.city);
    input("Enter the postcode of the customer address: ", "%[^\n]s", address_customer.postcode);
    input("Enter the state of the customer address: ", "%[^\n]s", address_customer.state);
    return address_customer;
}
int ProductBarcodeComp(const void*  a, const void* b)
{
    return strcmp((*(product *)a).barcode, (*(product *)b).barcode);
}
int ProductNameComp(const void*  a, const void* b)
{
    return strcmp((*(product *)a).name, (*(product *)b).name);
}
int ProductCategoryComp(const void*  a, const void* b)
{
    return strcmp((*(product *)a).category, (*(product *)b).category);
}
int ProductPriceComp(const void*  a, const void* b)
{
    if((*(product *)a).price==(*(product *)b).price)
        return 0;
    else if((*(product *)a).price > (*(product *)b).price)
        return 1;
    else
        return -1;
}
void InputRequestList(array *CurrList)
{
    int UserInput = 1;
    char barcode[BARCODE_MAX_LEN];
    product *ProductList = NULL;
    int len = LoadProduct(&ProductList);
    while(UserInput)
    {
        QuickSort(ProductList, len, sizeof(product), ProductBarcodeComp);
        PrintAllProductRow(ProductList, len);
        input("Enter the barcode of product you wish to request: ", "%[^\n]s",&barcode);
        int idx= BinarySearch(barcode, ProductList, len, sizeof(product), ProductBarcodeComp);
        if(idx!=-1)
        {
            RequestRow temp;
            PrintProduct(ProductList[idx]);
            temp.self =  ProductList[idx];
            input("Enter the quantity: ", "%d", &temp.qty);
            pushBackArr(temp, CurrList);
        }
        else
            printf("The barcode is not recorded in the system\n");
        input("Enter 1 if you wish to continue, or enter any key otherwise: ", "%d", &UserInput);
    }
}
double CalTotalPrice(array *CurrList)
{
    double sum = 0;
    for(int i = CurrList->front; i < CurrList->currSize;++i)
    {
        sum += CurrList->arrPtr[i].qty*CurrList->arrPtr[i].self.price;
    }
    return sum;
}
void UpdateRequestList(node **li)
{
    if(*li == NULL)
        return;
    node *head = *li;
    node *curr = *li;
    do
    {
        curr->val.totalPrice = CalTotalPrice(&(curr->val.requestList));
        curr = curr->next;
    }while(curr != head);
}
void SortedProduct(product *ProductList, int len)
{
    int UserInput = 0;
    printf("\nView sorted product List based on\n"
           "1)\t Barcode\n"
           "2)\t Name\n"
           "3)\t Category\n"
           "4)\t Price\n");
    input("Enter the number: ", "%d", &UserInput);
    switch(UserInput)
    {
    case 1:
        QuickSort(ProductList, len, sizeof(product), ProductBarcodeComp);
        break;
    case 2:
        QuickSort(ProductList, len, sizeof(product), ProductNameComp);
        break;
    case 3:
        QuickSort(ProductList, len, sizeof(product), ProductCategoryComp);
        break;
    case 4:
        QuickSort(ProductList, len, sizeof(product), ProductPriceComp);
        break;
    }
}
void PrintProduct(product product_info)
{
    printf("Barcode: %s\n", product_info.barcode);
    printf("Product: %s\n", product_info.name);
    printf("Category: %s\n", product_info.category);
    printf("Price: %.2f\n", product_info.price);
}
void PrintAllProductGiven(product arr[], size_t len)
{
    for(size_t i = 0; i < len; ++i)
    {
        printf("%d\n", i);
        PrintProduct(arr[i]);
        printf("\n");
    }
}
void PrintAllProduct()
{
    product *ProductList=NULL;
    int len = LoadProduct(&ProductList);
    for(size_t i = 0; i < len; ++i)
    {
        printf("%d\n", i);
        PrintProduct(ProductList[i]);
        printf("\n");
    }
    free(ProductList);
}
void PrintProductRow(product product_info)
{
    printf("%s\t\t%s\t%s\t%.2f", product_info.barcode, product_info.name, product_info.category, product_info.price);
}
void PrintAllProductRow(product *ProductList, int len)
{
    printf("No\tBarcode\t\tProduct Name\t\tCategory\tPrice(RM)\n");
    for(size_t i = 0; i < len; ++i)
    {
        printf("%d\t", i+1);
        PrintProductRow(ProductList[i]);
        printf("\n");
    }
}
void PrintRequestRow(array instance)
{
    int j = 1;
    for(int i = instance.front; i < instance.currSize; ++i, ++j)
    {
        printf("%d\t%s\t%s\t%.2f\t%d\n",
               j,
               instance.arrPtr[i].self.barcode,
               instance.arrPtr[i].self.name,
               instance.arrPtr[i].self.price,
               instance.arrPtr[i].qty
               );
    }
}
void PrintRequest(request instance)
{
    printf("The orderID of the request: %u\n", instance.orderID);
    printf("The receiver name of the request: %s\n", instance.receiver);
    printf("The direction of the product:");
    if (instance.direction == '0')
        printf("OUTBOUND\n");
    else
        printf("INBOUND\n");
    printf("The date of request: %s\n", instance.requestDate);
    printf("No\tProduct\tName\tPrice\tQty\n");
    PrintRequestRow(instance.requestList);
    printf("Total Price: RM %.2f\n", instance.totalPrice);

}
void PrintAddress(address address_customer)
{
    printf("The address line 1: %s\n", address_customer.DetailAddr);
    printf("Street: %s\n", address_customer.street);
    printf("City: %s\n", address_customer.city);
    printf("Postcode: %s\n", address_customer.postcode);
    printf("State: %s\n", address_customer.state);
}
void PrintRequestQueue(node *q)
{
    if(q == NULL)
        return;
    int idx = 0;
    node *head = q;
    do
    {
        ++idx;
        printf("\n%d\n", idx);
        PrintRequest(q->val);
        q=q->next;
        printf("\n");
    }while(q != head);
}
void ProductModification(product *ProductList, int *len)
{
    system("CLS");
    char UserInput = 0;
    int idx = 0;
    SortedProduct(ProductList, *len);
    PrintAllProductRow(ProductList, *len);
    input("\nInput the number of the product:", "%d", &idx);
    idx = idx-1;
    PrintProduct(ProductList[idx]);
    input("\ne)\t Edit"
          "\nd)\t Delete"
          "\nq)\t Quit\n", "%c", &UserInput);
    switch(UserInput)
    {
    case 'e':
        printf("Enter the change if you wish, otherwise left it blank\n");
        ProductList[idx]=InputEditedProduct(ProductList[idx]);
        SaveProduct(ProductList, *len);
        break;
    case 'd':
        for(int i = idx; i < *len;++i)
            ProductList[idx]=ProductList[idx+1];
        *len -= 1;
        SaveProduct(ProductList, *len);
        break;
    }
}
void FileInit(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    if(fp == 0)
    {
        printf("Cannot open the file, then a new file is created : %s\n", filename);
        fp = fopen(filename, "wb");
    }
    fclose(fp);
}
int GetRecordSize(char *filename, size_t elemSize)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {
        fclose(fp);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long lSize = ftell(fp);
    fclose(fp);
    return lSize/elemSize;
}
void FileLoadSeq(char *filename, void* seq, size_t elemSize)
{
    FILE *fp;
    fp = fopen(filename,"rb");
    fread(seq, elemSize, GetRecordSize(filename, elemSize), fp);
    fclose(fp);
};
void FileSaveSeq(char *filename, int length, void *seq, size_t elemSize)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    fwrite(seq, elemSize, length, fp);
    fclose(fp);
}
int LoadProduct(product **arr)
{
    char filename[]="Product List.bin";
    int CurrLen = GetRecordSize(filename, sizeof(product));
    *arr=NULL;
    if(CurrLen != 0)
    {
            *arr=(product *)malloc(CurrLen*sizeof(product));
            FileLoadSeq(filename, *arr, sizeof(product));
        }
    return CurrLen;
}
void SaveProduct(product *arr, size_t length)
{
    char filename[]="Product List.bin";
    FileInit(filename);
    FileSaveSeq(filename, length, arr, sizeof(product));
}
void SaveRequest(node** instance, char *filename)
{
    FileInit(filename);
    FILE *fp;
    fp = fopen(filename,"wb");
    node* curr = *instance;
    node* head = *instance;
    int CurrLen = getLen(*instance);
    fwrite(&CurrLen, sizeof(int), 1, fp);
    if(*instance == NULL)
        return;
    do
    {
        fwrite(&(curr->val), sizeof(request), 1, fp);
        fwrite(&(curr->val.requestList.arrPtr[curr->val.requestList.front]),
              sizeof(ArrT), curr->val.requestList.currSize, fp);
        curr = curr->next;
    }while(curr != head);
    fclose(fp);
}
void LoadRequest(node** instance, char *filename)
{
    destoryList(instance);
    FILE *fp;
    fp = fopen(filename,"rb");
    int RecordSize = 0;
    fread(&RecordSize, sizeof(int), 1, fp);
    for(int i = 0; i < RecordSize; ++i)
    {
        request temp;

        fread(&(temp), sizeof(request), 1, fp);
        temp.requestList.currSize -= temp.requestList.front;
        temp.requestList.front = 0;
        temp.requestList.maxSize=temp.requestList.currSize;
        temp.requestList.arrPtr = initialiseArray(temp.requestList.maxSize, sizeof(ArrT));
        fread(temp.requestList.arrPtr,
              sizeof(ArrT), temp.requestList.currSize, fp);
        pushBack(instance, temp);
    }
    fclose(fp);
}
#endif // WAREHOUSESYSTEM_H_INCLUDED
