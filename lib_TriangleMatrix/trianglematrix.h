#ifndef TRIANGLEMATRIX_TRIANGLEMATRIX_H
#define TRIANGLEMATRIX_TRIANGLEMATRIX_H

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix() {};
    TriangleMatrix(const int) {};
    TriangleMatrix(const TriangleMatrix&) {};

    TriangleMatrix<T> transpose();

    TriangleMatrix<T> operator +(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator -(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator *(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator * (const T&);
    friend std::ostream& operator << (std::ostream& out, const TriangleMatrix<T>& matrix) {
        return out;
    }
    friend std::istream& operator >>(std::istream& in, const TriangleMatrix<T>& matrix) {
        return in;
    }

    TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);
    MathVector<T>& operator [] (const int&);
};

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::transpose() {
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator +(const TriangleMatrix<T>& second) {
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator -(const TriangleMatrix<T>& second) {
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator *(const TriangleMatrix<T>& second) {
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator *(const T& number) {
    return TriangleMatrix<T>();
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator = (const TriangleMatrix<T>& other) {
    return TriangleMatrix();
}

template <class T>
MathVector<T>& TriangleMatrix<T>::operator [] (const int& index) {
    MathVector<T> vector;
    return vector;
}


#endif // !TRIANGLEMATRIX_TRIANGLEMATRIX_H
