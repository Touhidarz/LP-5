#include<iostream>
#include<omp.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

void Min(vector<double> arr){
    int seqMin = INT_MAX;
    cout<<"Minimum Element : ";
    
    double seqStart = omp_get_wtime();
    for(auto i = arr.begin(); i != arr.end(); i++){
        if(*i < seqMin){
            seqMin = *i;
        }
    }
    double seqEnd = omp_get_wtime();
    double seqTime = seqEnd-seqStart;
    cout<<seqMin<<endl<<"Sequential Min Time : "<<seqTime<<endl;
    
    int parMin = INT_MAX;
    double parStart = omp_get_wtime();
    #pragma omp parallel for reduction (min : parMin)
    for(auto i = arr.begin(); i != arr.end(); i++){
        if(*i < parMin){
            parMin = *i;
        }
    }
    double parEnd = omp_get_wtime();
    double parTime = parEnd-parStart;
    cout<<"Parallel Min Time : "<<parTime<<endl;
    cout<<"SpeedUp factor : "<<(seqTime/parTime)<<endl<<endl;
    
}

void Max(vector<double> arr){
    int seqMax = INT_MIN;
    cout<<"Maximum Element : ";
    
    double seqStart = omp_get_wtime();
    for(auto i = arr.begin(); i != arr.end(); i++){
        if(*i > seqMax){
            seqMax = *i;
        }
    }
    double seqEnd = omp_get_wtime();
    double seqTime = seqEnd-seqStart;
    cout<<seqMax<<endl<<"Sequential Time : "<<seqTime<<endl;
    
    int parMax = INT_MIN;
    double parStart = omp_get_wtime();
    #pragma omp parallel for reduction (max : parMax)
    for(auto i = arr.begin(); i != arr.end(); i++){
        if(*i > seqMax){
            seqMax = *i;
        }
    }
    double parEnd = omp_get_wtime();
    double parTime = parEnd-parStart;
    
    cout<<"Parallel Time : "<<parTime<<endl;
    cout<<"Speed Up Factor : "<<(seqTime/parTime)<<endl<<endl;
}

void Sum(vector<double> arr){
    double sum = 0.0;
    cout<<"Sum : ";
    
    double start = omp_get_wtime();
    for(auto i = arr.begin(); i != arr.end(); i++){
        sum += *i;
    }
    double end = omp_get_wtime();
    double time = end-start;
    cout<<sum<<endl<<"Time elapsed : "<<time<<endl;
    
    double parSum = 0.0;
    
    double parStart = omp_get_wtime();
    #pragma omp parallel for reduction (+: parSum)
    for(auto i = arr.begin(); i != arr.end(); i++){
        parSum += *i;
    }
    double parEnd = omp_get_wtime();
    double parTime = parEnd-parStart;
    cout<<"Parallel Time : "<<parTime<<endl;
    cout<<"Speed Up : "<<(time/parTime)<<endl<<endl;
    
}

void Avg(vector<double> arr){
    double sum=0.0;
    cout<<"Average : ";
    
    double start = omp_get_wtime();
    for(auto i = arr.begin(); i != arr.end(); i++){
        sum += *i;
    }
    double end = omp_get_wtime();
    double time = end-start;
    cout<<(sum/arr.size())<<endl<<"Time elapsed : "<<time<<endl;
    
    double parSum = 0.0;
    double parStart = omp_get_wtime();
    #pragma omp parallel for reduction (+: parSum)
    for(auto i = arr.begin(); i != arr.end(); i++){
        parSum += *i;
    }
    double parEnd = omp_get_wtime();
    double parTime = parEnd-parStart;
    cout<<"Parallel Time : "<<parTime<<endl;
    cout<<"Speed Up : "<<(time/parTime)<<endl<<endl;
}

int main(){
    int size;
    cout<<"Enter number of Elements : "<<endl;
    cin>>size;
    
    vector<double> arr;
    
    for(int i=0; i<size; i++){
        arr.push_back(rand() % 1000);
    }
    
    Min(arr);
    Max(arr);
    Sum(arr);
    Avg(arr);
}