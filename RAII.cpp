// RAII. cpp: Defines the entry point for the console application.
// PluralSight Demo: RAII (min 4:58)

#include <iostream>
#include "Resource_RAII.h"
using std::cout;
using std::cin;

int RAII() {
    // Ask for file name
    cout << "Enter full path to file";
    char filepath[255];
    cin.getline(filepath, 255);

    try
    {
        // Open file
        ResourceRAII numbersfile{ filepath };

        if (numbersfile.OK())
        {
            cout << "first line is: \n";
            cout << numbersfile.GetLine();
            char ans;
            cout << "Continue? (y/n)";
            cin >> ans;
            if (ans == 'y')
            {
                numbersfile.ProcessLines();
                cout << numbersfile.GetLineCount() + 1 << " lines read. \n";
            }
        }
        else
        {
            cout << "Could not open file: " << filepath << "\n";
        }

        // Actually use numbers for something or otherwise genuinely process the file
        // eg numbersfile.AccessNumber(i)
    }
    catch (...)
    {
        cout << "An error occurred.";
    }
    return 0;
}