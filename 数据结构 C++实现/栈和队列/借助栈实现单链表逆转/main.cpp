//借助栈实现单链表逆转
template<class T>
struct LinkNode{
    T*link;
    T data;
};

template<class T>
LinkNode<T>* reverseList(LinkNode<T>* first){
    int top=-1;
    int size=0;
    LinkNode<T>* current=first;
    while(current!=NULL){
        size++;
        current=current->link;
    }
    current=first;
    T stack[size];
    while (current!=NULL)
    {
        top++;
        stack[top]=current->data;
        current=current->link;
    }
    LinkNode<T>* newFirst=new LinkNode<T>;
    current=newFirst;    
    while(top!=-1)
    {
        LinkNode<T>* newNode=new LinkNode<T>;
        newNode->data=stack[top];
        top--;
        current->link=newNode;
        current=current->link
    }
    delete[] stack;
    return newFirst;
}