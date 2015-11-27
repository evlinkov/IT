#ifndef Edge_h
#define Edge_h

#include <iostream>

class Edge {
    
private :
    
    int from, to;
    
public :
    
    Edge ();
    Edge (int from, int to);
    int getTo() const;
    int getFrom() const;
};

class NetworkEdge : public Edge {
    
private :
    
    int capacity, flow, numberEdge;
    NetworkEdge *reversedNetworkEdge;
    
public :
    
    NetworkEdge();
    NetworkEdge(int from, int to, int capacity, int numberEdge);
    int getFlow();
    int getCapacity() const;
    void changeFlow (int delta);
    void reversed(NetworkEdge * edge);
    int getNumberEdge() const;
};

#endif 