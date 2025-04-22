#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>
#include<chrono>

using namespace std;

void minimum(vector<int> array){
    int min = INT_MAX;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    cout<<endl;
    cout<<"Sequential Min";
    start = std::chrono::system_clock::now();
    for(auto i = array.begin(); i != array.end();i++){
        if(*i < min){
            min = *i;
        } 
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqmin = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << endl;
    cout << "Minimum Element: " << min << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqmin.count() << "s\n";
              
    cout<<endl; 
    cout<<"Parallel Min";
    int min_ele = INT_MAX;
    start = std::chrono::system_clock::now();
    #pragma omp parallel for reduction(min: min_ele)
        for(auto i = array.begin(); i != array.end();i++){
            if(*i < min_ele){
                min_ele = *i;
            } 
        }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plmin = end - start;
    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time_t)
              << "elapsed time: " << elapsed_seconds_plmin.count() << "s\n";
    cout << "Minimum Element(Parallel Reduction): " << min_ele << endl;
    cout<<"Speed Factor = "<<elapsed_seconds_sqmin.count()/elapsed_seconds_plmin.count()<<endl;
}

void maximum(vector<int> array){
    int max = INT_MIN;
    cout<<endl;
    cout<<"Sequential Max"<<endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(auto i = array.begin(); i != array.end();i++){
        if(*i > max){
            max = *i;
        } 
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqmax = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "Maximum Element: " << max << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqmax.count() << "s\n";
    
    cout<<endl;
    cout<<"Parallel Max";
    int max_ele = INT_MIN;
    start = std::chrono::system_clock::now();
    #pragma omp parallel for reduction(max: max_ele)
        for(auto i = array.begin(); i != array.end();i++){
            if(*i > max_ele){
                max_ele = *i;
            } 
        }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plmax = end - start;
    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time_t)
              << "elapsed time: " << elapsed_seconds_plmax.count() << "s\n";
    cout << "Maximum Element(Parallel Reduction): " << max_ele << endl;
    cout<<"Speed Factor = "<<elapsed_seconds_sqmax.count()/elapsed_seconds_plmax.count()<<endl;
    
}

void sum(vector<int> array){
    int sum = 0;
    cout<<endl;
    cout<<"Sequential Sum"<<endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(auto i = array.begin(); i != array.end();i++){
        sum += *i; 
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqsum = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "Summation: " << sum << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqsum.count() << "s\n"; 
    
    cout<<endl;
    cout<<"Parallel Sum";
    sum = 0;
    start = std::chrono::system_clock::now();
    #pragma omp parallel for reduction(+: sum)
        for(auto i = array.begin(); i != array.end();i++){
            sum += *i; 
        }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plsum = end - start;
    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time_t)
              << "elapsed time: " << elapsed_seconds_plsum.count() << "s\n";
    cout << "Summation(Parallel Reduction): " << sum << endl;
    cout<<"Speed Factor = "<<elapsed_seconds_sqsum.count()/elapsed_seconds_plsum.count()<<endl;
}
void average(vector<int> array){
    float avg = 0;
    cout<<endl;
    cout<<"Sequential Avg"<<endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(auto i = array.begin(); i != array.end();i++){
        avg += *i; 
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_sqavg = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "Average: " << avg / array.size() << endl;
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds_sqavg.count() << "s\n"; 
    
    cout<<endl;
    cout<<"Parallel Avg";
    avg = 0;
    start = std::chrono::system_clock::now();
    #pragma omp parallel for reduction(+: avg)
        for(auto i = array.begin(); i != array.end();i++){
            avg += *i; 
        }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds_plavg = end - start;
    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
 
    cout << endl;
    std::cout << "finished computation at " << std::ctime(&end_time_t)
              << "elapsed time: " << elapsed_seconds_plavg.count() << "s\n";
    cout << "Average(Parallel Reduction): " << avg / array.size() << endl;
    cout<<"Speed Factor = "<<elapsed_seconds_sqavg.count()/elapsed_seconds_plavg.count()<<endl;
}

int main(){
    cout << "Enter number of elements in array: ";
    int N;
    int MAX = 1000;
    cin >> N;
    vector<int> array;
    for(int i = 0; i < N; i++){
        array.push_back(rand() % MAX);
    }
    minimum(array);
    maximum(array);
    sum(array);
    average(array);
    return 0;
}