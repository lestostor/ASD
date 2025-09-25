#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "../lib_MathVector/mathvector.h"
#include <iostream>

template <class T> class Matrix;

template <class T>
class Matrix : public MathVector<MathVector<T>> {
public:
    Matrix();
    Matrix(const int, const int);
    Matrix(const Matrix&);

    Matrix<T> transpose();

    Matrix<T> operator +(const Matrix<T>&);
    Matrix<T> operator -(const Matrix<T>&);
    Matrix<T> operator *(const Matrix<T>&);
    Matrix<T> operator *(const T&);
    friend std::ostream& operator << (std::ostream& out, const Matrix<T>& matrix) {
        return out;
    }
    friend std::istream& operator >>(std::istream& in, const Matrix<T>& matrix) {
        return in;
    }

    Matrix<T>& operator = (const Matrix<T>&);
    MathVector<T>& operator [] (const int&);
};

template <class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>() {}

template <class T>
Matrix<T>::Matrix(const int m, const int n) : MathVector<MathVector<T>>(m) {
    for (int i = 0; i < m; i++)
        _vec[i] = MathVector<T>(n);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other_matrix) : MathVector<MathVector<T>>(other_matrix._size) {
    for (int i = 0; i < other_matrix._size; i++) {
        if (i < other_matrix._size) {
            this->_vec[i] = MathVector<T>(other_matrix._vec[i]);
            this->_status[i] = Status::Busy;
        }
        else
            this->_status[i] = Status::Busy;
    }
}

template <class T>
Matrix<T> Matrix<T>::transpose() {
    return Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& second) {
    return Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& second) {
    return Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& second) {
    return Matrix<T>();
}

template <class T>
Matrix<T> Matrix<T>::operator *(const T& second) {
    return Matrix<T>();
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other) {
    return Matrix();
}

template <class T>
MathVector<T>& Matrix<T>::operator [] (const int& index) {
    MathVector<T> vector;
    return vector;
}

#endif // !MATRIX_MATRIX_H
