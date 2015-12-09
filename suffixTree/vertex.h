#ifndef vertex_h
#define vertex_h

#include <iostream>

static const int ALPHABET = 26;

class Vertex
{

private :
    
    int left, right; // [left, right)
    Vertex * next[ALPHABET];
    Vertex * parent, * link;
    
public :
    
    Vertex(Vertex * parent, int left, int right);
    
    void updateNext (Vertex * newNext, char symbol);
    void updateParent (Vertex * newParent);
    void updateLink (Vertex * newLink);
    void updateRight (int newRight);
    void updateLeft (int newLeft);
    
    Vertex * getNext (char symbol);
    Vertex * getParent();
    Vertex * getLink ();
    int getLength();
    int getRight();
    int getLeft();    
};

#endif
