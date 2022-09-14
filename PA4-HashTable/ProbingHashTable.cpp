#include "ProbingHashTable.h"
#include <stdexcept>
#include <fstream>

void ProbingHashTable::insert(string key, int val){
    if (!table){return;}

    unsigned int hashVal = hash(key);

    if (table[hashVal].key == key){
        table[hashVal].value = val;
        return;

    }else{
        for (unsigned int i = hashVal; i < this->capacity; i++){
            // If we find the key in a linear probe, just update value:
            if (table[i].key == key){
                table[i].value = val;
                return;
            }

            // If we find an empty space, just insert the key/val pair:
            if (!table[i].value){
                table[i].key = key;
                table[i].value = val;
                return;
            }
        }

        // Repeat the process from 0 - hash(key):
        for (unsigned int i = 0; i < hashVal; i++){
            // If we find the key in a linear probe, just update value:
            if (table[i].key == key){
                table[i].value = val;
                return;
            }

            // If we find an empty space, just insert the key/val pair:
            if (!table[i].value){
                table[i].key = key;
                table[i].value = val;
                return;
            }
        }

    }
}

int ProbingHashTable::remove(string key){
    if (!table){
        throw std::runtime_error("");
    }

    unsigned int hashVal = hash(key);
    int returnMe;

    if (table[hashVal].key == key){
        returnMe = table[hashVal].value;
        table[hashVal].value = 0;
        table[hashVal].key = "";
        return returnMe;
    }

    for (unsigned i = hashVal; i < capacity; i++){
        
        if (!table[i].value){
            throw std::runtime_error("");
        }

        if (table[i].key == key){
            returnMe = table[i].value;
            table[i].value = 0;
            table[i].key = "";
            return returnMe;
        }
    }

    for (unsigned i = 0; i < hashVal; i++){
        
        if (!table[i].value){
            throw std::runtime_error("");
        }

        if (table[i].key == key){
            returnMe = table[i].value;
            table[i].value = 0;
            table[i].key = "";
            return returnMe;
        }
    }
}

int ProbingHashTable::get(string key){
    if (!table){return 0;}

    if (table[hash(key)].key != key){
        // if the key is not there, we need to probe the next one:
        bool foundEmpty = false;

        for (unsigned int i = hash(key); i < capacity; i++){
            // If we find an empty space in the table, the key is not in the table:
            if (!table[i].value){ 
                foundEmpty = true;
                break;
            }
            // If we find the key, return the value:
            if (table[i].key == key){
                return table[i].value;
            }
        }

        if (foundEmpty){return 0;}
        
        for (unsigned int i = 0; i < hash(key); i++){
            if (!table[i].value){
                break;
            }
            if (table[i].key == key){
                return table[i].value;
            }
        }

    }else if (table[hash(key)].key == key){
        return table[hash(key)].value;
    }

    return 0;
}

void ProbingHashTable::printAll(string filename){
    std::ofstream file;
    file.open(filename);
    for (unsigned int i = 0; i < capacity; i++){
        if (!table[i].value){continue;}
        file << table[i].key << " " << table[i].value << std::endl;
    }
    file.close();
}