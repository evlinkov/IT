#include "Edge.h"
#include <iostream>

Edge :: Edge(int from, int to) : from(from), to(to) {}

NetworkEdge :: NetworkEdge(int from, int to, int capacity, int numberEdge) : capacity(capacity), flow(0), numberEdge(numberEdge), Edge (from, to) {}

int Edge :: getTo () const{
    return to;
}

int Edge :: getFrom() const{
    return from;
}

int NetworkEdge :: getFlow() {
    return flow;
}

int NetworkEdge :: getCapacity() const {
    return capacity;
}

void NetworkEdge:: changeFlow(int delta) {
    flow += delta;
    reversedNetworkEdge -> flow -= delta;
}

void NetworkEdge::reversed (NetworkEdge *edge) {
    reversedNetworkEdge = edge;
}

int NetworkEdge :: getNumberEdge() const {
    return numberEdge;
}