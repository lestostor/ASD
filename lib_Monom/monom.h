#ifndef MONOM_MONOM_H
#define MONOM_MONOM_H

#define VARS_COUNT 3
#include <iostream>

class Monom {
    double _coeff;
    int _powers[VARS_COUNT];
public:
    Monom(double coeff = 0.0, std::initializer_list<int> powers = { 0, 0, 0 });
    Monom(std::string);
    Monom(const Monom&);

    inline double coeff() { return _coeff; }

    bool operator==(const Monom&) const;
    bool operator!=(const Monom&) const;
    bool operator>(const Monom&) const;
    bool operator<(const Monom&) const;

    Monom operator+(const Monom&) const;
    Monom operator-(const Monom&) const;
    Monom operator-() const noexcept;
    Monom operator*(const Monom&) const noexcept;
    Monom operator*(const double) const noexcept;
    Monom operator/(const Monom&) const noexcept;
    Monom operator/(const double) const noexcept;

    Monom& operator=(const Monom&);
    Monom& operator+=(const Monom&);
    Monom& operator-=(const Monom&);
    Monom& operator*=(const Monom&) noexcept;
    Monom& operator*=(const double) noexcept;
    Monom& operator/=(const Monom&) noexcept;
    Monom& operator/=(const double) noexcept;

    double calculate(std::initializer_list<int> values = { 0, 0, 0 }) const;

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
    int read_coeff(std::string, int);  // return index of the first variable
    void read_powers(std::string, int);
};

#endif // !MONOM_MONOM_H
