#ifndef QUEUE_H
#define QUEUE_H

#include "DoublyLinkedList.h"
// TODO: Define the Queue class
// Note: You can do everything in this file since the functions 
//can all be very small (hint: use your list funcitons!)

template <typename T>
class Queue{
    /*
    New elements can only be added at the end of the current queue
    Elements can only be removed from the front

    Simulates "First-come-first serve" behavior, aka First-in-First-Out
    */
    private:
        DoublyLinkedList<T> queue;
    public:
        bool empty(){
            if (queue.getLength() == 0){return true;}
            return false;
        }

        void push_back(T data){
            queue.insert(data, queue.getLength());
        }

        T pop_front(){
            // Copy the data from the front element:
            T returnThis = queue.getFront()->getData(); 
            // Remove the front element from the queue:
            queue.remove(0);
            // Return the copied data:
            return returnThis;
        }

        std::string toString(){return queue.toString();}
};

#endif