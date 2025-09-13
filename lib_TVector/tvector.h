#ifndef TVECTOR_TVECTOR_H
#define TVECTOR_TVECTOR_H

#include <iterator>
#include <stdexcept>
#include <utility>
#include <random>
#include <iostream>

//  Copyright 2025 Shcherbakova Olesya

#define STEP_OF_CAPACITY 15

enum Status { Busy, Deleted, Empty };
template <class T> class TVector;

template <class T>
class TVector {
    T* _vec;
    Status* _status;
    size_t _size;
    size_t _capacity;

public:
    //  constructors
    TVector();
    explicit TVector(int);  //  empty vector
    TVector(std::initializer_list<T>);  //  convert list to vector
    TVector(const TVector<T>&);  //  copy
    ~TVector();  //  destructor

    void clear();

    //  add element
    void push_back(const T&);
    void push_front(const T&);
    void insert(const T*, const T&);

    //  friends
    template <class T>
    friend int find(const TVector<T>&, const T&);
    template <class T>
    friend int find_last(const TVector<T>&, const T&);
    template <class T>
    friend int* find_all(const TVector<T>&, const T&);

    template <class T>
    friend void shuffle(TVector<T>&);

    template <class T>
    friend void sort_vector(TVector<T>&);

    // delete element
    void pop_back();
    void pop_front();
    void erase(const T*);

    //  emplace
    void emplace(const T&, const T&);  //  by value
    void emplace(const T*, const T&);  //  by index

    TVector<T> assign(const TVector&);

    void reserve(size_t);

    //  operators
    TVector<T>& operator = (const TVector<T>&);
    bool operator == (const TVector<T>&);
    bool operator != (const TVector<T>&);
    T& operator[](const int) const;
    T& operator[](const int);
    template <class T>
    friend std::ostream& operator << (std::ostream&, const TVector<T>&);

    void shrink_to_fit();
    void resize(size_t, const T& value = T());

    //  getters
    inline size_t size() const noexcept {
        return this->_size;
    }

    inline size_t capacity() const noexcept {
        return this->_capacity;
    }

    inline T* data() const noexcept {
        return _vec;
    }

    inline T* begin() const noexcept {
        return _vec;
    }

    inline T* end() const noexcept {
        return _vec + _size;
    }

    inline T& front() const noexcept {
        return *(begin());
    }

    inline T& back() const noexcept {
        return *(end() - 1);
    }

    inline bool is_empty() const noexcept {
        for (int i = 0; i < _size; i++) {
            if (_status[i] == Status::Busy) return false;
        }
        return true;
    }

    T& at(const int) const;

private:
    T* reset_memory(size_t);
    T* reset_memory_for_deleted(size_t);
    int count_deleted() const;
    int count_right_pos(const T*) const;
    inline bool is_full() const noexcept {
        return !is_empty();
    }
    template <class T>
    friend void Hoara_sort_rec(TVector<T>&, int, int);
};

template <class T>
TVector<T>::TVector() {
    _size = 0;
    _capacity = STEP_OF_CAPACITY;
    _vec = new T[_capacity];
    _status = new Status[_capacity];
}

template <class T>
TVector<T>::TVector(int size) {
    _size = size;
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _vec = new T[_capacity];
    _status = new Status[_capacity];

    for (int i = 0; i < _capacity; i++)
        _status[i] = Status::Empty;
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> mass) {
    _size = mass.size();
    _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _vec = new T[_capacity];
    _status = new Status[_capacity];

    auto it = mass.begin();
    for (int i = 0; i < _capacity; i++, it++) {
        if (i < _size) {
            _vec[i] = *it;
            _status[i] = Status::Busy;
        }
        else _status[i] = Status::Empty;
    }
}

template <class T>
TVector<T>::TVector(const TVector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _vec = new T[_capacity];
    _status = new Status[_capacity];

    for (int i = 0; i < _capacity; i++) {
        if (i < other._size) {
            _vec[i] = other._vec[i];
            _status[i] = Status::Busy;
        }
        else _status[i] = Status::Empty;
    }
}

template <class T>
void TVector<T>::clear() {
    for (int i = 0; i < _size; i++)
        _status[i] = Status::Empty;
}

template <class T>
void TVector<T>::push_back(const T& value) {
    _vec = reset_memory(_size + 1);
    _size++;
    if (_size == 1) {
        _capacity = STEP_OF_CAPACITY;
        _vec = new T[1];
        _status = new Status[1];
    }
    _vec[_size - 1] = value;
    _status[_size - 1] = Status::Busy;
}

template <class T>
void TVector<T>::push_front(const T& value) {
    _vec = reset_memory(_size + 1);
    _size++;
    if (_size == 1) {
        _capacity = STEP_OF_CAPACITY;
        _vec = new T[1];
        _status = new Status[1];
    }
    for (int i = _size - 1; i > 0; i--) {
        _vec[i] = _vec[i - 1];
        _status[i] = _status[i - 1];
    }
    _vec[0] = value;
    _status[0] = Status::Busy;
}

template <class T>
void TVector<T>::insert(const T* pos, const T& value) {
    int right_pos = count_right_pos(pos);
    if (_size + 1 >= _capacity)
        _vec = reset_memory(_size + 1);
    int i = _size + count_deleted();
    for (i; i > right_pos; i--) {
        _vec[i] = _vec[i - 1];
        _status[i] = Status::Busy;
    }
    _size++;
    if (_size == 1) {
        _capacity = STEP_OF_CAPACITY;
        _vec = new T[1];
        _status = new Status[1];
    }
    _vec[i] = value;
    _status[i] = Status::Busy;
}

template <class T>
void TVector<T>::pop_back() {
    _status[_size - 1] = Status::Empty;
    _size--;
    if (count_deleted() >= _size * 0.1)
        _vec = reset_memory_for_deleted(_size);
}

template <class T>
void TVector<T>::pop_front() {
    int first_not_deleted = 0;
    while (_status[first_not_deleted] == Status::Deleted) first_not_deleted++;
    _status[first_not_deleted] = Status::Deleted;
    _size--;
    if (count_deleted() >= _size * 0.1)
        _vec = reset_memory_for_deleted(_size);
}

template <class T>
void TVector<T>::erase(const T* pos) {
    int right_pos = count_right_pos(pos);
    _status[right_pos] = Status::Deleted;
    _size--;
    if (count_deleted() >= _size * 0.1)
        _vec = reset_memory_for_deleted(_size);
}

template <class T>
void TVector<T>::emplace(const T& value, const T& new_value) {
    for (int i = 0; i < _size; i++) {
        if (_vec[i] == value && _status[i] == Status::Busy)
            _vec[i] = new_value;
    }
}

template <class T>
void TVector<T>::emplace(const T* pos, const T& new_value) {
    int right_pos = count_right_pos(pos);
    if (right_pos >= _size)
        throw std::logic_error("Index is out of range\n");
    _vec[right_pos] = new_value;
}

template <class T>
TVector<T> TVector<T>::assign(const TVector& other_vector) {
    if (&other_vector == NULL)
        throw std::logic_error("NULL object");
    else if (&other_vector == this)
        return *this;

    this->_size = other_vector._size;
    this->_capacity = other_vector._capacity;
    this->_vec = new T[this->_capacity];
    this->_status = new Status[this->_capacity];

    for (int i = 0; i < this->_capacity; i++) {
        if (i < other_vector._size) {
            this->_vec[i] = other_vector._vec[i];
            this->_status[i] = other_vector._status[i];
        }
        else this->_status[i] = Status::Empty;
    }

    return *this;
}

template <class T>
TVector<T>& TVector<T>::operator = (const TVector<T>& other_vector) {
    if (&other_vector != this) (*this).assign(other_vector);
    return *this;
}

template <class T>
bool TVector<T>::operator == (const TVector<T>& other_vector) {
    if (this->_size != other_vector._size) return false;
    for (int i = 0, j = 0; i + j < other_vector._size; i++) {
        if (this->_vec[i + j] != other_vector._vec[i] &&
            this->_status[i] == Status::Busy &&
            other_vector._status[i] == Status::Busy &&
            this->_vec[i] != other_vector._vec[i + j] &&
            this->_status[i] == Status::Busy &&
            other_vector._status[i] == Status::Busy) return false;

        else if (this->_status[i] != Status::Busy ||
            other_vector._status[i] != Status::Busy) j++;  // for deleted
    }
    return true;
}

template <class T>
bool TVector<T>::operator != (const TVector<T>& other_vector) {
    return !((*this) == other_vector);
}

template <class T>
T& TVector<T>::operator[](const int pos) const {
    int correct = 0, i;
    for (i = 0; i < _size; i++) {
        if (_status[i] != Status::Deleted) correct++;
        if (correct == pos + 1) break;
    }

    return _vec[i];
}

template <class T>
T& TVector<T>::operator[](const int pos) {
    int correct = 0, i;
    for (i = 0; i < _size; i++) {
        if (_status[i] != Status::Deleted) correct++;
        if (correct == pos + 1) break;
    }

    return _vec[i];
}

template <class T>
std::ostream& operator << (std::ostream& out, const TVector<T>& vector) {
    for (int i = 0; i < vector._size; i++) {
        if (vector._status[i] == Status::Busy) {
            out << vector._vec[i];
            if (i != vector._size - 1) out << ' ';
        }
    }
    out << std::endl;
    return out;
}

template <class T>
T& TVector<T>::at(const int pos) const {
    int correct = 0, i;
    for (i = 0; i < _size; i++) {
        if (_status[i] != Status::Deleted) correct++;
        if (correct == pos + 1) break;
    }

    if (i >= _size || i < 0)
        throw std::out_of_range("Index is out of range\n");
    return _vec[i];
}

template <class T>
void TVector<T>::reserve(size_t new_cap) {
    if (new_cap <= _capacity) {
        return;
    }
    T* new_vec = new T[new_cap];
    Status* new_status = new Status[new_cap];
    for (int i = 0, j = 0; i < _capacity; i++) {
        if (_status[i] == Status::Busy) {
            new_vec[j] = _vec[i];
            new_status[j] = Status::Busy;
            j++;
        }
    }
    for (int i = _size; i < new_cap; i++) {
        new_status[i] = Status::Empty;
    }
    delete[] _vec;
    delete[] _status;
    _vec = new_vec;
    _status = new_status;
    _capacity = new_cap;
}

template <class T>
T* TVector<T>::reset_memory(size_t new_size) {
    size_t new_capacity = (new_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    reserve(new_capacity);
    T* new_vec = new T[new_capacity];

    for (int i = 0, j = 0; j < _size; i++)
        if (_status[i] == Status::Busy) {
            new_vec[j] = _vec[i];
            j++;
        }
    delete[] _status;
    _status = new Status[new_capacity];
    for (int i = 0; i < new_capacity; i++) {
        if (i < _size) _status[i] = Status::Busy;
        else _status[i] = Status::Empty;
    }
    _capacity = new_capacity;
    delete[] _vec;

    return new_vec;
}

template <class T>
T* TVector<T>::reset_memory_for_deleted(size_t new_size) {
    T* new_vec = new T[_capacity];
    for (int i = 0, j = 0; j < _size && i < _capacity; i++) {
        if (_status[i] == Status::Busy) {
            new_vec[j] = _vec[i];
            _status[j] = Status::Busy;
            j++;
        }
    }
    delete[] _vec;
    _size = new_size;
    return new_vec;
}

template <class T>
void TVector<T>::shrink_to_fit() {
    _capacity = _size;
    if (_size == 0) {
        if (_vec != nullptr) {
            delete[] _vec;
            _vec = nullptr;
        }
        if (_status != nullptr) {
            delete[] _status;
            _status = nullptr;
        }
        return;
    }
    T* data = new T[_capacity];
    for (int i = 0, j = 0; i < _capacity; i++) {
        if (_status[i] == Status::Busy) {
            data[j] = _vec[i];
            j++;
        }
    }
    delete[] _vec;
    delete[] _status;
    _status = new Status[_capacity];
    _vec = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _vec[i] = data[i];
        _status[i] = Status::Busy;
    }
    delete[] data;
}

template <class T>
void TVector<T>::resize(size_t count, const T& value) {
    if (_size == count) {
        return;
    }
    else if (count > _size) {
        _vec = reset_memory(count);
        for (int i = _size - 1; i < count; i++) {
            _vec[i] = value;
            _status[i] = Status::Busy;
        }
    }
    else {
        T* data = this->data();
        _vec = new T[_capacity];
        for (int i = 0, j = 0; j < count; i++) {
            if (_status[i] == Status::Busy) {
                _vec[j] = data[i];
                j++;
            }
        }
    }
    _size = count;
}

template <class T>
int TVector<T>::count_deleted() const {
    int count = 0;
    for (int i = 0; i < _size; i++) {
        if (_status[i] == Status::Deleted ||
            _status[i] == Status::Empty)
            count++;
    }

    return count;
}

template <class T>
int TVector<T>::count_right_pos(const T* pos) const {
    T* correct = this->begin();
    int i;
    for (i = 0; i < _size; i++) {
        if (_status[i] != Status::Deleted) correct++;
        if (correct == pos + 1) break;
    }
    return i;
}

template <class T>
int find(const TVector<T>& vec, const T& value) {
    int deleted = 0;
    for (int i = 0; i < vec._size; i++) {
        if (vec._status[i] != Status::Busy) deleted++;
        if (vec._vec[i] == value && vec._status[i] == Status::Busy)
            return i - deleted;
    }
    return -1;
}

template <class T>
int find_last(const TVector<T>& vec, const T& value) {
    int deleted = 0;
    for (int i = vec._size - 1; i >= 0; i--) {
        if (vec._status[i] != Status::Busy) deleted++;
        if (vec._vec[i] == value && vec._status[i] == Status::Busy)
            return i - vec.count_deleted() + deleted;
    }
    return -1;
}

template <class T>
int* find_all(const TVector<T>& vec, const T& value) {
    int* result = nullptr, size = 0, deleted = 0;
    for (int i = 0; i < vec._size; i++) {
        if (vec._status[i] != Status::Busy) deleted++;
        if (vec._vec[i] == value && vec._status[i] == Status::Busy)
            size++;
    }
    size -= deleted;
    if (size == 0) return result;

    result = new int[size];
    for (int i = 0, j = 0; j < size; i++) {
        if (vec._status[i] != Status::Busy) deleted++;
        if (vec._vec[i] == value && vec._status[i] == Status::Busy) {
            result[j] = i - deleted;
            j++;
        }
    }

    return result;
}

template <class T>
void shuffle(TVector<T>& vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, vec._size - 1);
    for (int i = 0; i < vec._size; i++) {
        int rand_pos = 0;
        do {
            rand_pos = distrib(gen);
        } while (vec._status[rand_pos] != Status::Busy);
        std::swap(vec._vec[i], vec._vec[rand_pos]);
        std::swap(vec._status[i], vec._status[rand_pos]);
    }
}

template <class T>
void Hoara_sort_rec(TVector<T>& vec, int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int base_pos = (left + right) * 0.5;
        T base_value = vec._vec[base_pos];
        while (l <= r) {
            while (vec._vec[l] < base_value) l++;
            while (vec._vec[r] > base_value) r--;
            if (l < r) {
                std::swap(vec._vec[l], vec._vec[r]);
                std::swap(vec._status[l], vec._status[r]);
                l++;
                r--;
            }
            else break;
        }
        Hoara_sort_rec(vec, left, r);
        Hoara_sort_rec(vec, r + 1, right);
    }
}

template <class T>
void sort_vector(TVector<T>& vec) {
    Hoara_sort_rec(vec, 0, static_cast<int>(vec._size) - 1);
}

template <class T>
TVector<T>::~TVector() {
    if (_vec != nullptr) delete[] _vec;
    if (_status != nullptr) delete[] _status;
}

#endif // !TVECTOR_TVECTOR_H
