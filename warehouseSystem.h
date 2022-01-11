#ifndef WAREHOUSESYSTEM_H_INCLUDED
#define WAREHOUSESYSTEM_H_INCLUDED
const char BARCODE_MAX_LEN = 12;
const char PRODUCT_NAME_MAX_LEN = 64;
const char CATEGORY_NAME_MAX_LEN = 16;
const char RECEIVER_NAME_MAX_LEN = 32;

typedef struct product{
    char barcode[BARCODE_MAX_LEN];
    char name[PRODUCT_NAME_MAX_LEN];
    char category[CATEGORY_NAME_MAX_LEN];
}product;
typedef struct request{
    unsigned int orderID;
    char receiver[RECEIVER_NAME_MAX_LEN];
    char direction;
    product *List;
}request;
typedef struct



#endif // WAREHOUSESYSTEM_H_INCLUDED
