template <class T>
struct LinkNode
{
    T data;
    T *link;
};
template <class T>
class myqueue
{
public:
    // bool isFull() 是链表 不需要队满判断
    bool isEmpty() const { return (fronr == NULL) ? true : false; }
    void push(T& x){
        LinkNode<T>*newNode=new LinkNode<T>;
        newNode->data=x;
        newNode->link=front;
        rear->link=newNode;
        rear=newNode;
    }
    bool pop(T x){
        if(this->isEmpty()) return false;
        else{
            LinkNode<T>* temp=front;
            x=temp->data;
            front=front->link;
            delete temp;
            return true;
        }
    }
private:
    LinkNode<T> *front,*rear;
};