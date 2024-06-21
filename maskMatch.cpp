#include "maskMatch.h"
#include <Windows.h>

BOOL maskMatcher::matchesMask(std::string mask, UINT64 input) {
    //first argument in the TOPO suit without errors is LPCTSTR mask
    //userMask = static_cast<std::string>(mask); // In the TOPO suite.
    userMask = mask;

    cleanBlanks();
    if (containsOperator()) {
        eraseOperator();
    }
    if (containsAsterisk()) {
        collectToken();
        collectCoefficient();
        expandTokens();
        replaceTokens();
    }
    convertMaskToNumber(input);
    return conditionalComparison();
}

void maskMatcher::cleanBlanks() {
    userMask.erase(
        std::remove_if(
            userMask.begin(),
            userMask.end(),
            ::isspace
        ),
        userMask.end()
    );
}

BOOL maskMatcher::containsOperator() {
    BOOL result = TRUE;
    const int firstChar = 0;
    const int lastChar = 2;
    const enum condition { equal, lessThan, greaterThan };
    const std::string firstTwoChars = userMask.substr(firstChar, lastChar);
    if (firstTwoChars == "==") { operation = equal; }
    else if (firstTwoChars == "<=") { operation = lessThan; }
    else if (firstTwoChars == ">=") { operation = greaterThan; }
    else {
        operation = equal;
        result = FALSE;
    }
    return result;
}

void maskMatcher::eraseOperator() {
    const int firstChar = 0;
    const int lastChar = 2;
    userMask.erase(firstChar, lastChar);
}

BOOL maskMatcher::containsAsterisk() {
    BOOL short_hand = static_cast<BOOL>(
        std::any_of(begin(userMask), end(userMask), [](char c) {return c == '*'; }));
    return short_hand;
}

void maskMatcher::collectToken() {
    const int size = static_cast<int>(userMask.size());
    for (int i = 0; i < size; i++) {
        if (userMask[i] == '*')
            token += userMask[i + 1];
    }
}

void maskMatcher::collectCoefficient() {
    int startPosition{};
    std::string result{};
    while (true)
    {
        char startChar = '(';
        char endChar = '*';
        auto start = userMask.find(startChar, startPosition);
        auto end = userMask.find(endChar, start + 1);
        if (start == std::string::npos || end == std::string::npos)
            break;
        result = userMask.substr(start + 1, end - start - 1);
        coefficient.push_back(std::stoi(result));
        startPosition = static_cast<int>(end + 1);
    }
}

void maskMatcher::expandTokens() {
    std::string extendedToken{};
    const int clenght = static_cast<int>(coefficient.size());
    for (int i = 0; i < clenght; ++i) {
        extendedToken.append(coefficient[i], token[i]);
        extendedTokens.push_back(extendedToken);
        extendedToken.clear();
    }
}

void  maskMatcher::replaceTokens() {
    int currentIndex{};
    int openPosition{};
    int closePosition{};
    int tokenIndex = 0;
    while (true) {
        openPosition = static_cast<int>(userMask.find('(', currentIndex));
        closePosition = static_cast<int>(userMask.find(')', openPosition));
        if (openPosition == std::string::npos || closePosition == std::string::npos)
            break;
        int newTextIndex = tokenIndex % extendedTokens.size();
        userMask.replace(openPosition,
            closePosition - openPosition + 1,
            extendedTokens[newTextIndex]);
        currentIndex = openPosition
            + static_cast<int>(extendedTokens[newTextIndex].size());
        tokenIndex++;
    }
}

void maskMatcher::convertMaskToNumber(UINT64 input) {
    std::bitset<32> originalAddress(input);
    const int MaskSize = static_cast<int>(userMask.size());
    for (int bit = MaskSize; bit > 0; bit--) {
        if (userMask[bit - 1] == 'X' || userMask[bit - 1] == 'x') continue;
        // Reverse mask and casts tokens ('0' an '1') to numeric values.
        mask_fixed[MaskSize - bit] = userMask[bit - 1] - '0';
        addr_fixed[MaskSize - bit] = originalAddress[MaskSize - bit];
    }
}

BOOL maskMatcher::conditionalComparison() {
    const enum { equal, lessThan, greaterThan };
    UINT32 maskToCompare = mask_fixed.to_ulong();
    UINT32 addressToCompare = addr_fixed.to_ulong();
    switch (operation)
    {
    case equal:
        if (addressToCompare == maskToCompare) { return TRUE; }
        else { return FALSE; }
    case lessThan:
        if (addressToCompare <= maskToCompare) { return TRUE; }
        else { return FALSE; }
    case greaterThan:
        if (addressToCompare >= maskToCompare) { return TRUE; }
        else { return FALSE; }
    default:
        return FALSE;
    }
}
//UINT64 maskMatcher::AllBitsMaskResult(LPCTSTR mask, UINT64 input) {
UINT64 maskMatcher::AllBitsMaskResult(std::string mask, UINT64 input) {
    UINT64 result{};
    if (matchesMask(mask, input))
        result = 0xFFFFFFFF;
    return result;
}
//End class implementation

//**************Test function***************

void testFun(const std::vector<std::string> &testMasks,
    const std::vector<std::string> &expectedMasks){
    int counter{};
    for (int i = 0; i < testMasks.size(); i++) {
        maskMatcher Test1;
        if (Test1.getUserMask(testMasks[i]) != expectedMasks[i]) {
            cout << "Mask[" << i << "] does not match expected." << endl;
        }
        else {
            counter++;
        }
    }
    cout << "Result:" << counter << "/" << testMasks.size() << " correct." << endl;
    std::string result;
    result = (counter == testMasks.size()) ? "PASS\n" : "FAIL\n";
    cout << result;
}

using namespace std;

int run_maskMatch() {
    const std::vector<std::string>testMasks{
        "XXX1",
        "101X",
        "(4*1) 11XX",
        "(3*x)1100(2*1)",
        "(5*X)(6*1)(7*0)",
        "11110000(4*X)",
        "1100(6*1)001",
        "(20*X)1XX0"
    };
    const std::vector<std::string>expectedMasks{
        "XXX1",
        "101X",
        "111111XX",
        "xxx110011",
        "XXXXX1111110000000",
        "11110000XXXX",
        "1100111111001",
        "XXXXXXXXXXXXXXXXXXXX1XX0"
    };

    testFun(testMasks, expectedMasks);

    return 0;
}