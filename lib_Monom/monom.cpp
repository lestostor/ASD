#include "monom.h"

Monom::Monom(double coeff, std::initializer_list<int> powers) : _coeff(coeff) {
    auto it = powers.begin();
    int i = 0;
    for (auto it = powers.begin(); it < powers.end(); it++) {
        _powers[i] = *it;
        i++;
    }
}

Monom::Monom(std::string str) {
    parse(str);
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
    return !(*this > other) && *this != other;
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

Monom Monom::operator-() const noexcept {
    Monom res(*this);
    res._coeff *= -1;
    return res;
}

Monom Monom::operator*(const Monom& other) const noexcept {
    Monom res(*this);

    res._coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        res._powers[i] += other._powers[i];

    return res;
}

Monom Monom::operator*(const double number) const noexcept {
    Monom res(*this);
    res._coeff *= number;

    return res;
}


Monom Monom::operator/(const Monom& other) const noexcept {
    Monom res(*this);

    res._coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        res._powers[i] -= other._powers[i];

    return res;
}

Monom Monom::operator/(const double number) const noexcept {
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

Monom& Monom::operator*=(const Monom& other) noexcept {
    this->_coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        this->_powers[i] += other._powers[i];

    return *this;
}

Monom& Monom::operator*=(const double number) noexcept {
    this->_coeff *= number;
    return *this;
}

Monom& Monom::operator/=(const Monom& other) noexcept {
    this->_coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; i++)
        this->_powers[i] -= other._powers[i];

    return *this;
}

Monom& Monom::operator/=(const double number) noexcept {
    if (number == 0)
        throw std::logic_error("Division by 0");
    this->_coeff /= number;
    return *this;
}

double Monom::calculate(std::initializer_list<int> values) const {
    double res = _coeff;
    int i = 0;

    for (auto it = values.begin(); it != values.end(); it++)
        res *= pow(*it, _powers[i++]);

    return res;
}

std::string Monom::to_string() const noexcept {
    std::string str = "";

    if (abs(_coeff) != 1.0) str += std::to_string(_coeff);
    else if (_coeff == -1) str = "-";

    std::string vars = "xyz";
    for (int i = 0, j = 0; i < VARS_COUNT; i++, j++) {
        if (_powers[i] > 1)
            str += std::string(1, vars[j]) + "^" + std::to_string(_powers[i]);
        else if (_powers[i] == 1)
            str += vars[j];
    }

    return str;
}

void Monom::parse(std::string str) {
    int i = 0, j = 0;
    std::string num;
    for (int k = 0; k < VARS_COUNT; k++) _powers[k] = 0;

    for (i; str[i] == ' '; i++);

    i = read_coeff(str, i);

    read_powers(str, i);
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

int Monom::read_coeff(std::string str, int pos) {
    std::string num = "";
    int i = pos;

    if (str[0] >= '0' && str[0] <= '9' || str[0] == '-') {
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

    return i;
}

void Monom::read_powers(std::string str, int pos) {
    std::string num = "";
    int i = pos, j = 0;

    while (i < str.size()) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = read_number(str, i);
            i += num.size();
            _powers[j] = std::atof(num.c_str());
        }
        else if (str[i] != ' ') {
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
        else i++;
    }
}