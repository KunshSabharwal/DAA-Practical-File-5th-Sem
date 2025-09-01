#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

void swapValues(int *array, int idx1, int idx2)
{
    int temp = array[idx1];
    array[idx1] = array[idx2];
    array[idx2] = temp;
}

int partitionHelper(int *array, int low, int pivot, int high)
{
    int left = low, boundary = low;
    while (left < high)
    {
        if (array[left] < array[pivot])
        {
            swapValues(array, left, boundary);
            boundary++;
        }
        left++;
    }
    swapValues(array, boundary, pivot);
    return boundary;
}

void quickSorter(int *array, int low, int high)
{
    if (low >= high)
        return;

    int pivot = high;
    int newPivot = partitionHelper(array, low, pivot, high);

    quickSorter(array, low, newPivot - 1);
    quickSorter(array, newPivot + 1, high);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    int inputSizes[] = {10000, 50000, 80000, 100000, 150000, 180000};
    int totalCases = sizeof(inputSizes) / sizeof(inputSizes[0]);

    for (int t = 0; t < totalCases; t++)
    {
        int n = inputSizes[t];
        cout << "Sorting size: " << n << " using Quick Sort..." << endl;

        int *arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = rand();

        auto start = high_resolution_clock::now();
        quickSorter(arr, 0, n - 1);
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;
        cout << "Time taken: " << elapsed.count() << " seconds\n"
             << endl;

        delete[] arr;
    }

    return 0;
}
