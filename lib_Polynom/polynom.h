#ifndef POLYNOM_POLYNOM_H
#define POLYNOM_POLYNOM_H

#include "../lib_Monom/monom.h"
#include "../lib_list/list.h"
#include <string>

class Polynom {
    std::string _name;
    List<Monom> _polynom;

public:
    Polynom();
    Polynom(std::string, const Monom&);
    Polynom(std::string, std::string);

    inline void set_name(std::string name) { _name = name; }

    Polynom operator+(const Polynom&) const noexcept;
    Polynom operator-(const Polynom&) const noexcept;
    Polynom operator+(const Monom&) const noexcept;
    Polynom operator-(const Monom&) const noexcept;
    Polynom operator-() const noexcept;
    Polynom operator*(const Polynom&) const noexcept;
    Polynom operator*(const Monom&) const noexcept;
    Polynom operator*(const double) const noexcept;
    Polynom operator/(const Monom&) const noexcept;
    Polynom operator/(const double) const noexcept;

    Polynom& operator=(const Polynom&);
    Polynom& operator+=(const Polynom&);
    Polynom& operator-=(const Polynom&);
    Polynom& operator+=(const Monom&);
    Polynom& operator-=(const Monom&);
    Polynom& operator*=(const Polynom&) noexcept;
    Polynom& operator*=(const Monom&) noexcept;
    Polynom& operator*=(const double) noexcept;
    Polynom& operator/=(const Monom&) noexcept;
    Polynom& operator/=(const double) noexcept;

    friend std::istream& operator>>(std::istream& in, Polynom& polynom) {
        std::string str;
        std::getline(std::cin, str);

        polynom._polynom.pop_front();  // delete 0
        polynom.parse(str);
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynom& polynom) {
        out << polynom.to_string();
        return out;
    }

    std::string to_string() const noexcept;

    double calculate(std::initializer_list<int> values = { 0, 0, 0 }) const;

private:
    void parse(std::string);
    std::string read_monom(std::string, int);
};

#endif // !POLYNOM_POLYNOM_H
