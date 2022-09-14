#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "HashTable.h"
#include "Hash.h"
#include <string>

using std::string;

// Linear probing hash table class
// TODO: modify the class to use public inheritance from the base class HashTable
// Note that you'll need to specify the key and value types to instantiate the template
class ProbingHashTable : HashTable<string, int> {
private:
    // TODO: create the table data member, should be a list of Cell objects (defined in HashTable.h)
    // You may create a pointer and use a dynamic array or vector
    // For the dynamic array, manage new and delete with the constructors and destructors
    // For the vector, be sure to set the size to capacity in the constructor so you can direct index
    Cell<string, int>* table;
public: 
    // TODO: add the constructors & destructors as specified
    ProbingHashTable(): table(nullptr){
        this->capacity = 0;
        this->size = 0;
    }

    ProbingHashTable(int cap):table(nullptr){
        table = new Cell<string, int>[cap];
        this->capacity = cap;
        this->size = 0;

        // We should initialize each of the Cell's value to 0 since
        // it will make finding empty cells easier:
        for (int i = 0; i < capacity; i++){
            // strings are constructed to empty strings by default
            table[i].value = 0;
        }
    }

    ~ProbingHashTable(){delete [] table;}

    // TODO: include declarations to override the pure vritual functions from the base class
    unsigned int hash(string key){ return Hash::PRH24(key)%capacity; }

    void insert(string key, int val);

    int remove(string key);

    int get(string key);

    int operator[](string key){
        return get(key);
    }

    void printAll(std::string filename);
};

#endif