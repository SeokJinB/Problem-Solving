/*
Didn't get a perfect credit (50/100) : Time limit(1000ms) exceeded
Code modification is required
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;
static int preIdx = 0;
vector<int> leaves;
struct TreeNode
{
    int value;
    int num;
    struct TreeNode* left, * right;
};

// Utility function to allocate memory for a new node
bool isLeaf(TreeNode* node) {
    return (node->left == nullptr && node->right == nullptr);
}

int findMaxLeafToLeafSum(TreeNode* node, int& maxPathSum) {
    if (node == nullptr) return 0;

    if (isLeaf(node))
    {
        leaves.emplace_back(node->value);
        return node->value;
    }

    int leftSum = findMaxLeafToLeafSum(node->left, maxPathSum);
    int rightSum = findMaxLeafToLeafSum(node->right, maxPathSum);

    if (node->left && node->right) {
        int currentPathSum = leftSum + node->value + rightSum;
        if (currentPathSum > maxPathSum) {
            maxPathSum = currentPathSum;
        }

        return std::max(leftSum, rightSum) + node->value;
    }

    return (node->left ? leftSum : rightSum) + node->value;
}

int getMaxLeafToLeafSum(TreeNode* root) {
    if (root == nullptr) return 0;

    int maxPathSum = INT_MIN;
    findMaxLeafToLeafSum(root, maxPathSum);
    return maxPathSum;
}

int get_inorder_index(vector<int> inorder, int begin, int end, int target)
{
    for (int i = begin; i <= end; i++)
    {
        if (inorder[i] == target)
            return i;
    }
    return -1;
}

TreeNode* tree_restore(vector<int> preorder, vector<int> inorder, int begin, int end)
{
    TreeNode* newNode = NULL;

    if (begin <= end)
    {
        newNode = new TreeNode();
        newNode->num = preorder[preIdx++];
        newNode->left = newNode->right = NULL;

        int inIdx = get_inorder_index(inorder, begin, end, newNode->num);
        newNode->left = tree_restore(preorder, inorder, begin, inIdx - 1);
        newNode->right = tree_restore(preorder, inorder, inIdx + 1, end);
    }
    return newNode;
}

void mapValuesToTree(TreeNode* root, const std::vector<int>& arr)
{
    if (!root) return;

    if (root->num < arr.size())
    {
        root->value = arr[root->num];
    }

    mapValuesToTree(root->left, arr);
    mapValuesToTree(root->right, arr);
}

void inorderTraversal(TreeNode* root)
{
    if (root)
    {
        inorderTraversal(root->left);
        std::cout << "Node value: " << root->value << ", Node num: " << root->num << std::endl;
        inorderTraversal(root->right);
    }
}

int main()
{
    ifstream ifp("path.inp");
    ofstream ofp("path.out");

    int T, n;

    ifp >> T;

    for (int t = 0; t < T; t++)
    {
        preIdx = 0;
        ifp >> n;
        int index;

        vector<int> preorderNum(n);
        vector<int> inorderNum(n);
        vector<int> preorder(n);
        vector<int> inorder(n);

        for (int i = 0; i < n; i++)
        {
            inorderNum[i] = i;
            ifp >> inorder[i];
        }

        for (int i = 0; i < n; i++)
        {
            ifp >> index;
            preorderNum[i] = index;
            preorder[i] = inorder[index];
        }

        TreeNode* root = tree_restore(preorderNum, inorderNum, 0, n - 1);

        mapValuesToTree(root, inorder);
        //inorderTraversal(root);


        int maxPathleafSum = getMaxLeafToLeafSum(root);
        int maxleaf = *max_element(leaves.begin(), leaves.end());

        int maxPathSum = std::max(maxleaf, maxPathleafSum);

        //cout << maxPathSum << endl;
        ofp << maxPathSum << endl;

        leaves.clear();
    }

    ifp.close();
    ofp.close();

    return 0;
}
