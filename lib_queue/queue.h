#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

template <class T>
class Queue {
    T* _data;
    int _size;
    int _head = 0;
    int _count = 0;

public:
    Queue();
    Queue(int);
    Queue(const Queue&);
    ~Queue();

    void push(int value);
    void pop();
    inline T tail() const {
        return _data[(_head + _count) % _size - 1];
    }
    inline T head() const {
        return _data[_head];
    }
    inline bool is_empty() const noexcept {
        return _count == 0;
    }
    inline bool is_full() const noexcept {
        return _count == _size;
    }
    void clear() noexcept;
};

template <class T>
Queue<T>::Queue() {
    _size = 15;
    _data = new T[_size];
}

template <class T>
Queue<T>::Queue(int size) {
    if (size <= 0)
        throw std::invalid_argument("Size of stack must be > 0");
    _size = size;
    _data = new T[_size];
}

template <class T>
Queue<T>::Queue(const Queue& other) {
    _size = other._size;
    _head = other._head;
    _count = other._count;
    _data = new T[_size];
    for (int i = 0; i < _count; i++)
        _data[i] = other._data[i];
}

template <class T>
void Queue<T>::push(int value) {
    if (is_full())
        throw std::logic_error("The queue is full");
    int tail = (_head + _count) % _size;
    _data[tail] = value;
    _count++;
}

template <class T>
void Queue<T>::pop() {
    if (is_empty())
        throw std::logic_error("The queue is empty");
    _head = (_head + 1) % _size;
    _count--;
}

template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _count = 0;
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

#endif // !QUEUE_QUEUE_H
