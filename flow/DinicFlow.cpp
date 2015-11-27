#include "DinicFlow.h"
#include "Bfs.h"

DinicFlow :: DinicFlow(int sourse, int sink, int vertices) : flow(0), FlowSolver(sourse, sink, vertices) {
    distance.resize(vertices);
    neighbours.resize(vertices);
    inputFlowSolver();
    solveDinicFlow();
    outputFlowSolver();
}

bool DinicFlow :: dfsDinicFlow(int v, int skip) {
    if (v == getSink()) {
        return true;
    }
    for (; neighbours[v] < getNumbersNeigbor(v); ++neighbours[v]) {
        NetworkEdge * edge = getNeigbor(v, neighbours[v]);
        if (distance[edge->getTo()] == distance[v] + 1 && edge->getCapacity() - edge->getFlow() >= skip) {
            bool checkDfs = dfsDinicFlow(edge->getTo(), skip);
            if (checkDfs) {
                edge->changeFlow(skip);
                return true;
            }
        }
    }
    return false;
}

void DinicFlow :: solveDinicFlow() {
    int skipFlow;
    skipFlow = (1<<30);
    while (skipFlow != 0) {
        Bfs BfsDinicFlow;
        BfsDinicFlow.getDistances(*this, distance, skipFlow);
        if (distance[getSink()] == getVertices()) {
            skipFlow>>=1;
            continue;
        }
        for (int i = 0; i < getVertices(); ++i) {
            neighbours[i] = 0;
        }
        while (dfsDinicFlow(getSourse(), skipFlow)) {
            flow += skipFlow;
        }
    }
    equalFlow(flow);
}