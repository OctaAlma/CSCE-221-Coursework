#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
using std::vector;


class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    // helpers stored inside a vertex to help with path finding
    // you can use different auxilliary structures if desired
    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;

    bool operator < ( const Vertex &v ) const 
    { 
        // TODO for locator heap implementation
        return this->distanceTo < v.distanceTo;
    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    // TODO: store the vertices and edges in the graph
    vector<Vertex*> vertices;
    vector<Edge*> edges;

public:
    Graph () {}

    // TODO: Complete rule of 3:

    void clear(){
        for (int i = 0; i < vertices.size(); i++){
            if (vertices[i]){
                delete vertices[i];
            }
        }
        for (int i = 0; i < edges.size(); i++){
            if (edges[i]){
                delete edges[i];
            }
        }

        vertices.clear();
        edges.clear();
    }

    void copy(const Graph& other){

        // Quick check to ensure the "other" item actually has stuff:
        if (other.vertices.size()){
            this->vertices = vector<Vertex*>(other.vertices.size(),nullptr);
        }
        if (other.edges.size()){
            this->edges = vector<Edge*>(other.edges.size(),nullptr);
        }

        // Copy the vertices to "this":
        for (int i = 0; i < this->vertices.size(); i++){
            if (other.vertices.at(i)){
                this->vertices.at(i) = new Vertex(other.vertices.at(i)->label);
            }
        }

        int l1, l2;
        Vertex *V1, *V2;
        // Copy the edges to "this":
        for (int i = 0; i < this->edges.size(); i++){
            if (other.edges.at(i)){
                // We have to find the two corresponding vertices in "this"'s vertex vector:
                l1 = other.edges.at(i)->v1->label;
                l2 = other.edges.at(i)->v2->label;

                for (int j = 0; j < this->vertices.size(); j++){

                    if (this->vertices.at(j)){

                        if (this->vertices.at(j)->label == l1){
                            V1 = this->vertices.at(j);
                        }else if (this->vertices.at(j)->label == l2){
                            V2 = this->vertices.at(j);
                        }

                    }
                }
                this->edges.at(i) = new Edge(V1, V2, other.edges.at(i)->weight);
                // Add the edges to the vector:
                V1->edges.push_back(this->edges.at(i));
                //  V2->edges.push_back(edges.at(i));
            }
        }

    }

    // Destructor
    ~Graph () { this->clear(); }

    // Copy constructor
    Graph(const Graph& other){ 
        this->copy(other); 
    }

    // Copy assignment
    Graph& operator=(const Graph& other){
        if (&other == this){
            return *this;
        }

        this->clear();
        this->copy(other);
        return *this;
    }

    void insertVertex ( int label ) { this->vertices.push_back(new Vertex(label)); }

    void insertEdge ( int l1, int l2, float weight )
    {
        // TODO
        // NEW IMPLEMENTATION:
        Vertex* v1 = this->vertices.at(l1);
        Vertex* v2 = this->vertices.at(l2);

        Edge* newEdge = new Edge(v1, v2, weight);

        v1->edges.push_back(newEdge);
        edges.push_back(newEdge);

    }

    vector<Vertex*> shortestPath ( int start, int end ){
        // Initialize all of the vertices properly:
        Heap<Vertex*> priorityQ;

        for (int i = 0; i < vertices.size(); i++){
            vertices.at(i)->visited = false;
            vertices.at(i)->pathTo.clear();

            if (i == start){
                vertices.at(i)->distanceTo = 0;
                vertices.at(i)->pathTo.push_back(vertices.at(i));
            }else{
                vertices.at(i)->distanceTo = __FLT_MAX__;
            }

            vertices.at(i)->locator = priorityQ.insertElement(vertices.at(i));
        }

        Vertex* currVertex;
        while (!priorityQ.isEmpty()){
            // Insert and remove will return pointers to a HeapItem
            // heapItems contain both a vertex object AND its index
            currVertex = priorityQ.removeMin();

            // Check the neighbors and change their distanceTo and pathTo if appropriate
            for (int i = 0; i < currVertex->edges.size(); i++){
                Vertex* currNeighbor = currVertex->edges.at(i)->v2;

                if (currNeighbor->distanceTo > currVertex->distanceTo + currVertex->edges.at(i)->weight){
                    currNeighbor->distanceTo = currVertex->distanceTo + currVertex->edges.at(i)->weight;
                    currNeighbor->pathTo = currVertex->pathTo;
                    currNeighbor->pathTo.push_back(currNeighbor);

                    priorityQ.update(currNeighbor->locator);
                }
                
            }

            currVertex->visited = true;

            if (currVertex->label == end){
                break;
            }
        }

        return currVertex->pathTo;
    }

};

#endif
