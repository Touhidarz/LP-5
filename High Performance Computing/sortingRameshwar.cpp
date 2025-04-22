#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

#define NUM_THREADS 4  // Number of threads for parallel execution


void generateRandomArray(vector<int> &arr, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


void bubbleSortSequential(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void bubbleSortParallel(vector<int> &arr) {
    int n = arr.size();

    #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

}

void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mergeSortSequential(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortSequential(arr, left, mid);
        mergeSortSequential(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void mergeSortParallel(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, left, mid);

            #pragma omp section
            mergeSortParallel(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}


double measureExecutionTime(void (*sortFunction)(vector<int> &), vector<int> &arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}


double measureExecutionTime(void (*sortFunction)(vector<int> &, int, int), vector<int> &arr, int left, int right) {
    auto start = high_resolution_clock::now();
    sortFunction(arr, left, right);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}


int main() {
    int size = 0; // Array size

    cout << "Enter number of elemnts in array : ";
    cin >> size ;
    
    vector<int> arr(size), arr_copy;

    // Generate random array
    generateRandomArray(arr, size);
    arr_copy = arr;  // Copy for comparison

    
    cout << "Bubble Sort Sequential Execution:\n";
    auto start = high_resolution_clock::now();
    bubbleSortSequential(arr);
    auto end = high_resolution_clock::now();
    double bubbleSeqTime = duration<double>(end - start).count();
    cout << "Time: " << bubbleSeqTime << " sec\n\n";


    cout << "Bubble Sort parallel Execution:\n";
    start = high_resolution_clock::now();
    bubbleSortParallel(arr);
    end = high_resolution_clock::now();
    double bubbleParTime = duration<double>(end - start).count();
    cout << "Time: " << bubbleParTime << " sec\n";
    cout << "Speedup: " << bubbleSeqTime / bubbleParTime << "\n\n";


// Measure and compare Merge Sort
    arr = arr_copy; // Reset array
    cout << "Merge Sort Sequential Execution:\n";
    start = high_resolution_clock::now();
    mergeSortSequential(arr, 0, size - 1);
    end = high_resolution_clock::now();
    double mergeSeqTime = duration<double>(end - start).count();
    cout << "Time: " << mergeSeqTime << " sec\n\n";

    arr = arr_copy; // Reset array
    cout << "Merge Sort Parallel Execution:\n";
    start = high_resolution_clock::now();
    mergeSortParallel(arr, 0, size - 1);
     end = high_resolution_clock::now();
    double mergeParTime = duration<double>(end - start).count();
    cout << "Time: " << mergeParTime << " sec\n";
    cout << "Speedup: " << mergeSeqTime / mergeParTime << "\n";

    return 0;
}