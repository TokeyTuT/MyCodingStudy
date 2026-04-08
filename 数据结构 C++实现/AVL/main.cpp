#include<iostream>
// 平衡二叉搜索树
typedef struct Node
{
    int val;
    Node* left;
    Node* right;
    int height;
    Node(int _val) : val(_val), left(nullptr), right(nullptr), height(1) {}
} Node;
class AVLTree
{
private:
    Node* root;
    int max(int a, int b) { return a > b ? a : b; }
    int height(Node* n) { return n ? n->height : 0; }
    // 左旋
    Node* LeftRotation(Node* root)
    {
        Node* newroot = root->right;
        Node* temp = newroot->left;
        newroot->left = root;
        root->right = temp;
        // 更新树高
        root->height = 1 + max(height(root->left), height(root->right));
        newroot->height = 1 + max(height(newroot->left), height(newroot->right));
        return newroot;
    }
    // 右旋
    Node* RightRotation(Node* root)
    {
        Node* newroot = root->left;
        Node* temp = newroot->right;
        newroot->right = root;
        root->left = temp;
        root->height = 1 + max(height(root->left), height(root->right));
        newroot->height = 1 + max(height(newroot->left), height(newroot->right));
        return newroot;
    }
    // 获取平衡因子
    int getBalance(Node* node) { return height(node->left) - height(node->right); }
    //插入
    Node* InsertHelper(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (node->val > key) node->left = InsertHelper(node->left, key);
        else if (node->val < key) node->right = InsertHelper(node->right, key);
        else return node; // 已存在，不插入
        //更新高度
        node->height = 1 + max(height(node->left), height(node->right));
        //平衡操作
        int balance = getBalance(node);
        // LL
        if (balance > 1 && getBalance(node->left) >= 0) return RightRotation(node);
        // LR
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = LeftRotation(node->left);
            return RightRotation(node);
        }
        // RR
        if (balance < -1 && getBalance(node->right) <= 0) return LeftRotation(node);
        // RL
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = RightRotation(node->right);
            return LeftRotation(node);
        }
        return node;
    }
    // 删除（返回新根）
    Node* DelHelper(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->val) node->left = DelHelper(node->left, key);
        else if (key > node->val) node->right = DelHelper(node->right, key);
        else {
            // 找到要删除的节点
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) { // 无子
                    delete node;
                    return nullptr;
                }
                else { // 有一个子
                    delete node;
                    return temp;
                }
            }
            else {
                // 两个子，使用右子树的最小值（中序后继）
                Node* curr = node->right;
                while (curr->left) curr = curr->left;
                node->val = curr->val;
                node->right = DelHelper(node->right, curr->val);
            }
        }
        // 更新高度
        node->height = 1 + max(height(node->left), height(node->right));
        // 平衡操作
        int balance = getBalance(node);
        // LL
        if (balance > 1 && getBalance(node->left) >= 0) return RightRotation(node);
        // LR
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = LeftRotation(node->left);
            return RightRotation(node);
        }
        // RR
        if (balance < -1 && getBalance(node->right) <= 0) return LeftRotation(node);
        // RL
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = RightRotation(node->right);
            return LeftRotation(node);
        }
        return node;
    }
    //前序
    void PreTraveseralHelper(Node* node) {
        if (node == nullptr) return;
        std::cout << node->val << "  ";
        PreTraveseralHelper(node->left);
        PreTraveseralHelper(node->right);
    }
    //中序
    void InorderedTraversalHelper(Node* node) {
        if (node == nullptr) return;
        InorderedTraversalHelper(node->left);
        std::cout << node->val << "  ";
        InorderedTraversalHelper(node->right);
    }
    //查找
    int FindHelper(Node* node, int key, int& count) {
        Node* curr = node;
        count = 0;
        while (curr) {
            count++;
            if (curr->val == key) return count;
            else if (curr->val > key) curr = curr->left;
            else curr = curr->right;
        }
        return 0;
    }
public:
    //初始化
    AVLTree(int key) { root = new Node(key); }
    // 插入
    void Insert(int key) { root = InsertHelper(this->root, key); }
    //删除
    void Delete(int key) { root = DelHelper(root, key); }
    //前序
    void PreTraveral() { PreTraveseralHelper(root); }
    //中序
    void InorderedTraversal() { InorderedTraversalHelper(root); }
    //查找
    int Find(int key, int& count) { return FindHelper(root, key, count); }
};

int main() {
    AVLTree t(10);
    t.Insert(20);
    t.Insert(30);
    t.Insert(40);
    t.Insert(50);
    t.Insert(60);
    std::cout << "-------------前序遍历------------" << std::endl;
    t.PreTraveral();
    std::cout << "\n-------------中序遍历------------" << std::endl;
    t.InorderedTraversal();
    return 0;
}