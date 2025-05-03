#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define SIZE 1000000

using namespace std;

void quicksort(int arr[], int start, int end){
    if (start >= end) return;

    int pivot = arr[end];
    int i = start-1;

    for (int j = start; j < end; j++){
        if (arr[j] < pivot){
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    int partitionIdx = i + 1;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            quicksort(arr, start, partitionIdx - 1);
        }
        
        #pragma omp section
        {
            quicksort(arr, partitionIdx + 1, end);
        }
    }
}

int main() {
    int arr[SIZE];
    srand(time(0));
    for (int i = 0; i < SIZE; i++){
        arr[i] = rand() % 100 + 1;
    }

    cout << "Unsorted array: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    #pragma omp parallel
    {
        #pragma omp single
        quicksort(arr, 0, SIZE - 1);
    }

    cout << "Sorted array: ";
    for (int i = 0; i < SIZE; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}