#include "lcp.h"

LCP::LCP(SuffixArray &suf, std::vector<int> &buffer)
{
    for (int i = 0; i < suf.getSize(); ++i) {
        line.push_back(buffer[i]);
        suffixArray.push_back(suf.getSuffixArray(i));
    }
    lcp.resize(line.size());
    findLCP();
}

int LCP::getLcp(int i)
{
    return lcp[i];
}

void LCP::findLCP()
{
    std::vector <int> inverseSuffixArray;
    inverseSuffixArray.resize(suffixArray.size());
    for (int i = 0; i < suffixArray.size(); ++i) {
        inverseSuffixArray[suffixArray[i]] = i;
    }
    int num = 0;
    for (int i = 0; i < suffixArray.size(); ++i) {
        if (num > 0) {
            num--;
        }
        if (inverseSuffixArray[i] == line.size() - 1) {
            lcp[line.size() - 1] = 0;
            num = 0;
            continue;
        }
        int pos = suffixArray[inverseSuffixArray[i] + 1];
        while (std::max(i + num, pos + num) < line.size() && line[i + num] == line[pos + num]) {
            ++num;
        }
        lcp[inverseSuffixArray[i]] = num;
    }
}