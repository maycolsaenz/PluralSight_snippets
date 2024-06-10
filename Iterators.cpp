// Iterators.cpp: Defines the entry point for the console application.
#include "functions.h"

using namespace std;

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

    //Almost any algorithm min 5:25

    return 0;
}
