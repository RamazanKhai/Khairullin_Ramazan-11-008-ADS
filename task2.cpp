#include <iostream>
#include "build.h"
using namespace std;

TreeNode *remove(TreeNode *node)
{
    if (node->left != nullptr && node->right != nullptr)
    {
        node->left = remove(node->left);
        node->right = remove(node->right);
    }
    else if (node->left == nullptr && node->right != nullptr)
    {
        return remove(node->right);
    }
    else if (node->left != nullptr && node->right == nullptr)
    {
        return remove(node->left);
    }
    return node;
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
    tree = remove(tree);

    delete[] array;
    return 0;
}
