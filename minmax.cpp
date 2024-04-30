#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int findMin(const int arr[], int n)
{
    int min_val = arr[0];
#pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    return min_val;
}

int findMax(const int arr[], int n)
{
    int max_val = arr[0];
#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    return max_val;
}

int findSum(const int arr[], int n)
{
    int sum_val = 0;
#pragma omp parallel for reduction(+ : sum_val)
    for (int i = 0; i < n; i++)
    {
        sum_val += arr[i];
    }
    return sum_val;
}

double findAvg(int sum_val, int n)
{
    return (sum_val / n);
}

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    double start_time, end_time;

    start_time = omp_get_wtime();
    int min_seq = findMin(arr, n);
    int max_seq = findMax(arr, n);
    int sum_seq = findSum(arr, n);
    int avg_seq = findAvg(sum_seq, n);
    end_time = omp_get_wtime();

    double sequential = end_time - start_time;

    start_time = 0;
    end_time = 0;

    start_time = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        {

            int min = findMin(arr, n);
            int max = findMax(arr, n);
            int sum = findSum(arr, n);
            int avg = findAvg(sum_seq, n);
        }
    }
    end_time = omp_get_wtime();

    double parallel = end_time - start_time;

    cout<<sequential<<endl;
    cout<<parallel;

    return 0;
}