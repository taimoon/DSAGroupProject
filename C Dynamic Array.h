#ifndef C_DYNAMIC_ARRAY_H_INCLUDED
#define C_DYNAMIC_ARRAY_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
//print character after each is printed in printArr
///implement dynamic array like the vector of STL C++. It grows and shrinks automatically.

struct array{
    ArrT *arrPtr;
    int front;
    int currSize;
    int maxSize;
};
typedef struct array array;
array array_init = {NULL, 0, 0, 0};
int getLenArr(array arr){
    if(arr.arrPtr != NULL)
        return arr.currSize-arr.front+1;
    return 0;
}
ArrT* getElem(array arr, int pos){
    if(pos < 0 || pos >= getLenArr(arr)-1)
        exit(EXIT_FAILURE);
    else
        return &(arr.arrPtr[arr.front+pos]);
}
ArrT* initialiseArray(int len, size_t dataSize){
    return malloc(len*dataSize);
}
void constructDynamicArray(array *arr){
    if(arr->arrPtr == NULL){
        if(arr->arrPtr != NULL)
            free(arr->arrPtr);
        arr->arrPtr = initialiseArray(2, sizeof(ArrT));
        arr->front = 0;
        arr->currSize = 0;
        arr->maxSize = 2;
    }
}
//arr1 = arr2
void copyArray(ArrT arr1[], ArrT arr2[], int len){
    for(int i = 0; i < len; ++i)
        arr1[i] = arr2[i];
}
void shrinkArray(array *arr){
    if(arr->arrPtr == NULL)
        return;
    int currLen = getLenArr(*arr);
    if(currLen != 0 && currLen*2 < arr->maxSize){
        if(arr->maxSize/2 > 0){
            ArrT *newArr = initialiseArray(arr->maxSize/2, sizeof(ArrT));
            copyArray(newArr, &(arr->arrPtr[arr->front]), currLen);
            arr->currSize = currLen-1;
            arr->front = 0;
            arr->maxSize /= 2;
            free(arr->arrPtr);
            arr->arrPtr = newArr;
        }
    }else if(currLen == 0 && arr->arrPtr != NULL){
            free(arr->arrPtr);
            *arr = array_init;
    }
}
void growArray(array *arr){
    int currLen = getLenArr(*arr);
    if(arr->maxSize == 0)
        constructDynamicArray(arr);
    else if (currLen+1 >= arr->maxSize){
        ArrT *newArr = initialiseArray(arr->maxSize*2, sizeof(ArrT));
        copyArray(newArr, &(arr->arrPtr[arr->front]), currLen);
        arr->currSize = currLen-1;
        arr->front = 0;
        arr->maxSize *= 2;
        free(arr->arrPtr);
        arr->arrPtr = newArr;
    }
}


///end of dynamic array
/**
    we use the same array data structure for stack and queue
    The difference is on removing.
    removing a stack is removing the most recent added
    removing a queue is removing the least recent added.
**/
void pushBackArr(ArrT data, array *stack){
    shrinkArray(stack);
    growArray(stack);
    stack->arrPtr[stack->currSize] = data;
    stack->currSize += 1;
}
ArrT popBackArr(array *stack){
    if(stack->currSize == 0)
    {
        printf("Popping Empty Container");
        exit(EXIT_FAILURE);
    }
    stack->currSize -= 1;
    ArrT top = stack->arrPtr[stack->currSize];
    shrinkArray(stack);
    return top;
}
void enqueueArr(ArrT data, array *q){
    pushBackArr(data, q);
}
ArrT arrayPopFront(array *q){
    ArrT front = q->arrPtr[q->front];
    q->front += 1;
    shrinkArray(q);
    return front;
}

#endif // C_DYNAMIC_ARRAY_H_INCLUDED
