#include<stack>
#include<vector>
template <class T>
struct Node{
    T data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node():leftChild(NULL),rightChild(NULL){};
};

template<class T>
void preTraversal(Node<T>* root,std::vector<T>& vec){
    Node<T>*p;
    std::stack<Node<T>*> st;
    if(root==NULL) return;
    st.push(root);
    while(st!=NULL){
        p=st.top();
        st.pop();
        vec.push_back(p);
        if(p->rightChild!=NULL) st.push(p->rightChild);
        if(p->leftChild!=NULL) st.push(p->leftChild);
    }
}


template<class T>
void inordertraversal(Node<T>* root, std::vector<T>& vec) {
    std::stack<Node<T>*> st;
    Node<T>* p = root;
    while(p!=NULL||!st.empty()){
        while(p!=NULL){
            st.push(p);
            p=p->leftChild;
        }
        if(!st.empty()){
            st.pop(p);
            p=p->rightChild;
        }
    }
}