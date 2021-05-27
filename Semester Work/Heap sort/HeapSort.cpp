#include <utility>


void swap(int& number1, int& number2)
{
    int tmp = number1;
    number1 = number2;
    number2 = tmp;
}

int heapify(int* arr, int n, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        return heapify(arr, n, largest) + 1;
    }
    return 0;
}

std::pair<int, int> heapSort(int* arr, int n)
{
    int cycleIterationsCount = 0, recursiveCallscount = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        cycleIterationsCount++;
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        cycleIterationsCount++;
        swap(arr[0], arr[i]);
        recursiveCallscount += heapify(arr, i, 0);
    }

    return std::pair<int, int>(cycleIterationsCount, recursiveCallscount);
}
