#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef struct TreeNode
{
    int val;
    TreeNode* left, * right;
    TreeNode(int _val) :val(_val), left(nullptr), right(nullptr) {};
    TreeNode(int _val, TreeNode* _left, TreeNode* _right) :val(_val), left(_left), right(_right) {};
};
void creatMyTree() {
    //用层序遍历造树
    queue<string> vals;
    string  val = "#";  //定义 # 代表nullptr
    while (val != "114514") {
        cin >> val;
        vals.push(val);
    }
    queue<TreeNode*>q;
    if (vals.front() != "#") q.push(new TreeNode(stoi(vals.front())));
    vals.pop();
    while (!q.empty()) {
        int n = q.size();
        while (n--) {
            TreeNode* node = q.front();
            string l = vals.front();
            TreeNode* left;
            vals.pop();
            string r = vals.front();
            TreeNode* right;
            vals.pop();
            if (l == "#") {
                left == nullptr;
            }
            else left = new TreeNode(stoi(l));
            node->left = left;
            if (r == '#') node->right = nullptr;
        }
    }
}
void Debugger(TreeNode* node) {
    queue<TreeNode*> q;
    vector<vector<string>> res;
    if (node) q.push(node);
    while (!q.empty()) {
        vector<string> path;
        int n = q.size();
        while (n--) {
            TreeNode* curr = q.front();
            q.pop();
            if (curr == nullptr)
            {
                path.push_back("nullptr");
                continue;
            }
            path.push_back(to_string(curr -> val));
            q.push(curr->left);
            q.push(curr->right);
        }
        res.push_back(path);
    }
}
void Print(vector<string>& res) {
    cout << "[  ";
    for (string s : res) {
        cout << s <<"  ";
    }
    cout << "]" << endl;
}
//感染二叉搜索树所需要的时间
int InfectBinaryTree(TreeNode*root,int start) {
    int res = 0;
    auto dfs = [&](auto&& dfs, TreeNode* node)->pair<int, bool> { //节点数 ， 是否遍历到了start
        if (node == nullptr) return { 0,false };
        auto [l_n,l_b] = dfs(dfs, node->left);
        auto [r_n,r_b] = dfs(dfs, node->right);
        if (node->val == start) {
            res = max(l_n + r_n, res);
            return { 1 ,true };
        }
        res = max(res, l_b + r_b);
        if (l_b) {
            return { l_b + 1,true };
        }
        if (r_b) {
            return { r_b + 1,true };
        }
        return { max{l_n,r_n} + 1,false };
        };
    dfs(dfs, root);
    return res;
}

