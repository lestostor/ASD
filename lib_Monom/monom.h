#ifndef MONOM_MONOM_H
#define MONOM_MONOM_H

#define VARS_COUNT 3
#include <iostream>
#include <string>
#include <cmath>

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
        out << monom.to_string();
        return out;
    }

    std::string to_string() const noexcept;

private:
    void parse(std::string);
    std::string read_number(std::string, int) const;
    int read_coeff(std::string, int);  // return index of the first variable
    void read_powers(std::string, int);
};

#endif // !MONOM_MONOM_H
