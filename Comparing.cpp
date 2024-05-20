#include "functions.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int std_comparing() {
    vector<int> a{ 1, 2, 3, 4, 5 };
    vector<int> b{ 1, 2, 0, 4 };

    // No STL algorithm version
    bool same = a.size()==b.size();
    for (size_t i = 0; i < a.size() && same; i++) {
        if (a[i] != b[i]) {
            same = false;
        }
    }
    // Using STL Algorithm
    same = equal(begin(a), end(a), begin(b), end(b));

    auto firstChange = mismatch(begin(a), end(a), begin(b), end(b));

    int avalue = *(firstChange.first);
    int bvalue = *(firstChange.second);
    auto distance = firstChange.first - begin(a);

    // Accumulate with no STL algorithm
    int total = 0;
    for (int i : a)
    {
        total += i;
    }

    // Accumulate with STL algorithm
    total = accumulate(begin(a), end(a), 0);
    // Where 0 is the starting value.

    // Using lambdas
    total = accumulate(begin(a), end(a), 0,
        [](int total, int i) {if (i % 2 == 0) return total + i; return total; });
    // This one multiplies all elements. Note the number 1, instead of 0.
    total = accumulate(begin(a), end(a), 1,
        [](int total, int i) {return total * i; });

    // Accumulating strings
    vector<string> words{ "one", "two", "three" };
    auto allwords = accumulate(begin(words), end(words), string{});
    int length = allwords.size();

    allwords = accumulate(begin(words), end(words), string{ "Words:" },
        [](const string& total, string& s) {return total + " " + s; });

    string s = accumulate(begin(a), end(a), string{"The numbers are:"},
        [](const string& total, int i) {return total + " " + to_string(i); });

    // Common raw loops
    b = a;
    for (auto it = begin(b); it != end(b); it++)
    {
        *it = 0;
    }

    for (auto& i : b)
    {
        i = 1;
    }

    for_each(begin(b), end(b), [](int& elem) {elem = 2; });

    // For the aforementioned cases, the second option is the best. for_each is the best
    //option when we don't want to work with the whole range of elements:
    b = a;
    auto firstthree = find(begin(b), end(b), 3);
    for_each(firstthree, end(b), [](int& elem) {elem = 0; });

    return 0;
}