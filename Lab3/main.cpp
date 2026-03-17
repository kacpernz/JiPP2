#include <iostream>
#include <vector>
#include "Pojazd.hpp"

using namespace std;

int main() {
    vector<Pojazd*> parking;

    Pojazd* auto1 = new SamochodOsobowy("KK 11111");
    auto1->ustawCzasPostoju(2.5); 

    Pojazd* moto1 = new Motocykl("KR 2222");
    moto1->ustawCzasPostoju(1, 30); 

    Pojazd* elektryk1 = new PojazdElektryczny("KTA 33333");
    elektryk1->ustawCzasPostoju(5.0);

    parking.push_back(auto1);
    parking.push_back(moto1);
    parking.push_back(elektryk1);

    cout << "--- STATUS PARKINGU ---\n";
    
    for (const auto& p : parking) {
        cout << *p << "\n";
    }

    for (auto p : parking) {
        delete p;
    }

    return 0;
}