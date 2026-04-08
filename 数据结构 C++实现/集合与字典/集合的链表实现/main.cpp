struct Node
{
    int data;
    Node *link;
    Node(int _data) : data(_data), link(nullptr) {}
};

class Myset
{
private:
    // 附加头节点
    Node *first;
    Node *last;
    int size;

public:
    Myset()
    {
        this->first = new Node(-1);
        last = first;
        int size = 0;
    }
    bool Insert(int val)
    {
        Node *curr = first;
        while (curr)
        {
            if (curr->data == val)
                return false;
            if (curr->data < val && curr->link->data)
                break;
            curr = curr->link;
        }
        Node *temp = curr->link;
        Node *newNode = new Node(val);
        curr->link = newNode;
        newNode->link = temp;
        return true;
    }
    bool Del(int val)
    {
        Node *curr = first;
        Node *pre = nullptr;
        while (curr)
        {
            if (curr->data == val)
                break;
            pre == curr;
            curr = curr->link;
        }
        if (curr->data == val)
        {
            pre->link = curr->link;
            delete curr;
            return true;
        }
        else
            return false;
    }
    // 并集
    Myset operator+(const Myset &R)
    {
        this->size = 0;
        Node *pa = this->first;
        Node *pb = R.first;
        // p是最后结束的链表的节点的指针 pc是新指针
        Node *p, *pc = first; // 改变自己
        // 不需要创建新节点 在原基础上添加即可
        while (pa != nullptr && pb != nullptr)
        {
            if (pa->data == pb->data)
            {
                pc->link = pa;
                pa = pa->link;
                pb = pb->link;
            }
            else if (pa->data > pb->data)
            {
                pc->link = pb;
                pb = pb->link; // 不能再pa=pa->link 因为有可能pb下一个节点还是比pa->data 小!
            }
            else
            {
                pc->link = pa;
                pa = pa->link;
            }
            pc = pc->link;
            this->size++;
        }
        if (!pa)
            p = pa;
        else
            p = pb;
        while (p)
        {
            pc->link = p;
            p = p->link;
            pc = pc->link;
            this->size++;
        }
        pc->link = nullptr;
        this->last = p;
        return *this;
    }
    // 交集
    Myset operator*(const Myset &R)
    {
        this->size = 0;
        Node *pa = this->first;
        Node *pb = R.first;
        Node *p, *pc = first;
        while (pa && pb)
        {
            if (pa->data = pb->data)
            {
                pc->link = pa;
                pa = pa->link;
                pb = pb->link;
                pc = pc->link;
                this->size++;
            }
            else if (pa->data > pb->data)
            {
                pb = pb->link; // 不改变R只改变 this
            }
            else
            {
                p = pa;
                pa = pa->link;
                delete p;
            }
        }
        while (pa)
        {
            p = pa;
            pa = pa->link;
            delete p;
        }
        pc->link = nullptr;
        last = pc;
        return *this;
    }
    // 差
    Myset operator-(const Myset &R)
    {
        Node *pa = this->first;
        Node *pb = R.first;
        Node *p, *pc = first;
        this->size = 0;
        while (pa && pb)
        {
            if (pa->data == pb->data)
            {
                p = pa;
                pa = pa->link;
                delete p;
            }
            else if (pa->data > pb->data)
            {
                pc->link = pb;
                pb = pb->link;
                size++;
            }
            else
            {
                pc->link = pa;
                p = pa;
                pa = pa->link;
                size++;
                delete p;
            }
            pc = pc->link;
        }
        if (pa)
            p = pa;
        else
            p = pb;
        while (p)
        {
            pc->link = p;
            pc = pc->link;
            p = p->link;
            size++;
        }
        pc->link = nullptr;
        last = pc;
        return *this;
    }
    // 等于
    bool operator==(const Myset *R)
    {
        Node *pa = first->link;
        Node *pb = R->first->link;
        if (this->size != R->size || this->last->data != R->last->data)
            return false;
        while (pa != last && pb != last)
        {
            if (pa->data != pb->data)
                return false;
        }
        return true;
    }
};
