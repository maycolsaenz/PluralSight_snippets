#include "functions.h"
#include "maskMatch.h"
#include "inputCrossover.h"

//#define map_airportDB
//#define map_italianDictionary
//#define count
//#define find
//#define sorting
//#define comparing
//#define test_maskMatcher
//#define test_vectorFront
//#define singleton_1
//#define Generating
//#define inputWithCrossoverBits
//#define iterator
//#define unexpected
#define measureTime

int main() {

#ifdef map_airportDB
    std_map_airportDB();
#endif

#ifdef map_italianDictionary
    std_map_italianDictionary();
#endif

#ifdef count
    std_count();
#endif

#ifdef find
    std_find();
#endif

#ifdef sorting
    std_sorting();
#endif

#ifdef comparing
    std_comparing();
#endif

#ifdef test_maskMatcher
    run_maskMatch();
#endif

#ifdef test_vectorFront
    vectorFront();
#endif

#ifdef singleton_1
    singleton1();
#endif

#ifdef Generating
    generatingManipulating();
#endif

#ifdef inputWithCrossoverBits
    inputCrossover();
#endif

#ifdef iterator
    iterators();
#endif

#ifdef unexpected
    unexpectedOperations();
#endif

#ifdef measureTime
    timing();
#endif

}
