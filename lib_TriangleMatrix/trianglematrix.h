#ifndef TRIANGLEMATRIX_TRIANGLEMATRIX_H
#define TRIANGLEMATRIX_TRIANGLEMATRIX_H

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix() {};
    TriangleMatrix(const int) {};
    TriangleMatrix(const TriangleMatrix&) {};

    friend TriangleMatrix<T> operator +(const TriangleMatrix<T>&, const TriangleMatrix<T>&);
    friend TriangleMatrix<T> operator -(const TriangleMatrix<T>&, const TriangleMatrix<T>&);
    friend TriangleMatrix<T> operator *(const TriangleMatrix<T>&, const TriangleMatrix<T>&);

    TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);
    MathVector<T>& operator [] (const int&);
};

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
