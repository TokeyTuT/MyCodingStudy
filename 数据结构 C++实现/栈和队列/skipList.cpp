#include<iostream>
#include<vector>
#include<climits>
#define MAX_LEVEL 5

using namespace std;

//定义节点
class ListNode {
public:
    ListNode* next;
    int key; // 节点的键值，方便查找
    int val;
    //forwards 每一层的指针数组，用于指向下一层
    vector<ListNode*> forwards;
    ListNode():key(-1),val(INT_MIN),next(nullptr){}
    ListNode(int k, int v, int level) {
        key = k;
        val = v;
        forwards.resize(level, nullptr);
        next = nullptr;
    }
};

class skipList {
private:
    ListNode* head;
    int level;

    //创建伪随机数，对每个节点 level 进行随机
    int creatRandomLevel() {
        int k = 0;
        while (rand() % 2) {
            k++;
        }
        return k > MAX_LEVEL ? MAX_LEVEL - 1 : k;
    }
public:
    //默认构造函数
    skipList() {
        head = new ListNode(INT_MAX, 0, MAX_LEVEL - 1);
        for (auto& f : head->forwards) {
            f = nullptr;
        }
        level = 0;
    }
    //有参构造函数
    skipList(ListNode* head, int level) {
        this->level = level;
        this->head = head;
    }
    // 析构函数，释放内存
    ~skipList() {
        ListNode* curr = head;
        while (curr != nullptr) {
            auto tmp = curr->next;
            // vector数组会手动析构，不必在意
            delete curr;
            curr = tmp;
        }
    }

    //插入节点
    ListNode* insertNode(int key, int val) {
        
    }
};

int main() {
    skipList* sl = new skipList();
    delete sl;
    return 0;
}