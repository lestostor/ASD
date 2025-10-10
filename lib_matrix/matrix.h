#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "../lib_MathVector/mathvector.h"
#include <iostream>

template <class T> class Matrix;

template <class T>
class Matrix : public MathVector<MathVector<T>> {
protected:
    int _m;  // lines
    int _n;  // columns
public:
    Matrix();
    Matrix(const int, const int);
    Matrix(const MathVector<MathVector<T>>&);
    Matrix(const Matrix&);

    void transpose();
    Matrix<T> transposed() const;

    inline int get_lines() const {
        return _m;
    }

    inline int get_columns() const {
        return _n;
    }

    Matrix<T> operator +(const Matrix<T>&) const;
    Matrix<T> operator -(const Matrix<T>&) const;
    Matrix<T> operator *(const Matrix<T>&) const;
    MathVector<T> operator*(const MathVector<T>&) const;
    Matrix<T> operator *(const T&) const;
    friend std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix._m; i++) {
            for (int j = 0; j < matrix._n; j++)
                out << matrix[i][j] << " ";
            out << std::endl;
        }
        return out;
    }
    friend std::istream& operator >> (std::istream& in, Matrix<T>& matrix) {
        for (int i = 0; i < matrix._m; i++)
            for (int j = 0; j < matrix._n; j++)
                in >> matrix[i][j];
        return in;
    }

    Matrix<T>& operator = (const Matrix<T>&);
    bool operator==(const Matrix<T>&);
    bool operator!=(const Matrix<T>&);
};

template <class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>() , _m(0), _n(0) {}

template <class T>
Matrix<T>::Matrix(const int m, const int n) : MathVector<MathVector<T>>(m), _m(m), _n(n) {
    for (int i = 0; i < m; i++)
        (*this)[i] = MathVector<T>(n);
}

template <class T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& other) : MathVector<MathVector<T>>(other.size()) {
    this->_m = other.size();
    this->_n = other[0].size();
    for (int i = 0; i < _m; i++) {
        (*this)[i] = MathVector<T>(other[i]);
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other_matrix) : MathVector<MathVector<T>>(other_matrix._m) {
    this->_m = other_matrix._m;
    this->_n = other_matrix._n;
    for (int i = 0; i < _m; i++) {
        (*this)[i] = MathVector<T>(other_matrix[i]);
    }
}

template <class T>
void Matrix<T>::transpose() {
    Matrix<T> result(_n, _m);
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++)
            result[i][j] = (*this)[j][i];
    }
    *this = result;
}

template <class T>
Matrix<T> Matrix<T>::transposed() const{
    Matrix<T> result(_n, _m);
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++)
            result[i][j] = (*this)[j][i];
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& second) const {
    if (this->_m != second._m || this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    //Matrix<T> result(_m, _n);
    //for (int i = 0; i < _m; i++)
    //    result[i] = (*this)[i] + second[i];

    return this->MathVector<MathVector<T>>::operator+(second);
}

template <class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& second) const {
    if (this->_m != second._m || this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    Matrix<T> result(_m, _n);
    for (int i = 0; i < _m; i++)
        result[i] = (*this)[i] - second[i];

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& second) const {
    if (_n != second._m)
        throw std::logic_error("Wrong sizes");
    Matrix<T> result(_m, second._n);
    Matrix<T> second_t = second.transposed();
    for (int i = 0; i < _m; i++)
        for (int j = 0; j < second_t._m; j++)
            result[i][j] = (*this)[i] * second_t[j];

    return result;
}

template <class T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vector) const {
    if (vector.size() != _n)
        throw std::logic_error("Wrong sizes");
    MathVector<T> result(_m);
    for (int i = 0; i < _m; i++) {
        result[i] = (*this)[i] * vector;
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator *(const T& value) const {
    Matrix<T> result(_m, _n);
    for (int i = 0; i < _m; i++)
        result[i] = (*this)[i] * value;

    return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other_matrix) {
    if (&other_matrix == this)
        return *this;

    this->_m = other_matrix._m;
    this->_n = other_matrix._n;

    (*this).MathVector<MathVector<T>>::operator=(other_matrix);

    return *this;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other_matrix) {
    if (&other_matrix == this)
        return true;
    if (this->_m != other_matrix._m || this->_n != other_matrix._n)
        return false;
    for (int i = 0; i < _m; i++) {
        if ((*this)[i] != other_matrix[i])
            return false;
    }
    return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T>& other_matrix) {
    return !((*this) == other_matrix);
}

#endif // !MATRIX_MATRIX_H
