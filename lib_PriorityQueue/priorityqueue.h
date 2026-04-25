#ifndef PRIORITYQUEUE_PRIORITYQUEUE_H
#define PRIORITYQUEUE_PRIORITYQUEUE_H

#include "../lib_heap/heap.h"
#include <iostream>

template <class TValue>
class PriorityPair {
    int _priority;
    TValue _value;
    int _order;

public:
    PriorityPair(const int priority = 0, const TValue& value = TValue(), const int order = 1);

    inline int get_priority() { return _priority; }
    inline TValue get_value() { return _value; }

    bool operator<(const PriorityPair&) const noexcept;
    bool operator>(const PriorityPair&) const noexcept;
    bool operator==(const PriorityPair&) const noexcept;

    friend std::ostream& operator<<(std::ostream& out, const PriorityPair<TValue>& pair) {
        out << pair._priority << ": " << pair._value;

        return out;
    }
};

template <class TValue>
PriorityPair<TValue>::PriorityPair(const int priority, const TValue& value, const int order) : _priority(priority), _value(value), _order(order) {}

template <class TValue>
bool PriorityPair<TValue>:: operator<(const PriorityPair& pair) const noexcept {
    if (this->_priority != pair._priority)
        return this->_priority < pair._priority;
    return this->_order < pair._order;
}

template <class TValue>
bool PriorityPair<TValue>:: operator>(const PriorityPair& pair) const noexcept {
    if (this->_priority != pair._priority)
        return this->_priority > pair._priority;
    return this->_order > pair._order;
}

template <class TValue>
bool PriorityPair<TValue>:: operator==(const PriorityPair& pair) const noexcept {
    return this->_priority == pair._priority && this->_order == pair._order;
}

template <class TValue>
class PriotityQueue {
    Heap<PriorityPair<TValue>> _data;

public:
    PriotityQueue();

    void push(const int, const TValue&, const int);
    PriorityPair<TValue> pop();
    bool is_empty() const noexcept { return _data.is_empty(); }
};

template <class TValue>
PriotityQueue<TValue>::PriotityQueue() : _data() {}

template <class TValue>
void PriotityQueue<TValue>::push(const int priority, const TValue& value, const int order) {
    PriorityPair<TValue> pair(priority, value, order);
    _data.push(pair);
}

template <class TValue>
PriorityPair<TValue> PriotityQueue<TValue>::pop() {
    return _data.pop();
}

#endif // !PRIORITYQUEUE_PRIORITYQUEUE_H
