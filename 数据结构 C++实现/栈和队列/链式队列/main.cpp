#include <LinkNode.hpp>

template <class T>
class ListQunue
{
public:
    ListQunue() front(NULL), front(NULL) {};
    ListQunue(const ListQunue &);
    ~ListQunue() { this->makeEmpty(); }
    void makeEmpty();
    bool isEmpty() const { return (rear == front) ? true : false }
    void push(T &x);
    bool pop(T &x);
    int getSize()const;
    ListQunue<T>& operator=()
private:
    LinkNode<T> *front, *rear;
};

template <class T>
ListQunue<T>::ListQunue()
{
    rear = front = new LinkNode;
}

template <class T>
ListQunue<T>::ListQunue(const ListQunue &lq)
{
    LinkNode<T> *scrptr = lq.front;
    LinkNode<T> *rear = this->front;
    while (scrptr != NULL)
    {
        rear->link = new LinkNode;
        rear->data = scrptr->data;
        scrptr = scrptr->link;
        rear = rear->link;
    }
}

template <class T>
void ListQunue<T>::makeEmpty()
{
    LinkNode *del;
    while (front != NULL)
    {
        del = front;
        front = front->link;
        delete del;
    }
}
template <class T>
void ListQunue<T>::push(T &x)
{
    LinkNode<T> newNode = new LinkNode;
    newNode.data = x;
    rear->link = newNode;
    rear = newNode;
}
template<class T>
bool ListQunue<T>::pop(T& x){
    if(this->isEmpty())return false;
    LinkNode<T>* current=front;
    while(current->link!=rear){
        current=current->link;
    }
    rear=current;
    delete current->link;
    current->link=NULL;
    return true;
}
template<class T>
int ListQunue<T>::getSize()const{
    LinkNode<T>* current=front;
    int count=0;
    while(current!=nullptr){
        count++;
        current=current->link;
    }
}
