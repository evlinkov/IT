#include <iostream>
#include "suffixTree.h"

void solver()
{
    int k;
    std::string buffer;
    std::vector <int> line;
    
    std::cin >> k;
    std::cin >> buffer;
    buffer += buffer.substr(0, k - 1);
    
    for (int i = 0; i < int(buffer.size()); ++i) {
        line.push_back(buffer[i] - 'a');
    }
    for (int i = k - 1; i < buffer.size(); ++i) {
        line.push_back(buffer[i]);
        SuffixTree solver (i - k + 1, i, line);
        std::cout << solver.getAnswer() << ' ';
    }
}

int main ()
{
    solver();
    return 0;
}