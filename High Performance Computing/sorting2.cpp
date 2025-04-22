#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>
using namespace std;


    



std::chrono::duration<double> sequential_bubble_sort(int arr[],int size){
	std::chrono::time_point<std::chrono::system_clock> start, end;
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }

    //double start = omp_get_wtime();
    start = std::chrono::system_clock::now();
    for(int i = 0; i < size - 1; i ++){
        for(int j = 0; j < size - i - 1; j++){
            if(array[j] > array[j+1]){
                swap(array[j],array[j+1]);
            }
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqbs = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    cout << "Sequential Bubble Sort:\n";
    //  for(int i = 0 ; i < size; i++){
    //      cout << array[i] << " ";
    //  }
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqbs.count() << "s\n";
    //double end = omp_get_wtime();
    //cout << "Time Required: " << end - start << endl;
	return elapsed_seconds_sqbs;
}

std::chrono::duration<double> parallel_bubble_sort(int arr[],int size){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }
    start = std::chrono::system_clock::now();
    //double start = omp_get_wtime();
    for(int k = 0; k < size;k ++){
        if(k % 2 == 0){
            #pragma omp parallel for
                for(int i = 1; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
        else{
            #pragma omp parallel for
                for(int i = 0; i < size - 1; i += 2){
                    if(array[i] > array[i+1]){
                        swap(array[i],array[i+1]);
                    }
                }
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plbs = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    cout << "Parallel Bubble Sort:\n";
    //  for(int i = 0 ; i < size; i++){
    //      cout << array[i] << " ";
    //  }
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_plbs.count() << "s\n";
    //double end = omp_get_wtime();
    //cout << "Time Required: " << end - start << endl;
    return elapsed_seconds_plbs;
}

void merge(int array[],int low, int mid, int high,int size){
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)){
        if(array[i] >= array[j]){
            temp[k] = array[j];
            k++;
            j++;
        }
        else{
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid){
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = array[j];
        k++;
        j++;
    }

    k = 0;
    for(int i = low;i <= high;i++){
        array[i] = temp[k];
        k++;
    }
}

void mergesort(int array[],int low,int high,int size){
    if(low < high){
        int mid = (low + high) / 2;
        mergesort(array,low,mid,size);
        mergesort(array,mid+1,high,size);
        merge(array,low,mid,high,size);
    }
}

std::chrono::duration<double> perform_merge_sort(int arr[],int size){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }
    start = std::chrono::system_clock::now();
    //double start = omp_get_wtime();
    mergesort(array,0,size-1,size);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqms = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    cout << "Merge Sort:\n";
    //  for(int i = 0 ; i < size; i++){
    //      cout << array[i] << " ";
    //  }
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqms.count() << "s\n";
    //double end = omp_get_wtime();
    //cout << "Time Required: " << end - start << endl;
    return elapsed_seconds_sqms;
}

void p_mergesort(int array[],int low,int high,int size){
    if(low < high){
        int mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
                p_mergesort(array,low,mid,size);
            #pragma omp section
                p_mergesort(array,mid+1,high,size);
        }
        merge(array,low,mid,high,size);
    }
}

std::chrono::duration<double> perform_p_merge_sort(int arr[],int size){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int array[size];
    for(int i = 0 ; i < size; i++){
        array[i] = arr[i];
    }
    start = std::chrono::system_clock::now();
    //double start = omp_get_wtime();
    p_mergesort(array,0,size-1,size);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plms = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    cout << "Parallel Merge Sort:\n";
    //  for(int i = 0 ; i < size; i++){
    //      cout << array[i] << " ";
    //  }
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_plms.count() << "s\n";
    //double end = omp_get_wtime();
    //cout << "Time Required: " << end - start << endl;
    return elapsed_seconds_plms;
}



int main(int argc, char const *argv[])
{
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    cout<<endl;
    int array[SIZE];
    for(int i = 0 ; i < SIZE; i ++){
        array[i] = rand() % MAX;
    }
    //  cout << "Initial Array:\n";
    //  for(int i = 0 ; i < SIZE; i++){
        //  cout << array[i] << " ";
    //  }
    cout << endl;
    std::chrono::duration<double> elapsed_seconds_sqbs = sequential_bubble_sort(array,SIZE);
    std::chrono::duration<double> elapsed_seconds_plbs = parallel_bubble_sort(array,SIZE);
    cout<<"Speed Factor = "<<elapsed_seconds_sqbs.count()/elapsed_seconds_plbs.count()<<endl;
    std::chrono::duration<double> elapsed_seconds_sqms = perform_merge_sort(array,SIZE);
    std::chrono::duration<double> elapsed_seconds_plms = perform_p_merge_sort(array,SIZE);
    cout<<"Speed Factor = "<<elapsed_seconds_sqms.count()/elapsed_seconds_plms.count()<<endl;
    return 0;
}