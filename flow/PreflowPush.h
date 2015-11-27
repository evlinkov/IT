#ifndef PreflowPush_h
#define PreflowPush_h

#include <iostream>
#include "FlowSolver.h"
#include "Edge.h"
#include <deque>

class PreflowPush : public FlowSolver {
    
private :
    
    int max_height;
    std::deque <int> node;
    std::vector <int> height;
    std::vector <int> count_height;
    std::vector <long long> excess;
    void discharge (int u);
    void push(NetworkEdge *edge);
    void relable (int u);
    void gap (int height);
    void initializePreflowPush();
    void solvePreflowPush();
    
public :
    
    PreflowPush();
    PreflowPush(int sourse, int sink, int vertices);
};

#endif 