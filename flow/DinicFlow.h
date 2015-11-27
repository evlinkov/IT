#ifndef DinicFlow_h
#define DinicFlow_h

#include <iostream>
#include "FlowSolver.h"

class DinicFlow : public FlowSolver {
    
private :

    std :: vector <int> distance;
    std :: vector <int> neighbours;
    void solveDinicFlow();
    bool dfsDinicFlow(int v, int skip);
    long long flow;
    
public :

    DinicFlow();
    DinicFlow(int sourse, int sink, int vertices);
};

#endif 