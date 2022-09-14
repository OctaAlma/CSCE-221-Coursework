#ifndef DNODE
#define DNODE
#include "DecisionLogic.h"
#include <iostream>

class DNode{
    public:
    
    DNode():depth(0),parent(nullptr),left(nullptr),right(nullptr){}
    Decision key;
    int depth;
    DNode* parent;
    DNode* left;
    DNode* right;
};
#endif