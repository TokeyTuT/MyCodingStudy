// 这里只写循环队列
#define MAX_SIZE 10
#include <iostream>

template <class T>
class Qunue
{
public:
    Qunue();
    Qunue(const Qunue &);
    // 析构函数
    ~Qunue() { this->makeEmpty(); }
    bool isFull() { return (rear + 1) % MAX_SIZE == front; }
    bool isEmpty() { return rear == front; }
    bool push(T &x);
    bool pop(T &x);
    void makeEmpty(){delete[] data;}
    friend std::ofstream &operator<<(std::ofstream &os, T &x);

private:
    T* data;
    int front; // 头
    int rear;  // 尾
};

template <class T>
Qunue<T>::Qunue()
{
    data = new T[MAX_SIZE];
    if(data=NULL){
        std::cerr<<"内存分配错误!"<<std::endl;
        exit(1);
    }
    front = 0;
    rear = 0;
}

template <class T>
Qunue<T>::Qunue(const Qunue &q)
{
    if (q.front == q.rear)
        return;
    this->data = new T[MAX_SIZE];
    if(data=NULL){
        std::cerr<<"内存分配错误!"<<std::endl;
        exit(1);
    }
    for (int i = q.front; q != rear;)
    {
        i = (i + 1) % MAX_SIZE;
        this->data[i] = q.data[i];
    }
}
template <class T>
bool Qunue<T>::push(T& x)
{
    if(!this->isFull()) return false;
    this->front++;
    this->data[front]=x;
    return true;
}
template<class T>
bool Qunue<T>::pop(T&x){
    if(!this->isEmpty()) return false;
    x=this->data[rear];
    this->rear--;//逻辑上删除即可
    return true;
}
template<class T>
std::ofstream& operator<<(std::ofstream& os,const Qunue<T>& q){
    for(int i=q.front;q!=rear;){
        q=(q+1)%MAX_SIZE;
        os<<q.data[i]<<"  ";
    }
    return os;
} 