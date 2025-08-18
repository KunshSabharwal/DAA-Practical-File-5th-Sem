#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int j = 1; j <= arr.size() - 1; j++)
    {
        int key = arr[j];
        int i = j - 1;
        while (i >= 0 && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i = i - 1;
        }
        arr[i + 1] = key;
    }
}

int linear_search(vector<int> &arr, int key)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }
    return -1;
}

int binary_search(vector<int> &arr, int key)
{
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
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
    int key;
    cout << "Enter the element you want to search in the entered array: ";
    cin >> key;
    int choice;
    cout << "Enter the searching algorithm you want to use: " << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cin >> choice;
    int ans;
    if (choice == 1)
        ans = linear_search(arr, key);
    else
    {
        insertionSort(arr);
        ans = binary_search(arr, key);
    }
    if (ans == -1)
    {
        cout << "Element not found in the entered array!" << endl;
    }
    else
    {
        cout << "Element found at " << ans << " index in the entered array." << endl;
    }
    return 0;
}