#include "ChainingHashTable.h"
#include <stdexcept>
#include <fstream>

void ChainingHashTable::insert(string key, int val){
    if (!table){return;}

    unsigned HASH = hash(key);

    Node* curr = table[HASH];
    if (!curr){
        table[HASH] = new Node(key,val);
        return;
    }else{
        if (curr->c.key == key){
            curr->c.value = val;
            return;
        }
        while (curr->next){
            if (curr->next->c.key == key){
                curr->c.value = val;
                return;
            }
            curr = curr->next;
        }
        curr->next = new Node(key, val);
    }
}

int ChainingHashTable::remove(string key){
    if (!table){
        return 0;
    }
    int returnMe = 0;

    Node* curr = table[hash(key)];
    if (!curr){
        return 0;
    }else if (curr->c.key == key){
        returnMe = curr->c.value;
        table[hash(key)] = curr->next;
        delete curr;
        return returnMe;
    }else{
        while (curr->next){
            if (curr->next->c.key == key){
                Node* temp = curr->next;
                curr->next = temp->next;
                returnMe = temp->c.value;
                delete temp;
                return returnMe;
            }
            curr = curr->next;
        }
    }
    return returnMe;
}

int ChainingHashTable::get(string key){
    if (!table){
        return 0;
    }

    Node* curr = table[hash(key)];
    while (curr){
        if (curr->c.key == key){
            return curr->c.value;
        }
        curr = curr->next;
    }
    return 0;
}

void ChainingHashTable::printAll(string fileName){
    std::ofstream file;
    file.open(fileName);
    Node* curr;
    for (int i = 0; i < capacity; i++){
        curr = table[i];
        if (!curr){continue;}
        while (curr){
            file << curr->c.key << " " << curr->c.value << std::endl;
            curr = curr->next;
        }
    }
    file.close();
}