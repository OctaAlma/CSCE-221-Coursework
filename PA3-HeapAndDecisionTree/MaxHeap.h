#ifndef MAXHEAP
#define MAXHEAP
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

template <typename T>
class MaxHeap{
    private:
    vector<T> heap;
    int height;

    T removeRoot(){
        T max = heap.at(0);

        if (heap.size() == 1){
            heap.clear();
            return max;
        }

        vector<T> newHeap;
        for (int i = 0; i < heap.size(); i++){
            // put the last element on the top of the heap:
            if (i == 0){
                newHeap.push_back(heap.at(heap.size()-1));
                continue;
            }
            if (i == heap.size()-1){
                continue;
            }
            newHeap.push_back(heap.at(i));
        }

        heap = newHeap;
        return max;
    }

    public:
    MaxHeap(){
        this->heap.clear();
    }

    MaxHeap(vector<T> v){
        for (int i = 0; i < v.size(); i++){
            this->heap.push_back(v.at(i));
        }
        heapify();
    }

    int getHeight(){
        return (log2(heap.size()) + 1);
    }

    int getParent(int nodeIndex) const{
        return (nodeIndex-1)/2;
    }

    int getLeft(int nodeIndex) const{
        return nodeIndex*2+1;
    }

    int getRight(int nodeIndex) const{
        return nodeIndex*2+2;

    }

    bool empty() const{
        return heap.empty();
    }
    
    // The big boys:

    // UpHeap: Given the index of a node, propagate it up the max heap if the parent is a smaller value
    void upheap(int index){
        if (heap.empty()){
            return;
        }

        T key = heap.at(index);

        int parentIndex = getParent(index);
        T parent = heap.at(parentIndex);

        if (key > parent){
            heap.at(parentIndex) = key;
            heap.at(index) = parent;
            upheap(parentIndex);
        }
    }

    // downheap: Given the index of a node, propagate it down the max heap if a child has a larger value
    void downheap(int index){
        if (heap.size() <= index){
            return;
        }

        T node = heap.at(index);

        int lIndex = getLeft(index);
        int rIndex = getRight(index);

        // We need to check which child is bigger than the parent:
        if (heap.size() > lIndex && heap.size() > rIndex){
            T lChild = heap.at(lIndex);
            T rChild = heap.at(rIndex);
            if (heap.at(lIndex) >= heap.at(rIndex)){
                heap.at(index) = lChild;
                heap.at(lIndex) = node;
                downheap(lIndex);
                return;
            }else{
                heap.at(index) = rChild;
                heap.at(rIndex) = node;
                downheap(rIndex);
                return;
            }
        }

        // Check if left child is bigger OR EQUAL to parent:
        if (heap.size() > lIndex){
            T lChild = heap.at(lIndex);

            if (lChild >= node){
                heap.at(index) = lChild;
                heap.at(lIndex) = node;

                downheap(lIndex);
                return;
            }
        }

        // Check if right child is bigger than parent:
        if (heap.size() > rIndex){
            T rChild = heap.at(rIndex);
            
            if (rChild > node){
                heap.at(index) = rChild;
                heap.at(rIndex) = node;

                downheap(rIndex);
                return;
            }
        }
    }

    // Heapify: Heapify the current structure to ensure the rules of a heap are maintained; 
    //used in conjunction with the parameterized constructor that accepts a vector
    void heapify(){
        // we need to downheap from the last subtree, all the way to the top/root
        helperHeapify(heap.size()-1);
    }

    void helperHeapify(int index){
        if (index<=0){
            downheap(0);
            return;
        }
        int parent = getParent(index);
        downheap(parent);
        if (parent == 0){
            return;
        }else{
            helperHeapify(index-2);
        }

    }

    // Insert an element to the heap. Uses upheap
    void insert(T item){
        heap.push_back(item);
        upheap(heap.size()-1);
    }

    // Remove max element from the heap, returns max element and uses downheap
    T removeMax(){
        T max = removeRoot();
        downheap(0);
        return max;
    }

    /*void PRINTHEAP(){
        for (int i = 0; i < heap.size(); i++){
            if (i == 0){cout << "[ ";}
            cout << heap.at(i) << " ";
            if (i == heap.size()-1){cout << "]\n";}
        }
    }*/
};

template<typename T>
vector<T> heapsort(vector<T> v){
    MaxHeap<T> h;
    for (int i = 0; i < v.size(); i++){
        h.insert(v.at(i));
    }
    T max;
    for (int i = 0; i < v.size(); i++){
        max = h.removeMax();
        v.at(i) = max;
    }
    return v;
}

#endif