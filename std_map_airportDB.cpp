// Airport database:
// https://openflights.org/data.html

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Airport {
    string Name{};
    string City{};
    string Country{};
    double Latitude{};
    double Longitude{};
    int AltitudeFeet{};

    Airport() = default;

    Airport(string  const& name, string const& city, string const& country,
        double latitude, double longitude, int altitudeFeet)
        :Name(name), City(city), Country(country), Latitude(latitude),
        Longitude(longitude), AltitudeFeet(altitudeFeet){};

    //void printAll() {
    //    cout << " Airport name:     " << Name << '\n';
    //    cout << " City:             " << City << '\n';
    //    cout << " Country:          " << Country << '\n';
    //    cout << " Latitude:         " << Latitude << '\n';
    //    cout << " Longitude:        " << Longitude << '\n';
    //    cout << " Elevation (ft):   " << AltitudeFeet << '\n';
    //}
};


int std_map_airportDB(){
    map<string, Airport> airportDatabase{
        {"SEA",
            {"Seattle Tacoma International Airport", "Seattle", "United States",
             47.449001, -122.308998, 433}
        },
        {"LAX",
            {"Los Angeles International Airport", "Los Angeles", "United States",
             33.94250107, -118.4079971, 433}
        },
        {"FCO",
            {"Leonardo Da Vinci - Fiumicino Airport", "Rome", "Italy",
             41.8002778, 12.2388889, 13}
        },
        {"LHR",
            {"London Heathrow Airport", "London", "United Kingdom",
             51.4706, -0.461941, 83}
        }
    };

    cout << " Airport Database Demo \n";
    cout << " --------------------- \n\n";
    cout << " Airport unique code?";
    string code{};
    cin >> code;
    cout << '\n';

    // Look up airport information in the std::map database
    auto it = airportDatabase.find(code);
    if (it != airportDatabase.end()) {
        Airport const& airport = it->second;
        cout << " Airport name:     " << airport.Name           << '\n';
        cout << " City:             " << airport.City           << '\n';
        cout << " Country:          " << airport.Country        << '\n';
        cout << " Latitude:         " << airport.Latitude       << '\n';
        cout << " Longitude:        " << airport.Longitude      << '\n';
        cout << " Elevation (ft):   " << airport.AltitudeFeet   << '\n';
    }
    else {
        cout << " Sorry, airport code not found. \n";
    }
    return 0;
}