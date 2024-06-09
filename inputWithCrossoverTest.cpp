#include "functions.h"
#include "maskMatch.h"

const int BITS_ADDRESS_PER_OPERATION = 24;


UINT64 inputWithCrossover(
    UINT64 input,
    UINT64 crossover,
    const std::vector<int> xycrossoverbits)
{
    std::bitset<24>crossoverAddress(crossover);
    UINT64 mask29Bits = 0x1FFFFFFF;
    UINT64 crossoverBitsMask = 0b11111;
    UINT64 singleBit = 0;
    UINT64 maskBits = 0;
    const int iterator = 1;

    for (auto i = xycrossoverbits.rbegin(); i != xycrossoverbits.rend(); ++i) {
        singleBit = crossoverAddress[*i] ? 0b1 : 0b0;
        maskBits = (maskBits << iterator) | singleBit;
    }
    UINT64 crossoverBits = maskBits & crossoverBitsMask;
    UINT64 result = (crossoverBits << BITS_ADDRESS_PER_OPERATION | input) & mask29Bits;
    return result;
}

int inputCrossover() {

    const std::vector<int> crossoverBitsY{ 4, 0, 1, 3, 23 };
    const std::vector<int> crossoverBitsX{ 4, 1, 0, 3, 23 };

    for (UINT64 input = 0; input < 50; input++) {
        UINT64 crossover = input + 10;
        UINT64 completeInputX = inputWithCrossover(input, crossover, crossoverBitsY);
    }

    return 0;
}