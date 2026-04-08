#include <queue>
#include <vector>
#include <iostream>
using namespace std;
struct Node
{
    char ch;
    Node *left;
    Node *right;
    int weight;
    Node(int m_weight) : weight(m_weight), left(nullptr), right(nullptr) {}
    Node(char m_ch, int m_weight) : ch(m_ch), weight(m_weight), left(nullptr), right(nullptr) {}
};
// 比较器
struct Mycomparison
{
    bool operator()(Node *node1, Node *node2)
    {
        return node1->weight > node2->weight;
    }
};

Node *CreatHuffmanTree(const vector<char> &_char, const vector<int> &_weight)
{
    // 初始化
    Node *newnode;
    priority_queue<Node *, vector<Node *>, Mycomparison> pq;
    for (int i = 0; i < _char.size(); i++)
    {
        newnode = new Node(_char[i], _weight[i]);
        pq.push(newnode);
    }
    while (pq.size() > 1)
    {
        Node *min1 = pq.top();
        pq.pop();
        Node *min2 = pq.top();
        pq.pop();
        Node *node = new Node(min1->weight + min2->weight);
        node->left = min1;
        node->right = min2;
        // 放入优先队列 下一次while循环使用
        pq.push(node);
    }
    // 队列中只剩一个元素了 即头节点
    return pq.top();
}
vector<char> code;
void PrintMyCode(Node *root)
{
    // 终止条件
    if (!root->left && !root->right)
    {
        cout << root->ch << ":" << root->weight << "code:";
        for (int i = 0; i < code.size(); i++)
        {
            cout << code[i];
        }
        cout << endl;
    }
    // 回溯法
    if (root->left)
    {
        code.push_back('0');
        PrintMyCode(root->left);
        // 回溯
        code.pop_back();
    }
    if (root->right)
    {
        code.push_back('1');
        PrintMyCode(root->right);
        // 回溯
        code.pop_back();
    }
}

int main()
{
    vector<char> _char = {'a', 'b', 'c', 'd'};
    vector<int> _weight = {3, 2, 2, 1};
    Node *root = CreatHuffmanTree(_char, _weight);
    PrintMyCode(root);
    return 0;
}
