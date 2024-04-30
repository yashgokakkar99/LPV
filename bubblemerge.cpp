#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    #pragma omp for
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    double start_time, end_time;

    // Sequential Execution
    start_time = omp_get_wtime();
    bubbleSort(arr, n);
    end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;

    // Parallel Execution
    start_time = omp_get_wtime();
#pragma omp parallel
    {
        bubbleSort(arr, n);
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    // Calculate speedup
    double speedup = sequential_time / parallel_time;

    cout << "\n\nExecution time (Sequential): " << sequential_time << " seconds";
    cout << "\nExecution time (Parallel): " << parallel_time << " seconds";
}

#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    int a[n1];
    int b[n2];
    for (int i = 0; i < n1; i++)
    {
        a[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        b[i] = arr[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
        {
            arr[k] = a[i];
            k++;
            i++;
        }
        else
        {
            arr[k] = b[j];
            k++;
            j++;
        }
    }
    while (i < n1)
    {
        arr[k] = a[i];
        k++;
        i++;
    }
    while (j < n2)
    {
        arr[k] = b[j];
        k++;
        j++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            mergeSort(arr, l, mid);
#pragma omp section
            mergeSort(arr, mid + 1, r);
        }
        merge(arr, l, mid, r);
    }
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

    // Sequential Execution
    start_time = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;

    // Parallel Execution
    start_time = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        mergeSort(arr, 0, n - 1);
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n\nExecution time (Sequential): " << sequential_time << " seconds";
    cout << "\nExecution time (Parallel): " << parallel_time << " seconds\n";

    return 0;
}
