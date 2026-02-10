#ifndef MONOM_MONOM_H
#define MONOM_MONOM_H

#define VARS_COUNT 3
#include <iostream>

class Monom {
    double _coeff;
    int _powers[VARS_COUNT];
public:
    Monom(double coeff = 0.0, std::initializer_list<int> powers = { 0, 0, 0 });
    Monom(const Monom&);

    bool operator==(const Monom&) const;
    bool operator!=(const Monom&) const;
    bool operator>(const Monom&) const;
    bool operator<(const Monom&) const;

    Monom operator+(const Monom&) const;
    Monom operator-(const Monom&) const;
    Monom operator*(const Monom&) const;
    Monom operator*(const double) const;
    Monom operator/(const Monom&) const;
    Monom operator/(const double) const;

    Monom& operator=(const Monom&);
    Monom& operator+=(const Monom&);
    Monom& operator-=(const Monom&);
    Monom& operator*=(const Monom&);
    Monom& operator/=(const Monom&);

    friend std::istream& operator>>(std::istream& in, Monom& monom) {
        std::string str;
        in >> str;

        monom.parse(str);
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Monom& monom) {
        if (abs(monom._coeff) != 1.0) out << monom._coeff;
        else if (monom._coeff == -1) out << "-";

        std::string vars = "xyz";
        for (int i = 0, j = 0; i < VARS_COUNT; i++, j++) {
            if (monom._powers[i] > 1)
                out << vars[j] << "^" << monom._powers[i];
            else if (monom._powers[i] == 1)
                out << vars[j];
        }

        return out;
    }
private:
    void parse(std::string);
    std::string read_number(std::string, int) const;
};

#endif // !MONOM_MONOM_H
