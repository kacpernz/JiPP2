#include "Pojazd.hpp"
#include <iomanip>

using namespace std;

Pojazd::Pojazd(string nr) : nrRejestracyjny(nr), czasPostoju(0) {}

void Pojazd::ustawCzasPostoju(double godziny) {
    czasPostoju = godziny;
}

void Pojazd::ustawCzasPostoju(int godziny, int minuty) {
    czasPostoju = godziny + (minuty / 60.0);
}

void Pojazd::wypiszInfo(ostream& os) const {
    os << "Nr Rej: " << nrRejestracyjny 
       << " | Czas: " << fixed << setprecision(1) << czasPostoju << "h";
}

ostream& operator<<(ostream& os, const Pojazd& p) {
    p.wypiszInfo(os); 
    return os;
}

SamochodOsobowy::SamochodOsobowy(string nr) : Pojazd(nr) {}

double SamochodOsobowy::obliczOplate() const {
    return czasPostoju * 5.0; 
}

void SamochodOsobowy::wypiszInfo(ostream& os) const {
    os << "[Osobowy]  ";
    Pojazd::wypiszInfo(os);
    os << " | Oplata: " << obliczOplate() << " PLN";
}

Motocykl::Motocykl(string nr) : Pojazd(nr) {}

double Motocykl::obliczOplate() const {
    return 10.0 + (czasPostoju * 2.0);
}

void Motocykl::wypiszInfo(ostream& os) const {
    os << "[Motocykl] ";
    Pojazd::wypiszInfo(os);
    os << " | Oplata: " << obliczOplate() << " PLN";
}

PojazdElektryczny::PojazdElektryczny(string nr) : Pojazd(nr) {}

double PojazdElektryczny::obliczOplate() const {
    return 0.0;
}

void PojazdElektryczny::wypiszInfo(ostream& os) const {
    os << "[Elektryk] ";
    Pojazd::wypiszInfo(os);
    os << " | Oplata: BEZPLATNIE";
}