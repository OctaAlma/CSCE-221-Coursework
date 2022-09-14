#ifndef DTREE
#define DTREE
#include "MaxHeap.h"
#include "Queue.h"
#include "DNode.h"
#include <iostream>
#include <sstream>
using std::string;

class DTree{
    public:
    DNode* root = nullptr;      // Root of the tree, the default is nullptr
    int maxDepth = 10;          // Default max depth of the tree
    double delta = 0.000005;    // A very small delta and its default value, used comparing information gain

    Decision getMaxInformationGain(
        vector<string>& attributes,
        vector<vector<double>>& data,
        vector<int>& outcomes,
        vector<int>& instances
    ){
        /* iterates through the attributes vector and calls the provided getInformationGain()
        // for each attribute. If you are passing the attribute in attributes.at(i),
        // you will pass its corresponding data from data.at(i) to the getInformationGain() function,
        // along with the set of outcomes and instances being considered.

        // This function must utilize your max-heap to save the Decisions 
        // and return the one with the max information gain at the end*/

        MaxHeap<Decision> h;
        Decision d;
        for (int i = 0; i < attributes.size(); i++){
            d = getInformationGain(attributes.at(i),data.at(i),outcomes,instances);
            h.insert(d);
        }
        d = h.removeMax();
        return d;
    }

    void trainHelper
    (
    vector<string>& attributes, 
    vector<vector<double>>& data, 
    vector<int>& outcomes, 
    DNode* currNode)
    {

        if (!currNode){
            return;
        }
        
        if (currNode->depth == this->maxDepth){
            return;
        }
        
        DNode *lNode = new DNode;
        DNode *rNode = new DNode;
        
        //cout << "1good so far\n";

        rNode->key = getMaxInformationGain(attributes, data, outcomes, currNode->key.instancesAbove);
        lNode->key = getMaxInformationGain(attributes, data, outcomes, currNode->key.instancesBelow);
        
        //cout << "2good so far\n";
        lNode->depth = currNode->depth + 1;
        rNode->depth = currNode->depth + 1;

        lNode->parent = currNode;
        rNode->parent = currNode;

        currNode->left = lNode;
        currNode->right = rNode;

        /*cout << "l:" << lNode->key.informationGain << endl;
        cout << "r:" << rNode->key.informationGain << endl;
        cout << "delta: " << delta << endl;*/

        // Keep going until branch's information gain is less than delta:
        if (lNode->key.informationGain > delta){
            trainHelper(attributes,data,outcomes,lNode);
        }

        if (rNode->key.informationGain > delta){
            trainHelper(attributes,data,outcomes, rNode);
        }
    }

    void train(
        vector<string>& attributes,
        vector<vector<double>>& data,
        vector<int>& outcomes,
        vector<int>& instances
    ){
        // This function takes the set of attributes, all data, and the list of
        // outcomes and isntances so that it can build the decision tree. It should
        // call getMaxInformationGain() to get the decision that should be turned into
        // the next node.
        //cout << "ok\n";

        if (root){clear(root);}

        root = new DNode;
        root->depth = 0;
        root->key = getMaxInformationGain(attributes,data,outcomes,instances);
    
        trainHelper(attributes, data, outcomes, root);
    }

    int classify(vector<string>& attributes, vector<double>& delta){
        DNode* currNode = this->root;
        int index = 0;
        int returnMe;
        while (currNode){
            //cout << "cool\n";
            for (int i = 0; i < attributes.size(); i++){
                if (attributes.at(i) == currNode->key.attribute){
                    index = i;
                    break;
                }
            }

            double data = delta.at(index);
            if (data <= currNode->key.threshold){
                returnMe = currNode->key.majorityBelow;
                currNode = currNode->left;
            }else{
                returnMe = currNode->key.majorityAbove;
                currNode = currNode->right;
            }
        }

        return returnMe;
    }

    string levelOrderTraversal(){
        // To understand the structure the tree has built, we can use a level-order
        // traversal. In class, we went through an example of this algorithm with
        // detailed pseudocode. You can implement it exactly from that example
        // with one modification to how we print the data.

        // Add the following line in your function when the current node is dequeued 
        // so that you can print it with an indentation level corresponding to its depth:
        std::stringstream ss;
        ss.clear();

        Queue<DNode*> q;

        if (!root){
            return ss.str();
        }

        DNode *u, *l, *r;
        //ss << string(root->depth,'\t') << root->depth;
        q.push_back(root);

        while (!q.empty()){
            //cout << "ok\n";
            u = q.pop_front();
            ss << string(u->depth,'\t') << u->key;

            l = u->left;
            r = u->right;

            if (l){
                //ss << string(l->depth,'\t') << l->key;
                q.push_back(l);
            }
            if (r){
                //ss << string(r->depth,'\t') << r->key;
                q.push_back(r);
            }
        }
        return ss.str();
    }

    ~DTree(){
        // Destructor should clear all the memory being used by the DTree.
        // Note you should have a default constructor to set the initial member values
        // or at least somewhere define root to nullptr when the tree is instantiated!
        clear(this->root);
    }

    void clear(DNode *node){
        if (!node){
            return;
        }
        if (node->left){
            clear(node->left);
        }
        if (node->right){
            clear(node->right);
        }
        delete node;
    }

};
#endif