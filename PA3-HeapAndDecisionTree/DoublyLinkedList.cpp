#include "DoublyLinkedList.h"
#include "DNode.h"
#include <sstream>
// TODO: Write the source functions for the DoublyLinkedList

template <typename T>
void DoublyLinkedList<T>::copy(DoublyLinkedList<T> &other){
    Node<T> *newNode, *prevNode, *currNode;
    
    prevNode = nullptr;
    currNode = other.head;
    
    for (int i = 0; i < other.getLength(); i++){
        newNode = new Node<T>(currNode->getData());

        // If we are copying the first node, set the head:
        if (i == 0){
            this->head = newNode;
            newNode->setPrev(nullptr);
        }

        // If we are AT LEAST in the second node,
        // set the previous node's next, and this node's prev
        if (i > 0){
            prevNode->setNext(newNode);
            newNode->setPrev(prevNode);    
        }

        // If we are in the last node, set the tail:
        if (i == other.getLength()-1){
            this->tail = newNode;
            newNode->setNext(nullptr);
        }

        currNode = currNode->getNext();
        prevNode = newNode;
    }

    this->size = other.size;
}

template <typename T>
void DoublyLinkedList<T>::clear(){
    Node<T> *currNode, *tempNode;
    currNode = this->head;

    while (currNode){
        tempNode = currNode->getNext();
        delete currNode;
        currNode = tempNode;
    }

    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::insert(T data, int index){
    // There's some main possiblities:

    // Out of range:
    if ((index > this->size) || (index < 0)){
        throw std::out_of_range("Index outside of list bounds");
    }

    Node<T> *newNode, *currNode, *nextNode; 
    newNode = new Node<T>(data);

    // At the beginning of the list:
    if (index == 0){
        currNode = this->head;
        // If the list is empty
        if (currNode == nullptr){
            this->head = newNode;
            this->tail = newNode;

            newNode->setNext(nullptr);
            newNode->setPrev(nullptr);
        }else{
            currNode->setPrev(newNode);
            newNode->setNext(currNode);
            this->head = newNode;
        }
        this->size++;
        return;
    }

    // At the end of the list:
    if (index == this->size){
        currNode = this->getBack();

        currNode->setNext(newNode);
        newNode->setPrev(currNode);
        newNode->setNext(nullptr);

        this->tail = newNode;
        this->size++;
        return;
    }

    // Somewhere in the middle:{
    for (int i = 0; i < index; i++){
        if (i == 0){
            currNode = this->getFront();
            nextNode = currNode->getNext();
            continue;
        }
        currNode = nextNode;
        nextNode = nextNode->getNext();
    }

    currNode->setNext(newNode);    
    newNode->setPrev(currNode);

    nextNode->setPrev(newNode);
    newNode->setNext(nextNode);

    this->size++;
    //}
}

template <typename T>
void DoublyLinkedList<T>::remove(int index){
    // Some main possibilities:

    // Out of range:
    if ((index >= this->size) || (index < 0) || (this->size == 0)){
        throw std::out_of_range("Index outside of list bounds");
    }

    Node<T> *prevNode, *nodeToRemove, *nextNode;
    
    // Remove the head:
    if (index == 0){
        nodeToRemove = this->head;
        nextNode = nodeToRemove->getNext();

        delete nodeToRemove;

        // The list could have consisted of the node we removed.
        // This means nextNode can be null. Checking for that:
        if (nextNode){
            nextNode->setPrev(nullptr);
        }

        this->head = nextNode;
        this->size--;
        return;
    }

    // Remove the tail:
    if (index == this->size-1){
        nodeToRemove = this->getBack();
        prevNode = nodeToRemove->getPrev();

        delete nodeToRemove;

        if (prevNode){
            prevNode->setNext(nullptr);
        }

        this->tail = prevNode;
        this->size--;
        return;
    }

    // Remove something in the middle:
    for (int i = 0; i <= index; i++){
        // This for loop will find nodeToRemove
        if (i == 0){
            nodeToRemove = this->head;
            continue;
        }
        nodeToRemove = nodeToRemove->getNext();
    }

    // Once we exit the for loop, nodeToRemove should be
    // what we need to get rid of. So now we do that:

    prevNode = nodeToRemove->getPrev();
    nextNode = nodeToRemove->getNext();

    delete nodeToRemove;

    prevNode->setNext(nextNode);
    nextNode->setPrev(prevNode);
    this->size--;
}

/*template <typename T>
std::string DoublyLinkedList<T>::toString(){
    std::stringstream strStream;
    strStream.clear();
    
    Node<T> *currNode = this->getFront();
    while (currNode){
        strStream << currNode->getData();
        strStream << ' ';
        currNode = currNode->getNext();
    }

    return strStream.str();
}*/

// Made an at method to access specific elements in the list
template <typename T>
T DoublyLinkedList<T>::at(int index){
    if ((index >= this->size) || (index < 0) || (this->size == 0)){
        throw std::out_of_range("Index outside of list bounds");
    }

    // Iterate through the list until we get to the specified node:
    Node<T> *currNode;
    for (int i = 0; i <= index; i++){
        if (i == 0){
            currNode = this->getFront();
            continue;
        }
        currNode = currNode->getNext();
    }
    // Return the data in the node:
    return currNode->getData();
}

template class DoublyLinkedList<int>;
template class DoublyLinkedList<DNode*>;
template class DoublyLinkedList<std::string>;
