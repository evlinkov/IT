#include "FlowSolver.h"
#include <fstream>

FlowSolver :: FlowSolver(int sourse, int sink, int vertices) : flow(0), Graph(sourse, sink, vertices) {}

void FlowSolver :: inputFlowSolver() {
    std :: ifstream cin("input.txt");
    int numberOfEdges, to, from, cap;
    std :: cin >> numberOfEdges;
    edges = numberOfEdges;
    for (int i = 0; i < numberOfEdges; ++i) {
        std :: cin >> from >> to >> cap;
        addEdge(from, to, cap, i);
    }
}

void FlowSolver :: outputFlowSolver() {
    std :: cout << flow << "\n";
    std :: vector <int> answer;
    answer.resize(edges);
    for (int i = 0; i < getVertices(); ++i) {
        for (int v = 0; v < getNumbersNeigbor(i); ++v) {
            NetworkEdge * edge = getNeigbor(i, v);
            if (edge->getNumberEdge() >= 0) {
                answer[edge->getNumberEdge()] = edge->getFlow();
            }
        }
    }
    for (int i = 0; i < edges; ++i) std :: cout << answer[i] << "\n";
}

void FlowSolver :: equalFlow(long long ans) {
    flow = ans;
}