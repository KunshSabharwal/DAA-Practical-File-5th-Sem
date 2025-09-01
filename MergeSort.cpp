#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;
// added merge sort code with clock and rand functions
void mergeSections(int *array, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = new int[n1];
    int *rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = array[left + i];

    for (int j = 0; j < n2; j++)
        rightArr[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
            array[k++] = leftArr[i++];
        else
            array[k++] = rightArr[j++];
    }

    while (i < n1)
        array[k++] = leftArr[i++];
    while (j < n2)
        array[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

void recursiveMergeSort(int *array, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    recursiveMergeSort(array, left, mid);
    recursiveMergeSort(array, mid + 1, right);
    mergeSections(array, left, mid, right);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    int sizes[] = {100, 1000, 10000, 50000, 80000, 100000};
    int totalSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < totalSizes; s++)
    {
        int n = sizes[s];
        cout << "Sorting size: " << n << " using Merge Sort..." << endl;

        int *arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = rand();

        auto start = high_resolution_clock::now();
        recursiveMergeSort(arr, 0, n - 1);
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;
        cout << "Time taken: " << elapsed.count() << " seconds\n"
             << endl;

        delete[] arr;
    }

    return 0;
}
