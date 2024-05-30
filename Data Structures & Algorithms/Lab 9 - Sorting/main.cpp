#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds


int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//O(n log(n))
void Quicksort_midpoint(int numbers[], int i, int k) {
	if (i < k) { //base case : if partition size is 1 or 0 aka nothing left to sort.
        int pivot = numbers[i + (k - i) / 2];
        int left = i;
        int right = k;
        
        while (true) {
            while (numbers[left] < pivot) { //increments left index while numbers[leftSide] < pivot
                left += 1;
            }
            
            while (numbers[right] > pivot) { //decrements right index while numbers[rightSide] > pivot
                right -= 1;
            }
            
            //nothing left to sort aka if zero or one elements remain, break and use rightIndex
            if (left >= right) {
                break;
            }
            
            else if (left < right) { //swap
                int temp = numbers[left];
                numbers[left] = numbers[right];
                numbers[right] = temp;
                left += 1;
                right -= 1;
            }
        }

        Quicksort_midpoint(numbers, i, right);
        Quicksort_midpoint(numbers, right + 1, k);
    }

    else {
        return; 
    }
}

// helper function to quickly find the median 
int median(int beg, int mid, int end) {
	if (beg > mid) {
		if (mid > end) {
			return mid;
		}

		else if (beg > end) {
			return end;
		}

		else {
			return beg;
		}
	}
    
	else {
		if (beg > end) {
			return beg;
		}

		else if (mid > end) {
			return end;
		}

		else {
			return mid;
		}
	}
}

// O (n log(n))
void Quicksort_medianOfThree(int numbers[], int i, int k) { 
    if(i < k) {
        int pivot = median(numbers[i], numbers[i + (k-i)/2], numbers[k]); //median of the three values at beginning, mid, and end will be the pivot point
        int leftSide = i;
        int rightSide = k;

        //partition algorithm
        while(true){
            while(numbers[leftSide] < pivot) {
                ++leftSide;  //increments left index while numbers[leftSide] < pivot
            }

            while(numbers[rightSide] > pivot) {
                --rightSide; //decrements right index while numbers[rightSide] > pivot
            }
            
            //nothing left to sort aka if zero or one elements remain, break and use rightIndex
            if(leftSide >= rightSide) {
                break;
            } 
            
            else {
                //swap numbers at leftIndex and rightIndex
                int temp = numbers[leftSide];
                numbers[leftSide] = numbers[rightSide];
                numbers[rightSide] = temp;
                //update left and right indeces
                ++leftSide;
                --rightSide;
            }
        }

        //recursively sort from numbers[i] to numbers[rightSide]
        Quicksort_medianOfThree(numbers, i, rightSide);

        //recursively sort from numbers[rightSide + 1] to numbers[k]
        Quicksort_medianOfThree(numbers, rightSide + 1, k);
    }

    else { 
        return;
    }
}

//O(n^2)
void InsertionSort(int numbers[], int numbersSize){
    for (int i = 1; i < numbersSize; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (numbers[j] < numbers[j - 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j - 1];
                numbers[j - 1] = temp;
            }
        }
    }
}

int main(){
    int arr[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr, arr2, arr3);

    cout << "Now testing runtime of 3 sorting algs on arrays of size: " << NUMBERS_SIZE << endl;

    clock_t Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;
}