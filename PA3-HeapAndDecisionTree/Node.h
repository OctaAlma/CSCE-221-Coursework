#ifndef NODE_H
#define NODE_H

// TODO: Define the Node class
// Note: Since the functions are all small, you can put everything in this file
template <typename T>
class Node{
    private:
        T packet;
        Node<T>* next;
        Node<T>* prev;
    public:
        Node(const T& d):packet(d),next(nullptr),prev(nullptr){}
        //Getters:
        T getData(){return this->packet;}
        Node<T>* getNext(){return this->next;}
        Node<T>* getPrev(){return this->prev;}

        // Updater thingies:
        void setData(const T& d){this->packet = d;}
        void setNext(Node<T>* n){this->next = n;}
        void setPrev(Node<T>* p){this->prev = p;}
};

#endif