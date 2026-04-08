/*
* 这个文件是用于对二叉树题目的调试模版，内容包含：
* 1.CreatTree 建树，有两个重载，可以选择手动键入也可以选择直接编译前就导入。
* 2.PrintTree 输出树，按照 bfs 横向输出数据
* 3. Solution 需要调试的函数
*/
#include<iostream>
#include<climits>
#include<vector>
#include<stack>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<queue>
#include<deque>
using namespace std;
#define nptr INT_MIN

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left),
        right(right) {
    }
};

vector<vector<int>> getVal(TreeNode* root) {
    vector<vector<int>> res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        vector<int> path;
        while (n--) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr == nullptr) {
                path.push_back(nptr);
                continue;
            }
            path.push_back(curr->val);
            q.push(curr->left);
            q.push(curr->right);
        }
        res.push_back(path);
    }
    res.pop_back();
    return res;
}
void PrintTree(TreeNode* root) {
    cout << "[";
    auto res = getVal(root);
    for (int i = 0;i < res.size() - 1;i++) {
        for (int j = 0;j < res[i].size();j++) {
            if (res[i][j] == nptr) {
                cout << "nullptr,";
            }
            else cout << res[i][j] << ",";
        }
    }
    for (int j = 0;j < res[res.size() - 1].size() - 1;j++) {
        if (res[res.size() - 1][j] == nptr) {
            cout << "nullptr,";
        }
        else cout << res[res.size() - 1][j] << ",";
    }
    int q = res.back().back();
    if (q != nptr) {
        cout << q;
    }
    else {
        cout << "nullptr";
    }
    cout << "]" << endl;
}

class Tree {
private:
    TreeNode* root;
public:
    Tree() :root(nullptr) {};
    Tree(TreeNode* _root) :root(_root) {};
    //delete
    ~Tree() {
        auto dfs = [&](auto&& dfs, TreeNode* node) {
            if (node == nullptr) return;
            dfs(dfs, node->left);
            dfs(dfs, node->right);
            delete node;
            };
        dfs(dfs, this->root);
    }
    //deep copy
    Tree(const Tree& t) {
        auto dfs = [&](auto&& dfs, TreeNode* node) ->TreeNode* {
            if (node == nullptr) return nullptr;
            TreeNode* newNode = new TreeNode(node->val);
            newNode->left = dfs(dfs, node->left);
            newNode->right = dfs(dfs, node->right);
            return newNode;
            };
        this->root = dfs(dfs, t.root);
    }
    TreeNode* getRoot() { return this->root; }
    // Initialize a binary tree
    TreeNode* CreatTree(const vector<int>& arr) {
        if (arr.size() == 0) {
            cerr << "数组为空！" << endl;
            exit(0);
        }
        if (arr[0] == nptr) {
            return nullptr;
        }
        int n = arr.size();
        queue<TreeNode*> q;
        int idx = 1;
        TreeNode* _root;
        _root = new TreeNode(arr[0]);
        q.push(_root);
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            if (idx < n) {
                if (arr[idx] != nptr) {
                    curr->left = new TreeNode(arr[idx]);
                    q.push(curr->left);
                }
                idx++;
            }
            if (idx < n) {
                if (arr[idx] != nptr) {
                    curr->right = new TreeNode(arr[idx]);
                    q.push(curr->right);
                }
                idx++;
            }
        }
        this->root = _root;
        return root;
    }
    TreeNode* CreatTree() {
        cout << "Please enter the level-order traversal sequence for the tree, with nullptr nodes represented by \"nullptr\", separated by commas" << endl;
        string target;
        cin >> target;
        vector<int> arr;
        int left = 0;
        for (int i = 0;i < target.size();i++) {
            if (target[i] == ',') {
                string part = target.substr(left, i - left);
                if (part == "nullptr") {
                    arr.push_back(nptr);
                }
                else {
                    arr.push_back(stoi(part));
                }
                left = i + 1;
            }
        }
        string part = target.substr(left, target.size() - left);
        if (part == "nullptr") {
            arr.push_back(nptr);
        }
        else arr.push_back(stoi(part));
        return CreatTree(arr);
    }
    void Print() {
        PrintTree(this->root);
    }
};


int main() {
    Tree* myTree = new Tree;
    myTree->CreatTree();
    myTree->Print();
    auto root = myTree->getRoot();
    
    return 0;
}