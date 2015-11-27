#ifndef lcp_h
#define lcp_h

#include <iostream>
#include "suffixArray.h"

class LCP
{
    
private:
    
    std::vector<int> line;
    std::vector<int> suffixArray;
    std::vector<int> lcp;
    
public:
    
    LCP(SuffixArray &suf, std::vector<int> &buffer);
    void findLCP();
    int getLcp(int i);
};

#endif