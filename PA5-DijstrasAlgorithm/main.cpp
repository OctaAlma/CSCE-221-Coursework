#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int countWhitespace(string s){
    int count = 0;
    for (int i = 0; i < s.size(); i++){
        if (std::isspace(s.at(i))){count++;}
    }
    return count;
}

int main(int argc, const char * argv[]) {
    cout << "Filename of graph to load: ";

    // TODO: next five code snippets
    // Snippet 1: read filename and open file
    string filename;
    fstream file;

    cin >> filename;

    file.open(filename);

    if (file.fail()){
        throw std::runtime_error(filename + " did not open!");
    }

    // Snippet 2: get number graph size
    int numVertices, numEdges, l1,l2, startVertex, endVertex;
    float weight;

    file >> numVertices;
    file >> numEdges;
    
    // Snippet 3: create graph
    Graph g;

    // Snippet 4: read edges
    for (int i = 0; i < numVertices; i++){g.insertVertex(i);}

    for (int i = 0; i < numEdges; i++){
        file >> l1;
        file >> l2;
        file >> weight;

        g.insertEdge(l1,l2,weight);
        g.insertEdge(l2,l1,weight);
    }

    // Snippet 5: read start and end of path
    file >> startVertex;
    file >> endVertex;
    
    cout << "Shortest path from " << startVertex << " to " << endVertex << ":" << endl;

    vector<Vertex*> path;

    // TODO: call shortest path on your graph for the start and end vertices and save result to path

    path = g.shortestPath(startVertex, endVertex);
    
    for (auto i : path) { // this is a for-each loop
        cout << i->label << " ";
    }
    // cout endline at very end
    cout << endl;
    return 0;
}
