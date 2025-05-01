#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void minimum(vector<int> array) {
    int min = INT_MAX;
    cout << endl;
    cout << "Sequential Min" << endl;

    // Sequential Min timing using omp_get_wtime
    double start = omp_get_wtime();
    for (auto i = array.begin(); i != array.end(); i++) {
        if (*i < min) {
            min = *i;
        }
    }
    double end = omp_get_wtime();
    cout << "Minimum Element: " << min << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";

    cout << endl;
    cout << "Parallel Min" << endl;
    int min_ele = INT_MAX;

    // Parallel Min timing using omp_get_wtime
    start = omp_get_wtime();
    #pragma omp parallel for reduction(min: min_ele)
    for (auto i = array.begin(); i != array.end(); i++) {
        if (*i < min_ele) {
            min_ele = *i;
        }
    }
    end = omp_get_wtime();
    cout << "Minimum Element (Parallel Reduction): " << min_ele << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";
    cout << "Speed Factor = " << (end - start) / (end - start) << endl;
}

void maximum(vector<int> array) {
    int max = INT_MIN;
    cout << endl;
    cout << "Sequential Max" << endl;

    // Sequential Max timing using omp_get_wtime
    double start = omp_get_wtime();
    for (auto i = array.begin(); i != array.end(); i++) {
        if (*i > max) {
            max = *i;
        }
    }
    double end = omp_get_wtime();
    cout << "Maximum Element: " << max << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";

    cout << endl;
    cout << "Parallel Max" << endl;
    int max_ele = INT_MIN;

    // Parallel Max timing using omp_get_wtime
    start = omp_get_wtime();
    #pragma omp parallel for reduction(max: max_ele)
    for (auto i = array.begin(); i != array.end(); i++) {
        if (*i > max_ele) {
            max_ele = *i;
        }
    }
    end = omp_get_wtime();
    cout << "Maximum Element (Parallel Reduction): " << max_ele << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";
    cout << "Speed Factor = " << (end - start) / (end - start) << endl;
}

void sum(vector<int> array) {
    int sum = 0;
    cout << endl;
    cout << "Sequential Sum" << endl;

    // Sequential Sum timing using omp_get_wtime
    double start = omp_get_wtime();
    for (auto i = array.begin(); i != array.end(); i++) {
        sum += *i;
    }
    double end = omp_get_wtime();
    cout << "Summation: " << sum << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";

    cout << endl;
    cout << "Parallel Sum" << endl;
    sum = 0;

    // Parallel Sum timing using omp_get_wtime
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+: sum)
    for (auto i = array.begin(); i != array.end(); i++) {
        sum += *i;
    }
    end = omp_get_wtime();
    cout << "Summation (Parallel Reduction): " << sum << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";
    cout << "Speed Factor = " << (end - start) / (end - start) << endl;
}

void average(vector<int> array) {
    float avg = 0;
    cout << endl;
    cout << "Sequential Avg" << endl;

    // Sequential Avg timing using omp_get_wtime
    double start = omp_get_wtime();
    for (auto i = array.begin(); i != array.end(); i++) {
        avg += *i;
    }
    double end = omp_get_wtime();
    cout << "Average: " << avg / array.size() << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";

    cout << endl;
    cout << "Parallel Avg" << endl;
    avg = 0;

    // Parallel Avg timing using omp_get_wtime
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+: avg)
    for (auto i = array.begin(); i != array.end(); i++) {
        avg += *i;
    }
    end = omp_get_wtime();
    cout << "Average (Parallel Reduction): " << avg / array.size() << endl;
    cout << "Elapsed time: " << (end - start) << "s\n";
    cout << "Speed Factor = " << (end - start) / (end - start) << endl;
}

int main() {
    cout << "Enter number of elements in array: ";
    int N;
    int MAX = 1000;
    cin >> N;
    vector<int> array;
    for (int i = 0; i < N; i++) {
        array.push_back(rand() % MAX);
    }
    minimum(array);
    maximum(array);
    sum(array);
    average(array);
    return 0;
}
