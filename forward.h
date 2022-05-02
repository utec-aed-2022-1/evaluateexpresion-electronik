#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "node.h"

// TODO: Implement all methods
template <typename T>
class ForwardList{
    private:
        Node<T>* head;
        int nodes;

    public:
        ForwardList(){ // *
            this->nodes = 0;
            this->head = nullptr;
        }

        ~ForwardList(){
            this->clear();	            
        }

        T front(){
            if(!this->is_empty()){
                return this->head->data;
            } else{
                throw ("Lista vacía");
            }
        }

        T back(){           
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                for(int i = 0; i < this->nodes - 1; i++){
                    temp = temp->next;
                }
                return temp->data;
            } else{
                throw ("Lista vacía");
            } 
        }

        void push_front(T data){
            Node<T>* node = new Node<T>(data);
            node->data = data;
            node->next = this->head;
            this->head = node;
            nodes++;
        }

        void push_back(T data){
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                for(int i = 0; i < this->size()-1; i++){
                    temp = temp->next;
                }
                Node<T>* node = new Node<T>(data);
                temp->next = node;                
            } else{
                Node<T>* node = new Node<T>(data);
                node->data = data;
                this->head = node;
            }
            nodes++;
        }

        T pop_front(){
            if (!this->is_empty()){
                Node<T>* temp = this->head;
                this->head = this->head->next;
                this->nodes--;
                T data = temp->data;
                delete temp;
                return data;
            }
            else {
                throw ("Lista vacía.");
            }         
        }

        T pop_back(){
            if(!this->is_empty()){
                Node<T>* temp = this->head;
                for(int i = 0; i < this->nodes - 1; i++){
                    temp = temp->next;
                }
                T data = temp->data;
                delete temp;
                this->nodes--;
                return data;
            } else{
                throw ("Lista vacía");
            }
        }

        T insert(T data, int pos){
            if(!this->is_empty() && pos < this->nodes){
                Node<T>* temp = this->head;
                for(int i = 0; i < pos - 1; i++){
                    temp = temp->next;
                }
                Node<T>* node = new Node<T>(data);
                node->next = temp->next;
                temp->next = node;          
                nodes++;
                return data;
            } else{
                throw ("Lista vacía");
            }
        }

        bool remove(int pos){
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

        int size(){
            return this->nodes;
        }

        void clear(){          
            if(!this->is_empty()){
                int iter = this->size();
                for(int i = 0; i < iter; i++){
                    Node<T>* temp = this->head;
                    this->head = this->head->next;
                    delete temp;
                    this->nodes--;
                }
            }
        }
        
        void sort(){
            if(!this->is_empty()){
                bool isSorted = this->is_sorted();
                while(!isSorted){
                    isSorted = true;
                    Node<T>* temp = this->head;      
                    while(temp != nullptr && temp->next != nullptr){
                        if(temp->data > temp->next->data){
                            T aux = temp->data;
                            temp->data = temp->next->data;
                            temp->next->data = aux;
                            temp = temp->next;
                            isSorted = false;
                        }
                        temp = temp->next;
                    }
                }
            } else{
                throw ("Lista vacía.");
            }
        }

        bool is_sorted(){
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

        void reverse(){
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