#include <vector>
#include <iostream>

class Queue
{
public:
    Queue(int k) : count(0), capacity(k) { data = new int[capacity]; }
    bool isFull() { return (count == capacity) ? true : false; }
    bool isEmpty() { return (count == 0) ? true : false; }
    void push(int x)
    {
        if (isFull())
            this->pop();
        rear = (rear + 1) % capacity;
        data[rear] = x;
        count++;
    }
    void pop()
    {
        if (isEmpty())
            return;
        this->count--;
        front = (front + 1) % capacity;
    }
    friend std::ostream &operator<<(std::ostream &, Queue);

private:
    int *data;
    int count;
    int capacity;
    int front;
    int rear;
};

int fib(int n)
{
    if (n <= 2)
        return 1;
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

Queue setK_Fiber(int k, int max)
{
    // std::vector<int> Saved(n, -1);
    Queue q(k);
    int n = 0;
    while (!(fib(n) < max && fib(n + 1) > max))
    {
        n++;
        std::cout << fib(n) << std::endl;
        q.push(fib(n));
    }
    return q;
}
std::ostream &operator<<(std::ostream &os, Queue q)
{
    for (int i = 0; i < q.count; i++)
    {
        os << q.data[i] << "  ";
    }
    return os;
}
int main()
{
    Queue q = setK_Fiber(4, 100);
    std::cout << q;
}