#pragma once

#include <Windows.h>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <functional>
#include <iostream>
using namespace std;
class maskMatch {
private:
    std::string userMask{};
    std::string token{};
    int operation{};
    std::vector<int>coefficient{};
public:
    maskMatch() = default;
    BOOL matchesMask(std::string mask, UINT64 input);
    void cleanBlanks();
    BOOL setOperator();
    void eraseOperator();
    BOOL anyAsterisk();
    void setToken();
    void setCoefficient();
    void expandTokens();
    BOOL compare(UINT64 input);
    BOOL conditionalComparison(UINT32 msk, UINT32 addr);
    //Aux
    std::string getUserMask();
};