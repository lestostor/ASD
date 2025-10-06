#ifndef TRIANGLEMATRIX_TRIANGLEMATRIX_H
#define TRIANGLEMATRIX_TRIANGLEMATRIX_H

#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public MathVector<MathVector<T>> {
    int _n;
public:
    TriangleMatrix();
    TriangleMatrix(const int);
    TriangleMatrix(const TriangleMatrix&);

    inline int size() const {
        return _n;
    }

    TriangleMatrix<T> operator +(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator -(const TriangleMatrix<T>&);
    TriangleMatrix<T> operator *(const TriangleMatrix<T>&);
    MathVector<T> operator * (const MathVector<T>&);
    TriangleMatrix<T> operator * (const T&);
    friend std::ostream& operator << (std::ostream& out, const TriangleMatrix<T>& matrix) {
        for (int i = 0; i < matrix._n; i++) {
            for (int j = 0; j < matrix._n; j++)
                 out << matrix[i][j] << " ";
            out << std::endl;
        }
        return out;
    }
    friend std::istream& operator >>(std::istream& in, TriangleMatrix<T>& matrix) {
        for (int i = 0; i < matrix._n; i++)
            for (int j = i; j < matrix._n; j++)
                in >> matrix[i][j];
        return in;
    }

    TriangleMatrix<T>& operator = (const TriangleMatrix<T>&);
    bool operator==(const TriangleMatrix<T>&);
    bool operator!=(const TriangleMatrix<T>&);
};

template <class T>
TriangleMatrix<T>::TriangleMatrix() : MathVector<MathVector<T>> (), _n(0) {}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const int size) : MathVector<MathVector<T>>(size), _n(size) {
    for (int i = 0; i < size; i++)
        (*this)[i] = MathVector<T>(size - i, i);
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T>& other_matrix) : MathVector<MathVector<T>>(other_matrix._n), _n(other_matrix._n) {
    for (int i = 0; i < _n; i++)
        (*this)[i] = MathVector<T>(other_matrix[i]);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator +(const TriangleMatrix<T>& second) {
    if (this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    TriangleMatrix<T> result(this->_n);
    for (int i = 0; i < _n; i++)
        result[i] = (*this)[i] + second[i];

    return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator -(const TriangleMatrix<T>& second) {
    if (this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");

    TriangleMatrix<T> result(this->_n);
    for (int i = 0; i < _n; i++)
        result[i] = (*this)[i] - second[i];

    return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator *(const TriangleMatrix<T>& second) {
    if (this->_n != second._n)
        throw std::logic_error("Matrixes have different sizes");
    
    TriangleMatrix<T> result(_n);
    for (int i = 0; i < _n; i++) {
        result[i][i] = (*this)[i][i] * second[i][i];

        for (int j = i + 1; j < _n; j++) {
            T sum = T();
            for (int k = i; k <= j; k++)
                sum += (*this)[i][j] * second[i][j];
            result[i][j] = sum;
        }
    }

    return result;
}

template <class T>
MathVector<T> TriangleMatrix<T>::operator * (const MathVector<T>& vector) {
    if (vector.size() != _n)
        throw std::logic_error("Wrong sizes");
    MathVector<T> result(_n);
    for (int i = 0; i < _n; i++) {
        result[i] = (*this)[i] * vector;
    }

    return result;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator *(const T& value) {
    TriangleMatrix<T> result(_n);
    for (int i = 0; i < _n; i++)
        result[i] = (*this)[i] * value;

    return result;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator = (const TriangleMatrix<T>& other_matrix) {
    if (&other_matrix == this)
        return *this;

    this->_n = other_matrix._n;

    for (int i = 0; i < _n; i++)
        (*this)[i].MathVector<T>::operator=(other_matrix[i]);

    return *this;
}

template <class T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other_matrix) {
    if (&other_matrix == this)
        return true;
    if (this->_n != other_matrix._n)
        return false;
    for (int i = 0; i < _n; i++) {
        if ((*this)[i] != other_matrix[i])
            return false;
    }
    return true;
}

template <class T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other_matrix) {
    return !((*this) == other_matrix);
}

#endif // !TRIANGLEMATRIX_TRIANGLEMATRIX_H
