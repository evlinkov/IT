#include "suffixTree.h"

SuffixTree::SuffixTree(int left, int right, std::vector <int> &buffer) 
{
    for (int i = left; i <= right; i++) {
        line.push_back(buffer[i]);
    }
    initialization();
    buildSuffixTree();
}

void SuffixTree::initialization()
{
    blank = new Vertex(nullptr, 0, 0);
    root = new Vertex(blank, -1, 0);
    root->updateLink(blank);
    for (int i = 0; i < ALPHABET; ++i) {
        blank->updateNext(root, i);
    }
    startPoint.vertex = root;
    startPoint.currentShift = 0;
    startPoint.currentChar = -1;
}

SuffixTree::~SuffixTree()
{
    deleteVertex(root);
    delete blank;
    line.clear();
}

void SuffixTree::deleteVertex(Vertex * vertex)
{
    for (int i = 0; i < ALPHABET; ++i) {
        if (vertex->getNext(i) != nullptr) {
        deleteVertex(vertex->getNext(i));
        }
    }
    delete vertex;
}

void SuffixTree::buildSuffixTree()
{
    for (int i = 0; i < line.size(); ++i) {
        addSymbol(i);
    }
}

void SuffixTree::addSymbol(int position)
{
    Vertex * last = nullptr;
    while (!canMove(line[position])) {
        if (startPoint.currentShift != 0) {
            startPoint.vertex = createVertex();
            startPoint.currentShift = 0;
            startPoint.currentChar = -1;
        }
        if (last != nullptr) {
            last->updateLink(startPoint.vertex);
        }
        last = startPoint.vertex;
        createLeaf(startPoint.vertex, position);
        getLink();
        if (startPoint.currentShift == 0) {
            last->updateLink(startPoint.vertex);
            last = nullptr;
        }
    }
}

Vertex * SuffixTree::createLeaf(Vertex * vertex, int position)
{
    Vertex * leaf = new Vertex(vertex, position, int(line.size()));
    vertex->updateNext(leaf, line[position]);
    return leaf;
}

Vertex * SuffixTree::createVertex ()
{
    int symbol = line[startPoint.vertex->getNext(startPoint.currentChar)->getLeft()
                      + startPoint.currentShift];
    int left = startPoint.vertex->getNext(startPoint.currentChar)->getLeft();
    Vertex * newVertex = new Vertex (startPoint.vertex, left, left + startPoint.currentShift);
    newVertex->updateNext(startPoint.vertex->getNext(startPoint.currentChar), symbol);
    startPoint.vertex->updateNext(newVertex, startPoint.currentChar);
    newVertex->getNext(symbol)->updateParent(newVertex);
    newVertex->getNext(symbol)->updateLeft(newVertex->getRight());
    return newVertex;
}

void SuffixTree::getLink ()
{
    if (startPoint.vertex->getLink() != nullptr) {
        startPoint.vertex = startPoint.vertex->getLink();
        return;
    }
    int left = startPoint.vertex->getLeft();
    int right = startPoint.vertex->getRight();
    Vertex * link = startPoint.vertex->getParent()->getLink();
    while (link->getNext(line[left])->getLength() <= right - left) {
        int length = link->getNext(line[left])->getLength();
        link = link->getNext(line[left]);
        left += length;
    }
    startPoint.currentChar = line[left];
    startPoint.currentShift = right - left;
    startPoint.vertex = link;
}

bool SuffixTree::canMove(int symbol)
{
    if (startPoint.currentShift == 0) {
        if (startPoint.vertex->getNext(symbol) == nullptr) {
            return false;
        }
        if (startPoint.vertex->getNext(symbol)->getLength() > 1) {
            startPoint.currentShift = 1;
            startPoint.currentChar = symbol;
        }
        else {
            startPoint.vertex = startPoint.vertex->getNext(symbol);
            startPoint.currentChar = -1;
        }
        return true;
    }
    if (line[startPoint.vertex->getNext(startPoint.currentChar)->getLeft() + startPoint.currentShift] == symbol) {
        ++startPoint.currentShift;
        if (startPoint.currentShift == startPoint.vertex->getNext(startPoint.currentChar)->getLength()) {
            startPoint.vertex = startPoint.vertex->getNext(startPoint.currentChar);
            startPoint.currentShift = 0;
            startPoint.currentChar = -1;
        }
        return true;
    }
    return false;
}

long long SuffixTree::getAnswer()
{
    return getDifferentString(root) - 1;
}

long long SuffixTree::getDifferentString(Vertex * vertex)
{
    if (vertex == nullptr) {
        return 0;
    }
    long long answer = vertex->getLength();
    for (int i = 0; i < ALPHABET; ++i) {
        answer += getDifferentString(vertex->getNext(i));
    }
    return answer;
}
