#include <iostream>
#include <vector>
#include "build.h"
using namespace std;

void traverse(int targetElem, TreeNode *node, vector<int> &vec)
{
    if (node == nullptr)
    {
        vec = vector<int>();
        return;
    }
    vec.push_back(node->value);
    if (node->value != targetElem)
    {
        if (targetElem < node->value)
        {
            traverse(targetElem, node->left, vec);
        }
        else
        {
            traverse(targetElem, node->right, vec);
        }
    }
}

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
    cout << "Enter the element to find: ";
    int targetElem;
    cin >> targetElem;
    vector<int> vec;
    traverse(targetElem, tree, vec);
    if (vec.size() == 0)
    {
        cout << "There is no " << targetElem << " in a tree." << endl;
    }
    else
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            cout << vec[i] << ", ";
        }
        cout << vec[vec.size() - 1] << endl;
    }

    delete[] array;
    return 0;
}
