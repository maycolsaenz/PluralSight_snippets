#include "functions.h"
#include "Employee.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>    // for abs
#include <random>

using namespace std;

int std_sorting() {
    vector<int> v{ 4, 1, 0, 1, -2, 3, 7, -6, 2, 0, 0, -9, 9 };
    auto v2 = v;

    //Sort them according to their numerical values
    sort(begin(v2), end(v2));

    /*! For this one, the lambda should return a comparison.
     *  This should sort it in the opposite way.
     */
    sort(begin(v2), end(v2), [](int elem1, int elem2) { return elem1 > elem2; });

    //This one sorts them according to their absolute value. Descending order.
    sort(begin(v2), end(v2),
        [](int elem1, int elem2) { return abs(elem1) > abs(elem2); });
    
    std::vector<Employee> staff{
        {"Kate", "Gregory", 1000},
        {"Obvious", "Artificial", 2000},
        {"Fake", "Name", 1000},
        {"Alan", "Turing", 2000},
        {"Grace", "Hopper", 2000},
        {"Anita", "Borg", 2000}
    };

    //std::sort(begin(staff), end(staff)); //- only works if operator< defined for Employee
    std::sort(begin(staff), end(staff),
        [](Employee e1, Employee e2) {return e1.getSalary() < e2.getSalary(); });
    std::sort(begin(staff), end(staff),
        [](Employee e1, Employee e2) {return e1.getSortingName() < e2.getSortingName(); });

    std::sort(begin(staff), end(staff),
        [](Employee e1, Employee e2) {return e1.getSortingName() < e2.getSortingName(); });
    std::stable_sort(begin(staff), end(staff),
        [](Employee e1, Employee e2) {return e1.getSalary() < e2.getSalary(); });

    auto sorted = is_sorted(begin(v2), end(v2));
    sorted = is_sorted(begin(v2), end(v2), [](int elem1, int elem2) {return abs(elem1) > abs(elem2); });

    //For unsorted collections
    int high = *(max_element(begin(v), end(v)));
    int low = *(min_element(begin(v), end(v)));
    //For sorted collections
    sort(begin(v2), end(v2));
    low = *begin(v2);
    high = *(end(v2) - 1); // Remember: end(v2) points to pass the last element.
    int positive = *upper_bound(begin(v2), end(v2), 0); // Find the first element that is
                                                        // greater than cero.

    std::sort(begin(staff), end(staff),
        [](Employee e1, Employee e2) {return e1.getSortingName() < e2.getSortingName(); });

    //Find the first element that is not less than
    auto p = std::lower_bound(begin(staff), end(staff), "Gregory, Kate",
        [](Employee e1, std::string n) {return e1.getSortingName() < n; });
    //Dereferences the value
    int sal = p->getSalary();

    //Suffling
    random_device randomdevice;
    mt19937 generator(randomdevice());

    shuffle(begin(v2), end(v2), generator);

    /* Partial sort: The first and last arguments are the data source origin.
        *               Elements will be sorted until the position of 4. Any number in that
        *               position and after will be greater than the ordered ones but
        *               will not be sorted out. So, the position of number 4 is the first
        *               one when numbers will not be sorted any more.
        */
    partial_sort(begin(v2), find(begin(v2), end(v2), 4), end(v2));

    /* Returns the point on which numbers are not in order any more.Everything before
        * that number is sorted.
        */
    int breakpoint = *is_sorted_until(begin(v2), end(v2));

    vector<int> v3(3); // A vector holding 3 elements.
                        //Copy from to   | Into this range.But only the 3 smallest ordered values of v.
    partial_sort_copy(begin(v), end(v), begin(v3), end(v3));

    // Nth Element
    v2 = { 1, 5, 4, 2, 9, 7, 3, 8, 2 };
    int i = *(begin(v2) + 4);   // i = 9 at it(4).
    // This returns the value that would be in that position if the vector were sorted.
    nth_element(begin(v2), begin(v2) + 4, end(v2));
    i = *(begin(v2) + 4);



    return 0;
}
