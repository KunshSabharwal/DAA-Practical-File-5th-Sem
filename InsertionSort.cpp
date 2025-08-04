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
    insertionSort(arr);
    cout << "The sorted array is: " << endl;
    for (int k = 0; k < arr.size(); k++)
    {
        cout << arr[k] << endl;
    }
    return 0;
}
