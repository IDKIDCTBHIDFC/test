#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void find_sum_seq(long long int arr[], int n, long long &even_sum, long long &odd_sum) {
    even_sum = 0;
    odd_sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_sum += arr[i];
        } else {
            odd_sum += arr[i];
        }
    }
}

void find_sum_parallel(long long int arr[], int n, long long &even_sum, long long &odd_sum) {
    even_sum = 0;
    odd_sum = 0;
    #pragma omp parallel for shared(arr) reduction(+:even_sum, odd_sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even_sum += arr[i];
        } else {
            odd_sum += arr[i];
        }
    }
}

int main() {
    const int n = 10000000; // array size
    long long int *arr = new long long int[n];

    srand(time(0));
    // populate the array with random values between 1 and 100
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100 + 1;
    }

    int choice;
    cout << "choose an opption to claculate the sum:" << endl;
    cout << "1. sequentil sum" << endl;
    cout << "2. paralel sum" << endl;
    cout << "enter ur choise (1 or 2): ";
    cin >> choice;

    long long even_sum, odd_sum;

    if (choice == 1) {
        find_sum_seq(arr, n, even_sum, odd_sum);
        cout << "sum of even (seq): " << even_sum << endl;
        cout << "sum of odd (seq): " << odd_sum << endl;
    } 
    else if (choice == 2) {
        find_sum_parallel(arr, n, even_sum, odd_sum);
        cout << "sum of even (para): " << even_sum << endl;
        cout << "sum of odd (para): " << odd_sum << endl;
    } 
    else {
        cout << "invlid choise!" << endl;
    }

    delete[] arr;
}
