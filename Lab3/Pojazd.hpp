#ifndef POJAZD_HPP
#define POJAZD_HPP

#include <iostream>
#include <string>

class Pojazd {
protected:
    std::string nrRejestracyjny;
    double czasPostoju; 

public:
    Pojazd(std::string nr);
    virtual ~Pojazd() = default; 

    void ustawCzasPostoju(double godziny);
    void ustawCzasPostoju(int godziny, int minuty);

    virtual double obliczOplate() const = 0;

    virtual void wypiszInfo(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Pojazd& p);
};

class SamochodOsobowy : public Pojazd {
public:
    SamochodOsobowy(std::string nr);
    double obliczOplate() const override;
    void wypiszInfo(std::ostream& os) const override;
};

class Motocykl : public Pojazd {
public:
    Motocykl(std::string nr);
    double obliczOplate() const override;
    void wypiszInfo(std::ostream& os) const override;
};

class PojazdElektryczny : public Pojazd {
public:
    PojazdElektryczny(std::string nr);
    double obliczOplate() const override;
    void wypiszInfo(std::ostream& os) const override;
};

#endif // POJAZD_HPP