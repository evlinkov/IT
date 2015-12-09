#include "vertex.h"

Vertex :: Vertex (Vertex * parent, int left, int right) : parent (parent), left(left), right(right)
{
    link = nullptr;
    for (int i = 0; i < ALPHABET; ++i) {
        next[i] = nullptr;
    }
}

void Vertex::updateParent (Vertex * newParent)
{
    parent = newParent;
}


void Vertex::updateNext (Vertex * newNext, char symbol)
{
    next[symbol] = newNext;
}

void Vertex::updateLink (Vertex * newLink)
{
    link = newLink;
}

void Vertex::updateRight (int newRight)
{
    right = newRight;
}

void Vertex::updateLeft (int newLeft)
{
    left = newLeft;
}

Vertex * Vertex::getNext (char symbol)
{
    return next[symbol];
}

Vertex * Vertex::getParent()
{
    return parent;
}

Vertex * Vertex::getLink ()
{
    return link;
}

int Vertex::getLength()
{
    return right - left;
}

int Vertex::getRight()
{
    return right;
}

int Vertex::getLeft()
{
    return left;
}