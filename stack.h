#include <iostream>
using namespace std;

template <typename T>
class Stack { 
    private:
    T *array;
    int capacity;
    int front;

    public:
        Stack(int _capacity);
        ~Stack();
        void push(T data);
        bool empty();
        T pop();
        T top();
        
};

template <class T>
Stack<T>::Stack(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = -1;
}

template <class T>
Stack<T>::~Stack()
{
    delete[] this->array;
}

template <class T>
void Stack<T>::push(T data){
    if(!this->empty()){
        this->front = this->front + 1;
        this->array[this->front] = data;
    } else{
        this->array[0] = data;
        this->front = this->front = 0;
    }
}

template <class T>
T Stack<T>::pop(){
    if(!this->empty()){
        T poppedValue = this->array[this->front];
        this->front--;
        return poppedValue;
    } else{
        throw ("Empty stack."); // Esto debería dar error.
    }
}

template <class T>
bool Stack<T>::empty(){
    return (this->front == -1);
}

template <class T>
T Stack<T>::top(){
    return this->array[this->front];
}