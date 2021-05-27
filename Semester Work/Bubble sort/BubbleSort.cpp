void swap(int& number1, int& number2)
{
    int tmp = number1;
    number1 = number2;
    number2 = tmp;
}

int bubbleSort(int* arr, int n)
{
    int cycleIterationsCount = 0;

    for (int i = 0; i < n; i++)
    {
        bool flag = true;
        for (int j = 0; j < n - i - 1; j++)
        { 
            cycleIterationsCount++;
            if (arr[j] > arr[j + 1])
            {
                flag = false;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (flag)
            break;
    }

    return cycleIterationsCount;
}
