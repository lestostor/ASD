#include "monom.h"

Monom::Monom(double coeff, std::initializer_list<int> powers) : _coeff(coeff) {
    auto it = powers.begin();
    int i = 0;
    for (auto it = powers.begin(); it < powers.end(); it++) {
        _powers[i] = *it;
        i++;
    }
}

Monom::Monom(const Monom& other) {
    this->_coeff = other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        _powers[i] = other._powers[i];
}

bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++)
        if (_powers[i] != other._powers[i]) return false;
    return true;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this).operator==(other);
}

bool Monom::operator>(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] > other._powers[i]) return true;
        if (_powers[i] < other._powers[i]) return false;
    }
    return false;
}

bool Monom::operator<(const Monom& other) const {
    return !(*this).operator>(other);
}

Monom Monom::operator+(const Monom& other) const {
    if (*this != other)
        throw std::invalid_argument("Monomials are not similar");

    Monom res(*this);
    res._coeff += other._coeff;

    return res;
}

Monom Monom::operator-(const Monom& other) const {
    if (*this != other)
        throw std::invalid_argument("Monomials are not similar");

    Monom res(*this);
    res._coeff -= other._coeff;

    return res;
}

Monom Monom::operator*(const Monom& other) const {
    Monom res(*this);

    res._coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        res._powers[i] += other._powers[i];

    return res;
}

Monom Monom::operator*(const double number) const {
    Monom res(*this);
    res._coeff *= number;

    return res;
}


Monom Monom::operator/(const Monom& other) const {
    Monom res(*this);

    res._coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        res._powers[i] -= other._powers[i];

    return res;
}

Monom Monom::operator/(const double number) const {
    Monom res(*this);
    res._coeff /= number;

    return res;
}

Monom& Monom::operator=(const Monom& other) {
    if (this == &other)
        return *this;
    this->_coeff = other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        this->_powers[i] = other._powers[i];

    return *this;
}

Monom& Monom::operator+=(const Monom& other) {
    if (*this != other)
        throw std::invalid_argument("Monomials are not similar");

    this->_coeff += other._coeff;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (*this != other)
        throw std::invalid_argument("Monomials are not similar");

    this->_coeff -= other._coeff;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    this->_coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        this->_powers[i] += other._powers[i];

    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    this->_coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        this->_powers[i] -= other._powers[i];

    return *this;
}

void Monom::parse(std::string str) {
    int i, j = 0;
    std::string num;
    if (str[0] != 'x' && str[0] != 'y' && str[0] != 'z') {
        num = read_number(str, 0);
        i = num.size();

        if (num == "-")
            _coeff = -1.0;
        else
            _coeff = std::atof(num.c_str());
    }
    else if (str[0] == 'x' || str[0] == 'y' || str[0] == 'z') {
        _coeff = 1.0;
        i = 0;
    }
    else
        throw std::invalid_argument("Unexpected symbol");

    while (i < str.size()) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = read_number(str, i);
            i += num.size();
            _powers[j] = std::atof(num.c_str());
        }
        else {
            if (str[i] == 'x')
                j = 0;
            else if (str[i] == 'y')
                j = 1;
            else if (str[i] == 'z')
                j = 2;
            else
                throw std::invalid_argument("Unexpected symbol");

            if (str[i + 1] != '^') {
                _powers[j] = 1;
                i++;
                continue;
            }
            i += 2;
        }
    }
}

std::string Monom::read_number(std::string str, int pos) const {
    std::string number = "";
    for (int i = pos; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '.' ||
            pos == 0 && str[i] == '-')
            number += str[i];
        else if (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')
            break;
    }
    return number;
}