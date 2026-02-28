#include "polynom.h"

Polynom::Polynom() {
    Monom zero;
    _name = "zero";
    _polynom.push_back(zero);
}

Polynom::Polynom(std::string name, const Monom& monom) : _name(name) {
    _polynom.push_back(monom);
}

Polynom::Polynom(std::string name, std::string polynom) : _name(name) {
    parse(polynom);
}

Polynom Polynom::operator+(const Polynom& other) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0
    auto it1 = this->_polynom.begin(), it2 = other._polynom.begin();
    Monom monom;

    while (it1 != this->_polynom.end() || it2 != other._polynom.end()) {
        if (it2 == other._polynom.end() ||
            (it1 != this->_polynom.end() && *it1 > *it2)) {
            monom = *it1;
            ++it1;
        }
        else if (it1 == this->_polynom.end() ||
            (it2 != other._polynom.end() && *it1 < *it2)) {
            monom = *it2;
            ++it2;
        }
        else {
            monom = *it1 + *it2;
            ++it1;
            ++it2;
        }

        if (monom.coeff() != 0)
            res._polynom.push_back(monom);
    }

    return res;
}

Polynom Polynom::operator-(const Polynom& other) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0
    auto it1 = this->_polynom.begin(), it2 = other._polynom.begin();
    Monom monom;

    while (it1 != this->_polynom.end() || it2 != other._polynom.end()) {
        if (it2 == other._polynom.end() ||
            (it1 != this->_polynom.end() && *it1 > *it2)) {
            monom = *it1;
            ++it1;
        }
        else if (it1 == this->_polynom.end() ||
            (it2 != other._polynom.end() && *it1 < *it2)) {
            monom = -(*it2);
            ++it2;
        }
        else {
            monom = *it1 - *it2;
            ++it1;
            ++it2;
        }

        if (monom.coeff() != 0)
            res._polynom.push_back(monom);
    }

    return res;
}

Polynom Polynom::operator+(const Monom& monom) const noexcept {
    Polynom res(*this);
    Node<Monom>* curr = res._polynom.head(), * prev = nullptr;

    while (curr != nullptr && curr->_value > monom) {
        prev = curr;
        curr = curr->_next;
    }

    if (curr != nullptr && curr->_value == monom)
        curr->_value += monom;
    else if (prev == nullptr)
        res._polynom.push_front(monom);
    else res._polynom.insert(prev, monom);

    return res;
}

Polynom Polynom::operator-(const Monom& monom) const noexcept {
    Polynom res(*this);
    Node<Monom>* curr = res._polynom.head(), * prev = nullptr;

    while (curr != nullptr && curr->_value > monom) {
        prev = curr;
        curr = curr->_next;
    }

    if (curr != nullptr && curr->_value == monom)
        curr->_value -= monom;
    else if (prev == nullptr)
        res._polynom.push_front(-monom);
    else res._polynom.insert(prev, -monom);

    return res;
}

Polynom Polynom::operator-() const noexcept {
    Polynom res(*this);

    for (auto it = res._polynom.begin(); it != res._polynom.end(); it++)
        *it *= -1.0;

    return res;
}

Polynom Polynom::operator*(const Polynom& other) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0

    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); it1++)
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); it2++)
            res += (*it1) * (*it2);

    return res;
}

Polynom Polynom::operator*(const Monom& monom) const noexcept {
    Polynom pol("m", monom), res = *this * pol;
    res._name = this->_name;
    return res;
}

Polynom Polynom::operator*(const double num) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0
    res._name = this->_name;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++)
        res._polynom.push_back(*it * num);

    return res;
}

Polynom Polynom::operator/(const Monom& monom) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0
    res._name = this->_name;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++)
        res._polynom.push_back(*it / monom);

    return res;
}

Polynom Polynom::operator/(const double num) const noexcept {
    Polynom res;
    res._polynom.pop_front();  // delete 0
    res._name = this->_name;

    for (auto it = _polynom.begin(); it != _polynom.end(); it++)
        res._polynom.push_back(*it / num);

    return res;
}

Polynom& Polynom::operator=(const Polynom& other) {
    this->_name = other._name;
    this->_polynom = other._polynom;
    return *this;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    std::string name_copy = this->_name;
    *this = *this + other;
    this->_name = name_copy;
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    std::string name_copy = this->_name;
    *this = *this - other;
    this->_name = name_copy;
    return *this;
}

Polynom& Polynom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}

Polynom& Polynom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) noexcept {
    std::string name_copy = this->_name;
    *this = *this * other;
    this->_name = name_copy;
    return *this;
}

Polynom& Polynom::operator*=(const Monom& monom) noexcept {
    *this = *this * monom;
    return *this;
}

Polynom& Polynom::operator*=(const double num) noexcept {
    *this = *this * num;
    return *this;
}

Polynom& Polynom::operator/=(const Monom& monom) noexcept {
    *this = *this / monom;
    return *this;
}

Polynom& Polynom::operator/=(const double num) noexcept {
    *this = *this / num;
    return *this;
}

std::string Polynom::to_string() const noexcept {
    std::string str = _name + " = ";

    for (auto it = _polynom.begin(); it != _polynom.end(); it++) {
        if ((*it).coeff() > 0 && it != _polynom.begin())
            str += "+";
        str += (*it).to_string();
    }

    return str;
}

double Polynom::calculate(std::initializer_list<int> values) const {
    double res = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); it++)
        res += (*it).calculate(values);

    return res;
}

void Polynom::parse(std::string polynom) {
    std::string monom;
    int i = 0;
    std::string operation = "";

    while (i < polynom.size()) {
        if (polynom[i] == ' ') {
            i++;
            continue;
        }
        else if (polynom[i] == '+') {
            operation = "";
            i++;
            continue;
        }
        else if (polynom[i] == '-') {
            operation = "-";
            i++;
            continue;
        }

        monom = read_monom(polynom, i);
        i += monom.size();
        *this += Monom(operation + monom);
    }
}

std::string Polynom::read_monom(std::string polynom, int pos) {
    std::string monom = "";

    for (int i = pos; i < polynom.size(); i++) {
        if (polynom[i] >= '0' && polynom[i] <= '9' || polynom[i] == ' ' ||
            polynom[i] == 'x' || polynom[i] == 'y' || polynom[i] == 'z' ||
            polynom[i] == '.' || polynom[i] == '^')
            monom += polynom[i];
        else if ((polynom[i] == '+' || polynom[i] == '-') && monom != "")
            break;
        else if (polynom[i] != '+' && polynom[i] != '-')
            throw std::logic_error("Unexpected symbol");
    }

    return monom;
}