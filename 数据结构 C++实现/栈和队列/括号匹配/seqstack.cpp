#pragma once
#include <iostream>
const int increaseSize = 20;
template <class T>
class seqstack
{
public:
    seqstack(int sz)
    {
        top = -1;
        this->maxSize = sz;
        element = new T[maxSize];
    }
    bool isEmpty() { return (top == -1) ? true : false; }
    bool isFull() { return (top == maxSize - 1) ? true : false; }
    void Push(T &x);
    bool Pop(T &x);
    void overflow();

private:
    T *element;
    int top;
    int maxSize;
    int increaseSize;
};
template <class T>
void seqstack<T>::Push(T &x)
{
    if (this->isFull())
    {
        this->overflow();
    }
    top++;
    this->element[top] = x;
}
template <class T>
bool seqstack<T>::Pop(T &x)
{
    if (this->isEmpty())
    {
        return false;
    }
    x = this->element[top];
    top--;
    return true;
}
template <class T>
void seqstack<T>::overflow()
{
    int newSize = this->maxSize + increaseSize;
    T *newArr = new T[newSize];
    for (int i = 0; i < maxSize; i++)
    {
        newArr[i] = this->element[i];
    }
    delete[] this->element;
    this->element = newArr;
    this->maxSize = newSize;
}
