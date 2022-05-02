#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){
        data = 0;
        next = prev = nullptr;
    }

    Node(T value){
        data = value;
        next = prev = nullptr;
    }
 
};

#endif