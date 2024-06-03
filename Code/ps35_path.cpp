/*
Didn't get a perfect score (10/100) : Incorrect Answer
Code modification is required
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <climits>

using namespace std;
static int preIdx = 0;
struct TreeNode {
    int value;
    int num;
    struct TreeNode* left, * right;
};

int findMaxSum(TreeNode* root)
{
    int max_sum = INT_MIN;
    stack<pair<TreeNode*, int> > s;
    s.push(make_pair(root, 0));

    while (!s.empty())
    {
        auto node = s.top().first;
        int state = s.top().second;
        s.pop();

        if (node == nullptr)
        {
            continue;
        }

        if (state == 0)
        {
            // first visit to the node
            s.push(make_pair(node, 1));
            s.push(make_pair(node->left, 0));
        }
        else if (state == 1)
        {
            // second visit to the node
            s.push(make_pair(node, 2));
            s.push(make_pair(node->right, 0));
        }
        else
        {
            // third visit to the node
            int left_sum = (node->left != nullptr)
                ? node->left->value
                : 0;
            int right_sum = (node->right != nullptr)
                ? node->right->value
                : 0;
            max_sum
                = max(max_sum, node->value + max(0, left_sum)
                    + max(0, right_sum));
            int max_child_sum = max(left_sum, right_sum);
            node->value += max(0, max_child_sum);
        }
    }

    return max_sum;
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
        vector<int> path;

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

        int maxPathSum = findMaxSum(root);

        ofp << maxPathSum << endl;
        //cout << maxPathSum << endl;
    }

    ifp.close();
    ofp.close();

    return 0;
}
