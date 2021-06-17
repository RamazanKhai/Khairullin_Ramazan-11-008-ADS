#include "build.h"

TreeNode* build(int startIdx, int endIdx, int *array)
{
    if (startIdx == endIdx)
    {
        return nullptr;
    }
    if (startIdx + 1 == endIdx)
    {
        return new TreeNode(array[startIdx]);
    }
    TreeNode *newNode = new TreeNode(array[(startIdx + endIdx) / 2]);
    newNode->left = build(startIdx, (startIdx + endIdx) / 2, array);
    newNode->right = build((startIdx + endIdx) / 2 + 1, endIdx, array);
    return newNode;
}
