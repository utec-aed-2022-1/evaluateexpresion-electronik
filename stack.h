#include "forward.h"

template <typename T>
class Stack {
    private:
        Node<T>* head;
        int nodes;

    public:
        Stack(){
            this->nodes=0;
            this->head = nullptr;
        }
        T size(){
            return this->nodes;
        }

        T front(){
            if(!is_empty()){
                return this->head->data;
            } else{
                throw ("Lista vacía");
            }
        }

        T back(){ // *            
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

        T pop(){
            if (!this->is_empty()){
                T data = head->data;
                Node<T>* temp = this->head;
                this->head = this->head->next;
                temp->next = nullptr;
                
                delete temp;
                nodes--;
                return data;
            }
            else {
                throw ("Lista vacía.");
            }
        }
        
        void push(T data){
            Node<T>* node = new Node<T>(data);
            node->next = head;
            head = node;
            nodes++;
        }
        
        bool is_empty(){
            return this->head == nullptr;
        }
        
};