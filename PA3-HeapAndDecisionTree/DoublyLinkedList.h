#ifndef doublyLinkedList
#define doublyLinkedList

#include <iostream>
#include "Node.h"

// TODO: Define the DoublyLinkedList class
template <typename T>
class DoublyLinkedList{
    private:
        Node<T> *head, *tail;
        int size;
    public:
        // Regular constructor:
        DoublyLinkedList(): head(nullptr), tail(nullptr), size(0){}

        // Rule of 3: Destructor, copy constructor copy assignment
        void copy(DoublyLinkedList<T> &other);
        void clear();

        T at(int index);

        // Destuctor:
        ~DoublyLinkedList(){this->clear();}

        // Copy constructor:
        DoublyLinkedList(DoublyLinkedList& other){this->copy(other);}

        // Copy assignment:
        DoublyLinkedList& operator=(DoublyLinkedList& rhs){
            this->clear();
            this->copy(rhs);

            return *this;
        } 

        int getLength(){return this->size;}
        Node<T> *getFront(){return this->head;}
        Node<T> *getBack(){return this->tail;}

        // Should be able to handle: empty, front, middle, back
        // Remember to update the pointers!
        // If index is out of range, throw std::out_of_range with the message "Index outside of list bounds"
        void insert(T data, int index);
        
        // Removes the node at the specified index. Must be able to handle: front, middle, back!
        // If index is out of range, throw std::out_of_range with the message “Index outside of list bounds”.
        void remove(int index);

        // Converts the list to a string. The network package has a << operator.
        // You should probs make a stringstream and then use that thing's toString() function.
        std::string toString();


};

#endif