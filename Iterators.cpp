// Iterators.cpp: Defines the entry point for the console application.
#include "functions.h"

using namespace std;
using std::string;
int iterators() {

    // Preallocating the vector size
    vector<int>v1(10);
    fill(begin(v1), end(v1), 1);
    fill_n(begin(v1), 6, 2);
    iota(begin(v1), end(v1), 1);

    // Without preallocating the vector
    vector<int> v2;
    fill_n(back_inserter(v2), 6, 2);

    /* This will add 10 elements after the previous 6.
     * For each one it will return the operation in the lambda.
     * [n = 10]This is called 'alias capture' in the lambda.
     * Caviat: vector does not support front_inserter().
     */ 
    generate_n(back_inserter(v2), 10, [n = 10]()mutable{return n++;});

    // For a collection that supports front_inserter()
    deque<int> q3;
    fill_n(front_inserter(q3), 6, 2);
    generate_n(front_inserter(q3), 10, [n = 0]()mutable{return n++;});

    /* Vector does not support front_inserter:
     * fill_n(front_inserter(v1), 6, 2);
     */

    /* Examples with transform()
     * This will insert elements from v1 into v2 multiplied by 2.
     */
    v2.clear();
    transform(begin(v1), end(v1), back_inserter(v2),
        [](int elem){return elem*2;});

    /* Fixing the problem of using copy_if without knowing
     * the size of the collection.
     */
    vector<int> v3{ 3, 6, 1, 0, -2, 5 };
    vector<int> v5;
    copy_if(begin(v3), end(v3), back_inserter(v5),
        [](int elem){return elem % 2 == 0; });
    
    // Eliminating duplicates
    v3[3] = -2;
    vector<int> v6;
    unique_copy(begin(v3), end(v3), back_inserter(v6));

    // With strings
    string sentence = "Hellow, world!";
    string reverse;
    reverse_copy(begin(sentence), end(sentence), back_inserter(reverse));

    /* inserter works for algorithms that don't rely on a distance:
     * fill_n but not fill
     * generate_n but not generate
     * transform
     * copy, copy_if
     * unique_copy
     * reverse_copy
     */

    // Reverse iterators
    v2.clear();
    copy(rbegin(v1), rend(v1), back_inserter(v2));

    v1[5] = 2;
    auto two = find(begin(v1), end(v1), 2);
    auto distance = two - begin(v1);
    // By looking at the next value we can figure out which 2 was found.
    two++;
    
    // An iterator and a reverse iterator are not of the same type.
    auto rtwo = find(rbegin(v1), rend(v1), 2);
    distance = rtwo - rbegin(v1);
    rtwo++;
   
    // distance = rtwo - two; // This is an error.

    // Iterator Arithmetic

    // Is "3" in the first or second half?
    auto three = find(begin(v1), end(v1), 3);
    bool firsthalf = (three - begin(v1) < end(v1) - three);
    // What about "9";
    auto nine = find(begin(v1), end(v1), 9);
    firsthalf = (nine - begin(v1) < end(v1) - nine);
    
    // Iterators to const Elements
    array<const int, 5>ca = { 3, 1, 6, 0, 2 };
    auto it = begin(ca);
    it++;
    // *it = 7;
    int i = *it;

    //vector<const int> vc; // vector does not support const elements.

    it = find(begin(ca), end(ca), 1);
    it++;
    // *it = 7;
    // it = cbegin(ca);

    auto it2 = begin(v2);
    it2++;
    *it2 = 7;

    auto cit = cbegin(v2);
    cit++;
    // *cit = 7;

    return 0;
}
