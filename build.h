struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x)
    {
        value = x;
        left = right = nullptr;
    }
};

TreeNode* build(int startIdx, int endIdx, int *array);
