// Basic std::map demo: implementing a simple English-Italian dictionary
// by Giovanni dicanio

#include <iostream> // for std::cout
#include <map>      // for std::map
#include <string>   // for std:: string
using namespace std;

// Show some basic operations with std::map
int std_map_italianDictionary() {
    map<string, string> dictionary{
        //English  --->     Italian
        {"hello",           "ciao"},
        {"goodbye",         "arrivederci"},
        {"good morning",    "buon giorno"},
        {"good evening",    "buona sera"},
        {"thank you",       "grazie"},
        {"beautiful",       "bello(m.), bella(f.)"},
        {"church",          "chiesa"},
        {"pizza",           "pizza"},
        {"pasta",           "pasta"},
        {"ice cream",       "gelato"}
    };

    dictionary.insert({"museum", "museo"});
    dictionary.insert({"how much?", "quanto?"});

    cout << " English to Italian Dictionary \n";
    cout << " ----------------------------- \n";
    for (auto const& [english, italian]: dictionary) {
        cout << "   " << english << ": " << italian << '\n';
    }

    cout << "\n The Italian for 'thank you' is: '"
        << dictionary["thank you"] << "' \n";
    return 0;
}