#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

struct Item
{
    double value, weight;
};

// Comparator to sort by value/weight ratio
bool cmp(const Item &a, const Item &b)
{
    return (a.value / a.weight) > (b.value / b.weight);
}

double fractionalKnapsack(Item items[], int n, double capacity)
{
    sort(items, items + n, cmp);

    double totalValue = 0;
    for (int i = 0; i < n && capacity > 0; i++)
    {
        if (items[i].weight <= capacity)
        {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        else
        {
            totalValue += (items[i].value / items[i].weight) * capacity;
            capacity = 0;
        }
    }
    return totalValue;
}

int main()
{
    srand(time(nullptr));

    int sizes[] = {1000, 5000, 10000, 50000, 80000, 100000};
    double capacity = 10000;

    for (int n : sizes)
    {
        Item *items = new Item[n];
        for (int i = 0; i < n; i++)
        {
            items[i].weight = (rand() % 100) + 1;
            items[i].value = (rand() % 500) + 1;
        }

        auto start = high_resolution_clock::now();
        double maxProfit = fractionalKnapsack(items, n, capacity);
        auto end = high_resolution_clock::now();

        double timeTaken = duration<double>(end - start).count();

        cout << "Number of items: " << n << "\n";
        cout << "Highest Profit: " << maxProfit << "\n";
        cout << "Time Taken: " << timeTaken << " seconds\n";
        cout << "-----------------------------\n";

        delete[] items;
    }
    return 0;
}
