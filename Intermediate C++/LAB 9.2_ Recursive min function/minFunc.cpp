#include "minFunc.h"
const int * min(const int arr[], int arrSize) {
    if (arrSize == 0){
        return nullptr;
    }
    else if (arrSize == 1){
        return arr;
    }
    else{
        const int * m = min(arr + 1, arrSize - 1);
        if (*m < arr[0]){
            return m;
        }
        else{
            return arr;
        }
    }
}