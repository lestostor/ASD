#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include "../lib_MathVector/mathvector.h"
#include <iostream>

template <class T> class Matrix;

template <class T>
class Matrix : public MathVector<MathVector<T>> {
    int _m;  // lines
    int _n;  // columns
public:
    Matrix() {};
    Matrix(const int, const int) {};
    Matrix(const Matrix&) {};

    friend Matrix<T> operator +(const Matrix<T>&, const Matrix<T>&);
    friend Matrix<T> operator -(const Matrix<T>&, const Matrix<T>&);
    friend Matrix<T> operator *(const Matrix<T>&, const Matrix<T>&);
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
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other) {
    return Matrix();
}

template <class T>
MathVector<T>& Matrix<T>::operator [] (const int& index) {
    MathVector<T> vector;
    return vector;
}

template <class T>
Matrix<T> operator +(const Matrix<T>& first, const Matrix<T>& second) {
    if (first._m != second._m || first._n != second._n)
        throw std::logic_error("Sizes of matrixes must be equal");
    return Matrix<T>();
}

template <class T>
Matrix<T> operator -(const Matrix<T>& first, const Matrix<T>& second) {
    if (first._m != second._m || first._n != second._n)
        throw std::logic_error("Sizes of matrixes must be equal");
    return Matrix<T>();
}

template <class T>
Matrix<T> operator *(const Matrix<T>& first, const Matrix<T>& second) {
    if (first._n != second._m)
        throw std::logic_error("Columns of first matrix and lines of second matrix must be equal");
    return Matrix<T>();
}

#endif // !MATRIX_MATRIX_H
