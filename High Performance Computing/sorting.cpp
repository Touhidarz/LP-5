#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void sequential_bubble_sort(int arr[], int size) {
    int* array = new int[size];  // Dynamic allocation instead of VLA
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }

    double start = omp_get_wtime();
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort:\n";
    cout << "Time Required: " << end - start << endl;
    delete[] array;  // Free allocated memory
}

void parallel_bubble_sort(int arr[], int size) {
    int* array = new int[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        for(int k = 0; k < size; k++) {
            if(k % 2 == 0) {
                #pragma omp for
                for(int i = 1; i < size - 1; i += 2) {
                    if(array[i] > array[i+1]) {
                        swap(array[i], array[i+1]);
                    }
                }
            }
            else {
                #pragma omp for
                for(int i = 0; i < size - 1; i += 2) {
                    if(array[i] > array[i+1]) {
                        swap(array[i], array[i+1]);
                    }
                }
            }
            #pragma omp barrier  // Ensure all threads complete before next iteration
        }
    }
    double end = omp_get_wtime();
    cout << "Parallel Bubble Sort:\n";
    cout << "Time Required: " << end - start << endl;
    delete[] array;
}

void merge(int array[], int low, int mid, int high) {  // Removed unused size parameter
    int temp[high - low + 1];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)) {
        if(array[i] <= array[j]) {  // Changed to <= for stable sort
            temp[k++] = array[i++];
        }
        else {
            temp[k++] = array[j++];
        }
    }
    while(i <= mid) {
        temp[k++] = array[i++];
    }
    while(j <= high) {
        temp[k++] = array[j++];
    }
    for(i = low, k = 0; i <= high; i++, k++) {
        array[i] = temp[k];
    }
}

void mergesort(int array[], int low, int high) {  // Removed size parameter
    if(low < high) {
        int mid = low + (high - low) / 2;  // Avoid potential integer overflow
        mergesort(array, low, mid);
        mergesort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

void perform_merge_sort(int arr[], int size) {
    int* array = new int[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    mergesort(array, 0, size-1);
    double end = omp_get_wtime();
    cout << "Merge Sort:\n";
    cout << "Time Required: " << end - start << endl;
    delete[] array;
}

void p_mergesort(int array[], int low, int high) {
    if(low < high) {
        int mid = low + (high - low) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            p_mergesort(array, low, mid);
            #pragma omp section
            p_mergesort(array, mid + 1, high);
        }
        merge(array, low, mid, high);
    }
}

void perform_p_merge_sort(int arr[], int size) {
    int* array = new int[size];
    for(int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    #pragma omp parallel  // Add parallel region
    {
        #pragma omp single  // Only one thread should start the recursion
        p_mergesort(array, 0, size-1);
    }
    double end = omp_get_wtime();
    cout << "Parallel Merge Sort:\n";
    cout << "Time Required: " << end - start << endl;
    delete[] array;
}

int main() {
    int SIZE;
    const int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int* array = new int[SIZE];  // Dynamic allocation
    srand(time(NULL));  // Seed random number generator
    for(int i = 0; i < SIZE; i++) {
        array[i] = rand() % MAX;
    }
    
    sequential_bubble_sort(array, SIZE);
    parallel_bubble_sort(array, SIZE);
    perform_merge_sort(array, SIZE);
    perform_p_merge_sort(array, SIZE);
    
    delete[] array;  // Free memory
    return 0;
}