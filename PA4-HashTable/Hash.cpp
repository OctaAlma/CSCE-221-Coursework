#include "Hash.h"

// TODO: implement the hash function (remember to namespace to Hash::)

unsigned int Hash::PRH24(std::string s){
    // Takes in a string and returns an unsigned integer
    
    // p = 137, m = 16,777,215, hash starts at 0:
    unsigned int p = 1;
    unsigned int m = 16777215;
    unsigned int hash = 0;

    for (auto i = s.begin(); i != s.end(); i++){
        hash = (hash + ((*i) * p)) % m;
        p = (p*137) % m;
    }

    return hash;
}