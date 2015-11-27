#ifndef suffixArray_h
#define suffixArray_h

#include <iostream>
#include <vector>
#include <algorithm>

static const int TRIPLE = 3;

struct triplet {
    int elements[TRIPLE];
};

bool equalTriplet (triplet a, triplet b);

class SuffixArray {
    
private :
    
    std::vector <int> line;
    std::vector <int> suffixArray;
    std::vector <std::pair <triplet, int> > triplets;
    
public :
    
    SuffixArray(std::vector <int> &buffer);
    void findSuffixArray();
    int getSuffixArray(int i);
    void getTripletInDivisibleTriple();
    void getTripletDivisibleTriple(std::vector <int> &array);
    void radixSort(std::vector <std::pair <triplet, int> > &array, int rank);
    void getTripletLine (std::vector <int> &tripletLine);
    void getSuffixArrayInDivisibleTriple (SuffixArray &smallLine, std::vector <int> &array);
    void getSuffixArrayDivisibleTriple (std::vector <int> &array);
    int getSize();
    void mergeSuffixes (std::vector<int> &arrayDivisibleTriple, std::vector<int> &arrayInDivisibleTriple, int addSign);
};

#endif
