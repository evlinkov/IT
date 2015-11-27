#include "suffixArray.h"


//--------------------------------------------------------------------------------------------------------------------------

bool equalTriplet (triplet a, triplet b)
{
    for (int i = 0; i < TRIPLE; ++i) {
        if (a.elements[i] != b.elements[i]) {
            return false;
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------------------------------

SuffixArray::SuffixArray (std::vector <int> &buffer)
{
    line.resize(buffer.size());
    std::copy(buffer.begin(), buffer.end(), line.begin());
    findSuffixArray();
}

void SuffixArray::findSuffixArray()
{
    if (line.size() <= 4) {
        suffixArray.resize(line.size());
        std::vector <std::pair<std::vector<int>, int> > suffixes;
        for (int i = 0; i < line.size(); ++i) {
            std::vector<int> buffer;
            for (int j = i; j < line.size(); ++j) {
                buffer.push_back(line[j]);
            }
            suffixes.push_back(make_pair(buffer, i));
        }
        std::sort(suffixes.begin(), suffixes.end());
        for (int i = 0; i < line.size(); ++i) {
            suffixArray[i] = suffixes[i].second;
        }
        return;
    }
    int addSign = 0;
    while (line.size() % 3 != 0) {
        line.push_back(0);
        addSign++;
    }
    getTripletInDivisibleTriple();
    radixSort(triplets, int(line.size()));
    std::vector <int> tripletLine;
    getTripletLine (tripletLine);
    
    SuffixArray smallLine(tripletLine);
    
    std::vector <int> suffixArrayDivisibleTriple;
    std::vector <int> suffixArrayInDivisibleTriple;
    
    getSuffixArrayInDivisibleTriple(smallLine, suffixArrayInDivisibleTriple);
    getTripletDivisibleTriple(suffixArrayInDivisibleTriple);
    radixSort(triplets, int(line.size()));
    getSuffixArrayDivisibleTriple (suffixArrayDivisibleTriple);
    mergeSuffixes(suffixArrayDivisibleTriple, suffixArrayInDivisibleTriple, addSign);
    
    for (int i = 0; i < addSign; ++i) {
        line.pop_back();
    }
}

int SuffixArray::getSize()
{
    return int(line.size());
}

void SuffixArray::getSuffixArrayInDivisibleTriple (SuffixArray &smallLine, std::vector <int> &array)
{
    for (int i = 0; i < smallLine.getSize(); ++i) {
        if (smallLine.getSuffixArray(i) < line.size() / TRIPLE) {
            array.push_back(TRIPLE*smallLine.getSuffixArray(i) + 1);
        }
        else {
            array.push_back(TRIPLE*smallLine.getSuffixArray(i) + 2 - int(line.size()));
        }
    }
}

void SuffixArray::getSuffixArrayDivisibleTriple (std::vector <int> &array)
{
    for (int i = 0; i < triplets.size(); ++i) {
        array.push_back(triplets[i].second);
    }
}

void SuffixArray::getTripletLine (std::vector <int> &tripletLine)
{
    std::vector <int> sortingLine;
    sortingLine.resize(line.size());
    int countDifferent = 1;
    for (int j = 0; j < triplets.size(); ++j) {
        if (j != 0) {
            if (!equalTriplet(triplets[j].first, triplets[j - 1].first)) {
                countDifferent++;
            }
        }
        sortingLine[triplets[j].second] = countDifferent;
    }
    for (int j = 1; j < line.size(); j+=3) {
        tripletLine.push_back(sortingLine[j]);
    }
    for (int j = 2; j < line.size(); j+=3) {
        tripletLine.push_back(sortingLine[j]);
    }
}


int SuffixArray::getSuffixArray(int i)
{
    return suffixArray[i];
}

void SuffixArray::getTripletInDivisibleTriple()
{
    for (int i = 0; i < line.size(); ++i) {
        if (i % 3 == 0) {
            continue;
        }
        triplet element;
        for (int j = 0; j < TRIPLE; ++j) {
            if (i + j >= line.size()) {
                element.elements[j] = 0;
            }
            else {
                element.elements[j] = line[i + j];
            }
        }
        triplets.push_back(std::make_pair(element, i));
    }
}

void SuffixArray::getTripletDivisibleTriple(std::vector <int> &array)
{
    triplets.clear();
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] % 3 == 1) {
            triplet a ;
            a.elements[2] = 0;
            a.elements[1] = i;
            a.elements[0] = line[array[i] - 1];
            triplets.push_back(std::make_pair(a, array[i] - 1));
        }
    }
}

void SuffixArray::radixSort(std::vector <std::pair <triplet, int> > &array, int rank) // LSD
{
    rank = std::max(rank + 1, 26 + 1);
    std::vector <int> numberDigit;
    std::vector <std::pair <triplet, int> > sortingArray;
    sortingArray.resize(array.size());
    numberDigit.resize(rank);
    
    for (int i = TRIPLE - 1; i >= 0; --i) {
        for (int j = 0; j < rank; ++j) {
            numberDigit[j] = 0;
        }
        for (int j = 0; j < array.size(); ++j) {
            numberDigit[array[j].first.elements[i]]++;
        }
        int from = 0;
        for (int j = 0; j < rank; ++j) {
            int addFrom = numberDigit[j];
            numberDigit[j] = from;
            from += addFrom;
        }
        for (int j = 0; j < array.size(); ++j) {
            sortingArray[numberDigit[array[j].first.elements[i]]] = array[j];
            numberDigit[array[j].first.elements[i]]++;
        }
        for (int j = 0; j < array.size(); ++j) {
            array[j] = sortingArray[j];
        }
    }
}

void SuffixArray::mergeSuffixes (std::vector<int> &arrayDivisibleTriple, std::vector<int> &arrayInDivisibleTriple, int addSign)
{
    int i = 0, j = 0;
    std::vector <int> inverse;
    inverse.resize(line.size());
    for (int i = 0; i < arrayInDivisibleTriple.size(); ++i) {
        inverse[arrayInDivisibleTriple[i]] = i;
    }
    while (i < arrayInDivisibleTriple.size() && j < arrayDivisibleTriple.size()) {
        if (arrayInDivisibleTriple[i] % 3 == 1) {
            std::pair <int, int> firstElement, secondElement;
            firstElement = std::make_pair(line[arrayInDivisibleTriple[i]], inverse[arrayInDivisibleTriple[i] + 1]);
            secondElement = std::make_pair(line[arrayDivisibleTriple[j]], inverse[arrayDivisibleTriple[j] + 1]);
            if (firstElement < secondElement) {
                if (arrayInDivisibleTriple[i] < int(line.size()) - addSign) {
                    suffixArray.push_back(arrayInDivisibleTriple[i]);
                }
                ++i;
            }
            else {
                suffixArray.push_back(arrayDivisibleTriple[j]);
                ++j;
            }
        }
        else {
            std::pair <int, std::pair <int, int> > firstElement, secondElement;
            if (arrayInDivisibleTriple[i] == line.size() - 1) {
                firstElement = std::make_pair(line[arrayInDivisibleTriple[i]], std::make_pair(0, 0));
            }
            else {
                firstElement = std::make_pair(line[arrayInDivisibleTriple[i]],
                                              std::make_pair(line[arrayInDivisibleTriple[i] + 1], inverse[arrayInDivisibleTriple[i] + 2]));
            }
            secondElement = std::make_pair(line[arrayDivisibleTriple[j]],
                                           std::make_pair(line[arrayDivisibleTriple[j] + 1], inverse[arrayDivisibleTriple[j] + 2]));
            
            if (firstElement < secondElement) {
                if (arrayInDivisibleTriple[i] < int(line.size()) - addSign) {
                    suffixArray.push_back(arrayInDivisibleTriple[i]);
                }
                ++i;
            }
            else {
                suffixArray.push_back(arrayDivisibleTriple[j]);
                ++j;
            }
        }
    }
    while (i < arrayInDivisibleTriple.size()) {
        suffixArray.push_back(arrayInDivisibleTriple[i]);
        ++i;
    }
    while (j < arrayDivisibleTriple.size()) {
        suffixArray.push_back(arrayDivisibleTriple[j]);
        ++j;
    }
}