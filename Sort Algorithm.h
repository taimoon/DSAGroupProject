#ifndef SORT_ALGORITHM_H_INCLUDED
#define SORT_ALGORITHM_H_INCLUDED

int BinarySearch(const void* key, const void *arr,
                  size_t len, size_t elemSize,
                  int(*cmp)(const void*, const void*));
void QuickSort(void* arr, size_t len, size_t elemSize, int (*cmp)(const void*, const void*));


int BinarySearch(const void* key, const void *arr,
                  size_t len, size_t elemSize,
                  int(*cmp)(const void*, const void*))
{
    int low = 0;
    int high = len-1;
    int mid = (high+low)/2;
    do
    {
        if(cmp(arr+mid*elemSize, key) < 0)
            low = mid+1;
        else if(cmp(arr+mid*elemSize, key) > 0)
            high = mid-1;
        else
            return mid;
        mid = (high+low)/2;
    }while(low <= high);
    return -1;
}
void Swap(void *a, void *b, size_t size){
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}
//arr[l..r]
int Partition(void* arr, int l, int r, size_t elemSize, int (*cmp)(const void*, const void*)){
    int i = l-1;
    void *pivot = arr+r*elemSize;//int pivot = arr[r];
    for(int j = l; j < r; ++j)
        if(cmp(arr+j*elemSize, pivot) <= 0)//if(arr[j] <= pivot)
            Swap(arr+elemSize*++i, arr+j*elemSize, elemSize);//swapping(&arr[++i], &arr[j]);
    Swap(arr+elemSize*++i, arr+r*elemSize, elemSize);//swapping(&arr[i+1], &arr[r]);
    return i;
}
void QuickSortRecur(void* arr, int l, int r, size_t elemSize, int (*cmp)(const void*, const void*)){
    if(l < r){
        int p = Partition(arr, l, r, elemSize, cmp);
        QuickSortRecur(arr, l, p-1, elemSize, cmp);
        QuickSortRecur(arr, p+1, r, elemSize, cmp);
    }
}
void QuickSort(void* arr, size_t len, size_t elemSize, int (*cmp)(const void*, const void*)){
    QuickSortRecur(arr, 0, len-1, elemSize, cmp);
}
#endif // SORT_ALGORITHM_H_INCLUDED
