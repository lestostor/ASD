#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "../lib_MathVector/mathvector.h"
#include <iostream>

template <class T>
class Matrix : public MathVector<MathVector<T>> {
public:
    Matrix() {};
    Matrix(const int, const int) {};
    Matrix(const Matrix&) {};

    friend Matrix<T> operator +(const Matrix<T>&, const Matrix<T>&) {};
    friend Matrix<T> operator -(const Matrix<T>&, const Matrix<T>&) {};
    friend Matrix<T> operator *(const Matrix<T>&, const Matrix<T>&) {};
    friend Matrix<T> operator /(const Matrix<T>&, const Matrix<T>&) {};

    Matrix<T>& operator = (const Matrix<T>&);
};

template <class T>
Matrix<T>& Matrix<T>::operator = (const TVector<T>& other_vector) {
    return Matrix();
}

#endif // !MATRIX_MATRIX_H
