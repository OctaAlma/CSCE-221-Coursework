#ifndef CHAINING_H
#define CHAINING_H

#include "HashTable.h"
#include "Hash.h"
#include <string>

using std::string;

struct Node{
    Cell<string, int> c; 
    Node* next;
    Node(string k, int val):c(k,val),next(nullptr){}
};

// Linear probing hash table class
// TODO: modify the class to use public inheritance from the base class HashTable
// Note that you'll need to specify the key and value types to instantiate the template
class ChainingHashTable : HashTable<string, int> {
private:
    // TODO: create the table data member, should be a list of Cell objects (defined in HashTable.h)
    // You may create a pointer and use a dynamic array or vector
    // For the dynamic array, manage new and delete with the constructors and destructors
    // For the vector, be sure to set the size to capacity in the constructor so you can direct index
    Node** table;
public: 
    // TODO: add the constructors & destructors as specified
    ChainingHashTable(): table(nullptr){
        this->capacity = 0;
        this->size = 0;
    }

    ChainingHashTable(int cap):table(nullptr){
        table = new Node*[cap];
        this->capacity = cap;
        this->size = 0;

        // Initialize every cell in the table to a nullptr
        // since it will make identifying empty cells easier:
        for (int i = 0; i < cap; i++){
            table[i] = nullptr;
        }
    }

    ~ChainingHashTable(){
        for (int i = 0; i < capacity; i++){
            deleteLinkedList(table[i]);
        }
        delete [] table;
    }

    void deleteLinkedList(Node* root){
        if (!root){
            return;
        }else{
            deleteLinkedList(root->next);
            delete root;
        }
    }

    // TODO: include declarations to override the pure vritual functions from the base class
    unsigned int hash(string key){ return Hash::PRH24(key)%capacity; }

    void insert(string key, int val);

    int remove(string key);

    int get(string key);

    void printAll(std::string filename);

    int operator[](string key){
        return get(key);
    }
};

#endif