#include "Graph.h"
#include "Edge.h"

Graph :: Graph (int sourse, int sink, int vertices) : sourse(sourse), sink(sink), vertices(vertices) {
    edges.resize(vertices);
}

int Graph :: getSink() const {
    return sink;
}

int Graph :: getSourse() const {
    return sourse;
}

int Graph :: getVertices() const {
    return vertices;
}

NetworkEdge * Graph :: addEdge(int from, int to, int cap, int numberEdge) {
    --to;
    --from;
    NetworkEdge* direct, *reversed;
    direct = new NetworkEdge(from, to, cap, numberEdge);
    reversed = new NetworkEdge(to, from, 0, -1);
    direct->reversed(reversed);
    reversed->reversed(direct);
    edges[from].push_back(direct);
    edges[to].push_back(reversed);
    return direct;
}

NetworkEdge * Graph :: getNeigbor(int v, int u) {
    return edges[v][u];
}
int Graph :: getNumbersNeigbor(int v) {
    return int(edges[v].size());
}

long long Graph :: Min (long long a, long long b) {
    if (a > b) return b;
    return a;
}