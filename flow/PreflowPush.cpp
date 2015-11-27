#include "PreflowPush.h"

PreflowPush :: PreflowPush (int sourse, int sink, int vertices) : max_height(vertices), FlowSolver(sourse, sink, vertices) {
    height.assign(vertices, 0);
    height[sourse] = vertices;
    excess.assign(vertices, 0);
    count_height.assign(2 * vertices + 2, 0);
    count_height[0] = vertices - 1;
    count_height[vertices] = 1;
    inputFlowSolver();
    initializePreflowPush();
    solvePreflowPush();
    outputFlowSolver();
}

void PreflowPush :: discharge (int u) {
    if (getNumbersNeigbor(u) == 0) return;
    int v = 0;
    NetworkEdge * edge;
    while (excess[u] > 0) {
        edge = getNeigbor(u, v);
        if (height[u] == height[edge->getTo()] + 1 && edge->getCapacity() - edge->getFlow() > 0) {
            push(edge);
        }
        ++v;
        if (v == getNumbersNeigbor(u)) {
            relable(u);
            v = 0;
        }
    }
}

void PreflowPush :: push(NetworkEdge *edge) {
    long long pushFlow = Min (excess[edge->getFrom()], edge->getCapacity() - edge->getFlow() );
    if (excess[edge->getTo()] == 0 && pushFlow > 0 && edge->getTo() != getSink() && edge->getTo() != getSourse()) {
        node.push_back(edge->getTo());
    }
    edge->changeFlow(int(pushFlow));
    excess[edge->getFrom()] -= pushFlow;
    excess[edge->getTo()] += pushFlow;
}

void PreflowPush :: relable (int u) {
    int StartHeight = height[u];
    count_height[height[u]] --;
    height[u] = max_height;
    for (int v = 0; v < getNumbersNeigbor(u); ++v) {
        NetworkEdge * edge = getNeigbor(u, v);
        if (edge->getCapacity() - edge->getFlow() > 0) {
            height[u] = std :: min (height[u], height[edge->getTo()]);
        }
    }
    ++height[u];
    count_height[height[u]]++;
    if (count_height[StartHeight] == 0) gap(StartHeight);
    max_height = std::max(max_height, height[u]);
}

void PreflowPush :: gap (int h) {
    for (int i = 0; i < getVertices(); ++i) {
        if (i == getSink()) continue;
        if (i == getSourse()) continue;
        if (height[i] > h) height[i] = getVertices();
    }
}

void PreflowPush :: initializePreflowPush() {
    for (int v = 0; v < getNumbersNeigbor(getSourse()); ++v) {
        NetworkEdge * edge = getNeigbor(getSourse(), v);
        if (getSourse() == edge->getTo()) continue;
        edge->changeFlow(edge->getCapacity());
        excess[edge->getTo()] += edge->getCapacity();
        excess[edge->getFrom()] -= edge->getCapacity();
        if (edge->getCapacity() != 0 && edge->getTo() != getSink()) {
            node.push_back(edge->getTo());
        }
    }
}

void PreflowPush :: solvePreflowPush() {
    while (node.size() > 0) {
        int u = node.front();
        node.pop_front();
        discharge(u);
    }
    equalFlow(excess[getSink()]);
}