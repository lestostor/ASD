#ifndef TRIANGLEMATRIX_TRIANGLEMATRIX_H
#define TRIANGLEMATRIX_TRIANGLEMATRIX_H

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public MathVector<MathVector<T>> {
public:
    TriangleMatrix();
    TriangleMatrix(const int);
    TriangleMatrix(const TriangleMatrix&);

    TriangleMatrix<T> transpose();

    TriangleMatrix<T> operator +(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator -(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator *(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator * (const T&);
    friend std::ostream& operator << (std::ostream& out, const TriangleMatrix<T>& matrix) {
        for (int i = 0; i < matrix._size; i++) {
            for (int j = 0; j < matrix._size; j++)
                 out << matrix._vec[i][j] << " ";
            out << std::endl;
        }
        return out;
    }
    friend std::istream& operator >>(std::istream& in, TriangleMatrix<T>& matrix) {
        for (int i = 0; i < matrix._size; i++)
            for (int j = i; j < matrix._size; j++)
                in >> matrix._vec[i][j];
        return in;
    }

    TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);
    MathVector<T>& operator [] (const int&);
    MathVector<T>& operator [] (const int&) const;
};

template <class T>
TriangleMatrix<T>::TriangleMatrix() : MathVector<MathVector<T>> () {}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const int size) : MathVector<MathVector<T>>(size) {
    for (int i = 0; i < size; i++)
        this->_vec[i] = MathVector<T>(size - i, i);
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other_matrix) : MathVector<MathVector<T>>(other_matrix.size()) {
    for (int i = 0; i < _size; i++) {
        this->_vec[i] = MathVector<T>(other_matrix._vec[i]);
        this->_status[i] = Status::Busy;
    }
}

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
TriangleMatrix<T>& TriangleMatrix<T>::operator = (const TriangleMatrix<T>& other_matrix) {
    if (&other_matrix == this)
        return *this;

    this->_size = other_matrix._size;
    this->_capacity = other_matrix._capacity;
    this->_vec = new MathVector<T>[this->_size];
    this->_status = new Status[this->_size];
    this->_start_index = other_matrix._start_index;

    for (int i = 0; i < _size; i++) {
        this->_vec[i] = other_matrix._vec[i];
        this->_status[i] = Status::Busy;
    }

    return *this;
}

template <class T>
MathVector<T>& TriangleMatrix<T>::operator [] (const int& index) {
    return _vec[index];
}

template <class T>
MathVector<T>& TriangleMatrix<T>::operator [] (const int& index) const {
    return _vec[index];
}

#endif // !TRIANGLEMATRIX_TRIANGLEMATRIX_H
