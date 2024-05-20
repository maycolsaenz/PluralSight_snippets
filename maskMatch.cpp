#include "maskMatch.h"

//Class implementation
BOOL maskMatch::matchesMask(std::string mask, UINT64 input) { //I changed the mask type
    BOOL result = TRUE;
    userMask = mask;
    //userMask = static_cast<std::string>(mask); //I don't get this error in ATOPO suite.


    //Functions working
    cleanBlanks();
    if (setOperator()) {
        eraseOperator();
    }
    if (anyAsterisk()) {
        setToken();
        setCoefficient();
        expandTokens();
    }
    result &= compare(input);

    return result;
}
void maskMatch::cleanBlanks() {
    userMask.erase(std::remove_if(userMask.begin(), userMask.end(), ::isspace),
        userMask.end());
}
BOOL maskMatch::setOperator() {
    BOOL result = TRUE;
    const std::string firstTwoChars = userMask.substr(0, 2);
    if (firstTwoChars == "==") { operation = 0; }
    else if (firstTwoChars == "<=") { operation = 1; }
    else if (firstTwoChars == ">=") { operation = 2; }
    else {
        operation = 0;
        result = FALSE; }
    return result;
}
void maskMatch::eraseOperator() {
    userMask.erase(0, 2);
}

BOOL maskMatch::anyAsterisk() {
    BOOL short_hand =static_cast<BOOL>(
        std::any_of(
            begin(userMask),
            end(userMask),
            [](char c){return c == '*';}
        )
    );
    return short_hand;
}
void maskMatch::setToken() {
    const int size = static_cast<int>(userMask.size());
    for (int i = 0; i < size; i++) {
        if (userMask[i] == '*')
            token += userMask[i + 1];
    }
}
void maskMatch::setCoefficient() {
    int startPosition{};
    std::string result{};
    while(true)
    {
        char startChar = '(';
        char endChar = '*';

        int start = userMask.find(startChar, startPosition);
        if (start == std::string::npos)
            break;
        int end = userMask.find(endChar, start + 1);
        if (end == std::string::npos)
            break;
        result = userMask.substr(start + 1, end - start - 1);
        coefficient.push_back(std::stoi(result));
        startPosition = end + 1; 
    }
}

void maskMatch::expandTokens() {
    std::vector<std::string> extendedTokens{};
    std::string extendedToken{};
    const int clenght = static_cast<int>(coefficient.size());
    for (int i = 0; i < clenght; ++i) {
        extendedToken.append(coefficient[i], token[i]);
        extendedTokens.push_back(extendedToken);
        extendedToken.clear();
    }

    int currentIndex{};
    int openPos{};
    int closePos{};
    while (true) {
        openPos = userMask.find('(', currentIndex);
        if (openPos == std::string::npos)
            break;
        closePos = userMask.find(')', openPos);
        if (closePos == std::string::npos)
            break;
        int newTextIndex = currentIndex % extendedTokens.size();
        userMask.replace(openPos,
            closePos - openPos + 1,
            extendedTokens[newTextIndex]);
        currentIndex = openPos + extendedTokens[newTextIndex].size();
    }
}
BOOL maskMatch::compare(UINT64 input) {
    BOOL result = TRUE;
    std::bitset<32> mask_fixed;
    std::bitset<32> addr_fixed;
    std::bitset<32> originalAddress(input);
    const int MaskSize = static_cast<int>(userMask.size());
    for (int bit = MaskSize; bit > 0; bit--) {
        if (userMask[bit - 1] == 'X' || userMask[bit - 1] == 'x') continue;
        mask_fixed[MaskSize - bit] = userMask[bit - 1] - '0';
        addr_fixed[MaskSize - bit] = originalAddress[MaskSize - bit];
    }
    UINT32 maskToCompare = mask_fixed.to_ulong();
    UINT32 addressToCompare = addr_fixed.to_ulong();
    result &= conditionalComparison(maskToCompare, addressToCompare);
    return result;
}

BOOL maskMatch::conditionalComparison(UINT32 msk, UINT32 addr) {
    switch (operation) 
    {
    case 0:
        if (addr == msk) { return TRUE; }
        else { return FALSE; }
    case 1:
        if (addr <= msk) { return TRUE; }
        else { return FALSE; }
    case 2:
        if (addr >= msk) { return TRUE; }
        else { return FALSE; }
    default:
        return FALSE;
    }
}

//Aux
std::string maskMatch::getUserMask() {
    return userMask;
}


//End class implementation

using namespace std;

int run_maskMatch() {
    std::string mask1 = "== (2*X)(4*1)";

    maskMatch Test1;
    UINT64 input = 0x2f;
    BOOL TestResult{};
    TestResult = Test1.matchesMask(mask1, input);
    std::cout << "ResultTest = " << TestResult << std::endl;
    std::cout << "Final mask = " << Test1.getUserMask() << std::endl;


    return 0;
}