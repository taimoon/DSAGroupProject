#ifndef SORT_ALGORITHM_H_INCLUDED
#define SORT_ALGORITHM_H_INCLUDED

int BinarySearch(const void* key, const void *arr,
                  size_t len, size_t elemSize,
                  int(*comparator)(const void*, const void*))
{
    int low = 0;
    int high = len-1;
    int mid = (high+low)/2;
    do
    {
        if(comparator(arr+mid*elemSize, key) < 0)
            low = mid+1;
        else if(comparator(arr+mid*elemSize, key) > 0)
            high = mid-1;
        else
            return mid;
        mid = (high+low)/2;
    }while(low <= high);
    return -1;
}
void assign(void *a, void *b, size_t elemSize){
    memcpy(a, b, elemSize);
}
//arr[p..q] and arr[q+1..len]
void Merge(void *arr, int p, int q,
            size_t len, size_t elemSize,
            int(*cmp)(const void*, const void*)){
    int n1 = q-p+1;
    int n2 = len-q;
    void *leftArr = malloc(n1*elemSize);
    void *rightArr = malloc(n2*elemSize);
    for(int i = 0; i < n1; ++i)
        assign(leftArr+i*elemSize, arr+(p+i)*elemSize, elemSize);
    for(int i = 0; i < n2; ++i)
        assign(rightArr+i*elemSize, arr+(q+1+i)*elemSize, elemSize);
    int i, j, k;
    i=j=0;
    k=p;
    while(i < n1 && j < n2){
        if(cmp(leftArr+i*elemSize, rightArr+j*elemSize) <= 0)
            assign(arr+(k++)*elemSize, leftArr+(i++)*elemSize, elemSize);
            //arr[k++] = rightArr[i++];
        else
            assign(arr+(k++)*elemSize, rightArr+(j++)*elemSize, elemSize);
            //arr[k++] = rightArr[j++];
    }
    while(i < n1)
        assign(arr+(k++)*elemSize, leftArr+(i++)*elemSize, elemSize);
        //arr[k++] = leftArr[i++];
    while(j < n2)
        assign(arr+(k++)*elemSize, rightArr+(j++)*elemSize, elemSize);
        //arr[k++] = rightArr[j++];
    free(leftArr);
    free(rightArr);
}
void MergeSortReccur(void *arr, int left,
                        size_t len, size_t elemSize,
                        int(*cmp)(const void*, const void*)){
    if(left < len){
        int m = (left+len-1)/2;
        MergeSortReccur(arr, left, m, elemSize, cmp);
        MergeSortReccur(arr, m+1, len, elemSize, cmp);
        Merge(arr, left, m, len, elemSize, cmp);
    }
}
void MergeSort(void *arr, size_t len, size_t elemSize,
                 int(*cmp)(const void*, const void*)){
    MergeSortReccur(arr, 0, len, elemSize, cmp);
}
#endif // SORT_ALGORITHM_H_INCLUDED
