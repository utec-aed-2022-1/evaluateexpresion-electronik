#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>

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

    void killSelf(){
        delete next;
        delete prev;
    }    
};

// TODO: Implement all methods
template <typename T>
class ForwardList {
    private:
        Node<T>* head;
        int nodes;

    public:
        ForwardList() : nodes(0), head(nullptr){ // *
            nodes = 0;
            this->head = nullptr;
        }

        ~ForwardList(){ // *
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                while(temp != nullptr){
                    temp = this->head->next;
                    delete head;
                    this->head = temp;
                }
            }
        }

        virtual T front() = 0;

        //virtual T back() = 0;

        virtual void push(T data) = 0;

        virtual T pop() = 0;

        void display(){
            std::cout<<"[ ";
            Node<T>* temp = head;
            for(int i=0; i <= nodes-1; i++){
                std::cout<<temp->data<<" ";
                temp = temp->next;
            }
            std::cout<<"]"<<std::endl;
        }     

        void push_back(T data){ // *
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                for(int i = 0; i < this->nodes - 1; i++){
                    temp = temp->next;
                }
                Node<T>* node = new Node<T>(data);
                temp->next = node;
                nodes++;
            } else{
                throw ("Lista vacía");
            }
        }

        T pop_back(){ // *
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                int i = nodes-2;
                do{
                    temp = temp->next;
                    i--;
                }while(i != 0);
                
                delete &i;
                T data = temp->next->data;
                temp->next = nullptr;
                delete temp;
                nodes--;
                return data;
            } else{
                throw ("Lista vacía");
            }
        }

        T insert(T data, int pos){
            if(!this->is_empty() && pos < this->nodes){
                Node<T>* temp = this->head;
                int i = pos-1;
                do{
                    temp = temp->next;
                    --i;
                }while(i != 0);

                delete &i;
                Node<T>* node = new Node<T>(data);
                node->next = temp->next;
                temp->next = node;
                nodes++;
                return data;
            } else{
                throw ("Lista vacía");
            }
        }

        bool remove(int pos){ // *
            if(!this->is_empty() && pos < this->nodes){
                Node<T>* temp = this->head;
                for(int i = 0; i < pos - 1; i++){
                    temp = temp->next;
                }
                Node<T>* node = temp->next;
                temp->next = temp->next->next;
                delete node;
                nodes--;
                return true;
            } else{
                throw ("Lista vacía");
            }
        }        
                
        T& operator[](int pos){
            if(!this->is_empty() && pos < this->size()){
                Node<T>* temp = this->head;
                for(int i = 0; i < pos; i++){
                    temp = temp->next;
                }
                return temp->data;
            } else{
                throw ("Lista vacía.");
            }
        }

        bool is_empty(){
            return this->head == nullptr;
        }

        // int size(){} // Herencia

        void clear(){ // *            
            if(!this->is_empty()){
                for(int i = 0; i < this->nodes - 1; i++){
                    Node<T>* temp = this->head;
                    this->head = this->head->next;
                    delete temp;
                    nodes--;
                }
            } else{
                throw ("Lista vacía");
            }
        }
        
        void sort(){ //
            if(!this->is_empty() /* && this->is_sorted() = false && this->nodes == 1*/){
                Node<T>* temp = this->head;        
                for(int i = 0; i < this->size() - 1; i++){
                    if(temp->data < temp->next->data){
                        temp = temp->next;
                    } else{
                        T aux = temp->data;
                        temp->data = temp->next->data;
                        temp->next->data = aux;
                        temp = temp->next;
                    }
                }
            } else{
                throw ("Lista vacía.");
            }

        }

        bool is_sorted(){ // LISTO
            if(head != nullptr){
                T prev = head->data;
                for(Node<T>* temp = head->next; temp!=nullptr; temp=temp->next){
                    if(temp->data < prev)
                        return false;
                    prev = temp->data;
                }
                return true;
            }
            else
                throw("Lista vacía.");
        }

        void reverse(){ // REVISAR
            Node<T>* temp = this->head;
            T dato;
            for (int n = 0; n < nodes; ++n){
                dato = pop_back();
                insert(dato, n);
            }
        }

        std::string name(){
            return "ForwardList";
        }
        
};

#endif