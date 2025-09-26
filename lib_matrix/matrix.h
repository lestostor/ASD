#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "../lib_MathVector/mathvector.h"
#include <iostream>

template <class T> class Matrix;

template <class T>
class Matrix : public MathVector<MathVector<T>> {
public:
    int _m;  // lines
    int _n;  // columns
    Matrix();
    Matrix(const int, const int);
    Matrix(const Matrix&);

    void transpose();

    Matrix<T> operator +(const Matrix<T>&);
    Matrix<T> operator -(const Matrix<T>&);
    Matrix<T> operator *(const Matrix<T>&);
    Matrix<T> operator *(const T&);
    friend std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix._size; i++) {
            for (int j = 0; j < matrix._vec[0].size(); j++)
                out << matrix._vec[i][j] << " ";
            out << std::endl;
        }
        return out;
    }
    friend std::istream& operator >> (std::istream& in, Matrix<T>& matrix) {
        for (int i = 0; i < matrix._size; i++)
            for (int j = 0; j < matrix._vec[i].size(); j++)
                in >> matrix._vec[i][j];
        return in;
    }

    Matrix<T>& operator = (const Matrix<T>&);
    MathVector<T>& operator [] (const int&);
};

template <class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>() , _m(0), _n(0) {}

template <class T>
Matrix<T>::Matrix(const int m, const int n) : MathVector<MathVector<T>>(m), _m(m), _n(n) {
    for (int i = 0; i < m; i++)
        _vec[i] = MathVector<T>(n);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other_matrix) : MathVector<MathVector<T>>(other_matrix._size) {
    this->_m = other_matrix._m;
    this->_n = other_matrix._n;
    for (int i = 0; i < _m; i++) {
        this->_vec[i] = MathVector<T>(other_matrix._vec[i]);
        this->_status[i] = Status::Busy;
    }
}

template <class T>
void Matrix<T>::transpose() {
    Matrix<T> result(_n, _m);
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _m; j++)
            result[i][j] = this->_vec[j][i];
    }
    *this = result;
}

template <class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& second) {
    if (this->_m != second._m || this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    Matrix<T> result(_m, _n);
    for (int i = 0; i < _m; i++)
        result[i] = this->_vec[i] + second._vec[i];

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& second) {
    if (this->_m != second._m || this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    Matrix<T> result(_m, _n);
    for (int i = 0; i < _m; i++)
        result[i] = this->_vec[i] - second._vec[i];

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& second) {
    return Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator *(const T& value) {
    Matrix<T> result(_m, _n);
    for (int i = 0; i < _m; i++)
        result[i] = (*this)[i] * value;

    return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other_matrix) {
    if (&other_matrix == this)
        return *this;

    this->_size = other_matrix._size;
    this->_capacity = other_matrix._capacity;
    this->_vec = new MathVector<T>[this->_size];
    this->_status = new Status[this->_size];
    this->_start_index = other_matrix._start_index;
    this->_m = other_matrix._m;
    this->_n = other_matrix._n;

    for (int i = 0; i < _m; i++) {
        this->_vec[i] = other_matrix._vec[i];
        this->_status[i] = Status::Busy;
    }

    return *this;
}

template <class T>
MathVector<T>& Matrix<T>::operator [] (const int& index) {
    return _vec[index];
}

#endif // !MATRIX_MATRIX_H
