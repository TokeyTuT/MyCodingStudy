#include <vector>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node() : left(nullptr), right(nullptr) {};
    Node(int d)
    {
        left = nullptr;
        right = nullptr;
        data = d;
    }
};

Node *CreatBinaryTree(const vector<int> &postArr, const vector<int> &inorderArr)
{
    if (postArr.size() == 0)
        return nullptr;
    Node *root = new Node(postArr[postArr.size() - 1]);
    // 已经到了尽头
    if (postArr.size() == 1)
        return root;
    int index = 0;
    // 左子中序
    for (const auto it : inorderArr)
    {
        if (it == postArr[postArr.size() - 1])
        {
            break;
        }
        index++;
    }
    // 切割中序
    vector<int> temp_left_inorderArr;
    temp_left_inorderArr.assign(inorderArr.begin(), inorderArr.begin() + index);
    vector<int> temp_right_inorderArr;
    temp_right_inorderArr.assign(inorderArr.begin() + index + 1, inorderArr.end());
    // 切割后序
    vector<int> temp_left_postArr;
    temp_left_postArr.assign(postArr.begin(), postArr.begin() + temp_left_inorderArr.size());
    vector<int> temp_right_postArr;
    temp_right_postArr.assign(postArr.begin() + temp_left_inorderArr.size() + 1, postArr.end() - 1);
    // 递归
    root->left = CreatBinaryTree(temp_left_postArr, temp_left_inorderArr);
    root->right = CreatBinaryTree(temp_right_postArr, temp_right_inorderArr);
    return root;
}