#include "Bfs.h"
#include <iostream>
#include "Graph.h"
#include <deque>

void Bfs :: getDistances(Graph &graph, std :: vector <int> &distance, int skip) {
    for (int i = 0; i < graph.getVertices(); ++i) {
        distance[i] = graph.getVertices();
    }
    distance[graph.getSourse()] = 0;
    std :: deque <int> nodes;
    nodes.push_back(graph.getSourse());
    while (nodes.size() > 0 && distance[graph.getSink()] == graph.getVertices()) {
        int u = nodes.front();
        nodes.pop_front();
        for (int v = 0; v < graph.getNumbersNeigbor(u); ++v) {
            NetworkEdge * edge = graph.getNeigbor(u, v);
            if (distance[edge->getTo()] == graph.getVertices()
                && edge->getCapacity() - edge->getFlow() >= skip){
                distance[edge->getTo()] = distance[u] + 1;
                nodes.push_back(edge->getTo());
            }
        }
    }
}

