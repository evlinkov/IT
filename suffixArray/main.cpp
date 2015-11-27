#include "lcp.h"

void solver()
{
    int ans, k, currentLcp;
    std::vector <int> line;
    std::string buffer;
    
    std::cin >> k;
    std::cin >> buffer;
    int n = int(buffer.size());
    buffer += buffer.substr(0, k - 1);
    for (int i = 0; i < buffer.size(); ++i) {
        line.push_back(buffer[i] - 'a' + 1);
    }
    line.push_back(0);
    SuffixArray suf(line);
    LCP lcp(suf, line);
    
    for (int i = 0; i < n; ++i) {
        ans = k * (k + 1) / 2;
        int left = i;
        int right = i + k;
        currentLcp = 0;
        for (int j = 0; j < line.size(); ++j) { // [l; r)
            int numberOfSuffix = suf.getSuffixArray(j);
            if (numberOfSuffix < right && numberOfSuffix >= left) {
                if (currentLcp > right - numberOfSuffix) {
                    ans -= (right - numberOfSuffix);
                    currentLcp = std::min(currentLcp, lcp.getLcp(j));
                    continue;
                }
            }
            if (numberOfSuffix < right && numberOfSuffix >= left) {
                ans -= currentLcp;
                currentLcp = right - numberOfSuffix;
            }
            currentLcp = std::min(currentLcp, lcp.getLcp(j));
        }
        std::cout << ans << " ";
    }
}


int main()
{
    solver();
    return 0;
}