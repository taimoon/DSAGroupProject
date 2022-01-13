#define WAREHOUSESYSTEM_H_INCLUDED
#define WAREHOUSESYSTEM_H_INCLUDED
#define BARCODE_MAX_LEN 12
#define PRODUCT_NAME_MAX_LEN 64
#define CATEGORY_NAME_MAX_LEN 16
#define RECEIVER_NAME_MAX_LEN 32
#define DATE_MAX_LEN 12
#define DETAILADDR_MAX_LEN 64
#define STREET_MAX_LEN 32
#define CITY_MAX_LEN 32
#define STATE_MAX_LEN 32
#define POSTCODE_MAX_LEN 11
#define OUTBOUND 0
#define INBOUND 1
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
typedef struct request{
    unsigned int orderID;
    char receiver[RECEIVER_NAME_MAX_LEN];
    char direction;
    char requestDate[DATE_MAX_LEN];
    RequestRow *List;
    float totalPrice;
}request;
typedef struct address{
    char detailedAddr[DETAILADDR_MAX_LEN];
    char street[STREET_MAX_LEN];
    char city[CITY_MAX_LEN];
    char state[STATE_MAX_LEN];
    char postcode[POSTCODE_MAX_LEN];
}address;

struct product InputNewItem ();
struct request InputNewRequest ();
struct address AddressCustomer ();
//pythonic input
void PrintNewItem ();
void PrintNewRequest ();
void PrintAddress ();

product InputNewItem()
{
    struct product product_info;
    input("Enter the barcode of the product: ", "%[^\n]", product_info.barcode);
    input("Enter the name of the product: ", "%[^\n]", product_info.name);
    input("Enter the category of the product: ", "%[^\n]", product_info.category);
    input("Enter the price of the product: ", "%f", &product_info.price);
    return product_info;
};

request InputNewRequest()
{
    struct request newrequest;
    newrequest.direction = OUTBOUND;
    input("Enter the orderID of the request: ", "%u", &newrequest.orderID);
    input("Enter the receiver name of the request: ", "%[^\n]", newrequest.receiver);
    input("Enter the direction of request(0=Outbound/1=INBOUND): ", "%c", &newrequest.direction);
    input("Enter the date of request(DD/MM/YY): ", "%s", newrequest.requestDate);
    return newrequest;
};

address AddressCustomer()
{
    struct address address_customer;
    input("Enter the detail address of the customer address: ", "%[^\n]", address_customer.detailedAddr);
    input("Enter the street of the customer address: ", "%[^\n]", address_customer.street);
    input("Enter the city of the customer address: ", "%[^\n]", address_customer.city);
    input("Enter the postcode of the customer address: ", "%[^\n]", address_customer.postcode);
    input("Enter the state of the customer address: ", "%[^\n]", address_customer.state);
    return address_customer;
}

void PrintNewItem(product product_info)
{
    printf("The barcode of the product: %s\n", product_info.barcode);
    printf("The name of product: %s\n", product_info.name);
    printf("The category of the product: %s\n", product_info.category);
    printf("The price of the product: %.2f\n", product_info.price);
}

void PrintNewRequest(request newrequest)
{
    printf("The orderID of the request: %u\n", newrequest.orderID);
    printf("The receiver name of the request: %s\n", newrequest.receiver);
    if (newrequest.direction == '0')
    {
        printf("The direction of the product: OUTBOUND\n");
    }
    else
    {
        printf("The direction of the product: INBOUND\n");
    }
    printf("The date of request: %s\n", newrequest.requestDate);
}

void PrintAddress(address address_customer)
{
    printf("The address line 1 of the customer address: %s\n", address_customer.detailedAddr);
    printf("The street of the customer address: %s\n", address_customer.street);
    printf("The city of the customer address: %s\n", address_customer.city);
    printf("The postcode of the customer address: %s\n", address_customer.postcode);
    printf("The state of the customer address: %s\n", address_customer.state);
}
#endif // WAREHOUSESYSTEM_H_INCLUDED
