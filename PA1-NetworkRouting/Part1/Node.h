#ifndef NODE_H
#define NODE_H
#include "NetworkPacket.h"

// TODO: Define the Node class
// Note: Since the functions are all small, you can put everything in this file
class Node{
    private:
        NetworkPacket packet;
        Node* next;
        Node* prev;
    public:
        Node(const NetworkPacket& d):packet(d),next(nullptr),prev(nullptr){}
        //Getters:
        NetworkPacket getData(){return this->packet;}
        Node* getNext(){return this->next;}
        Node* getPrev(){return this->prev;}

        // Updater thingies:
        void setData(const NetworkPacket& d){this->packet = d;}
        void setNext(Node* n){this->next = n;}
        void setPrev(Node *p){this->prev = p;}
};

#endif