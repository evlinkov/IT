#ifndef FlowSolver_h
#define FlowSolver_h

#include <iostream>
#include "Graph.h"
#include "Edge.h"

class FlowSolver : public Graph {
    
private :
    
    long long flow;
    int edges;
    
public :
    
    FlowSolver();
    FlowSolver(int sourse, int sink, int vertices);
    void equalFlow (long long ans);
    void inputFlowSolver();
    void outputFlowSolver();
};

#endif