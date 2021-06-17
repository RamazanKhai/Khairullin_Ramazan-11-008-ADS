#include <iostream>
#include "build.h"
using namespace std;

int main()
{
    cout << "Enter a quantity of elements in tree: ";
    int countOfElems;
    cin >> countOfElems;
    cout << "Enter the elements separated by a space: ";
    int *array = new int[countOfElems];
    for (int i = 0; i < countOfElems; i++)
    {
        cin >> array[i];
    }
    TreeNode *tree = build(0, 10, array);

    delete[] array;
    return 0;
}
