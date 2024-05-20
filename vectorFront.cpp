#include "functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int vectorFront() {
    vector<int>numbers = { 5, 4, 3, 2, 1, 0 };
    vector<std::string>letters = { "firstOne", "secondOne", "thirdOne", "fourthOne"};

    cout << "The first number is: " << numbers.front() << " and " << letters.front()
        << endl;


    return 0;
}