#ifndef suffixTree_h
#define suffixTree_h

#include <iostream>
#include "vertex.h"
#include <vector>



struct StartPoint
{
    Vertex * vertex;
    int currentShift;
    int currentChar;
};

class SuffixTree
{

private :
    
    std::vector <int> line;
    Vertex * root, * blank;
    StartPoint startPoint;
    
public :
    
    SuffixTree(int left, int right, std::vector <int> &buffer);
    void initialization();
    ~SuffixTree();
    void deleteVertex(Vertex * vertex);
    void addSymbol (int position);
    void buildSuffixTree();
    Vertex * createLeaf(Vertex * vertex, int position);
    bool canMove (int symbol);
    Vertex * createVertex ();
    void getLink ();
    
    long long getAnswer();
    long long getDifferentString (Vertex * vertex);
};


#endif