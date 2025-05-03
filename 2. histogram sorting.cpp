#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <omp.h>
using namespace std;

vector<double> binSort(const vector<double>& arr, int numBins) {
    if (arr.size() <= 1 || numBins <= 0) return arr;
    double min = arr[0];
    double max = arr[0];
    
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
    vector<vector<double> > bins(numBins);
    
    double range = (max - min) / numBins;
    for (int i = 0; i < arr.size(); i++) {
        int index = (int)((arr[i] - min) / range);
        
        // Handle edge case where arr[i] == max
        if (index == numBins) index = numBins - 1;
        
        bins[index].push_back(arr[i]);
    }
	#pragma omp parallel for
    for (int i = 0; i < numBins; i++) {
        sort(bins[i].begin(), bins[i].end());
    }
    
    vector<double> result;
    for (int i = 0; i < numBins; i++) {
        for (int j = 0; j < bins[i].size(); j++) {
            result.push_back(bins[i][j]);
        }
    }
    
    return result;
}

vector<double> generatearray(int size, int min, int max) {
    vector<double> arr(size);
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        arr[i] = min + (rand() % (max - min + 1));
    }
    return arr;
}

int main() {
    srand(0);

    int arraySize, numBins;
    int minValue = 1;
    int maxValue = 100;
    
    cout << "Enter the size of the array: ";
    cin >> arraySize;
    
    cout << "Enter the number of bins: ";
    cin >> numBins;
    
    vector<double> arr = generatearray(arraySize, minValue, maxValue);

    cout << "Original array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    vector<double> sorted = binSort(arr, numBins);
   	cout << endl;
    cout << "Sorted array: ";
    for (int i = 0; i < sorted.size(); i++) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    return 0;
}

