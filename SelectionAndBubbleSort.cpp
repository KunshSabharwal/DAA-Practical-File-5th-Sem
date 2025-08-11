#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &arr)
{
    for (int i = 0; i <= arr.size() - 2; i++)
    {
        int min = i;
        for (int j = i; j <= arr.size() - 1; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        swap(arr[i], arr[min]);
    }
}

void bubbleSort(vector<int> &arr)
{
    for (int i = arr.size() - 1; i >= 1; i--)
    {
        bool swapped = false;
        for (int j = 0; j <= i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swapped = true;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (swapped == false)
            break;
    }
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int choice;
    cout << "Enter the sorting algorithm you want to use: " << endl;
    cout << "1. Selection Sort" << endl;
    cout << "2. Bubble Sort" << endl;
    cin >> choice;
    if (choice == 1)
        selectionSort(arr);
    else
        bubbleSort(arr);
    cout << "The sorted array is: " << endl;
    for (int k = 0; k < arr.size(); k++)
    {
        cout << arr[k] << endl;
    }
    return 0;
}
