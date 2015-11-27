#ifndef Graph_h
#define Graph_h

#include <iostream>
#include "Edge.h"
#include <vector>

class Graph {

private :
    
    int sourse, sink, vertices;
    std :: vector < std :: vector <NetworkEdge *> > edges;

public :

    Graph();
    Graph (int sourse, int sink, int vertecis);
    int getSink() const;
    int getSourse() const;
    int getVertices() const;
    NetworkEdge * addEdge(int from, int to, int cap, int numberEdge);
    NetworkEdge *getNeigbor(int v, int u);
    int getNumbersNeigbor(int v) ;
    long long Min (long long a, long long b);
};

#endif