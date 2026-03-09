#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include "../lib_TVector/tvector.h"
#include <utility>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <sstream>
template <class TKey, class TValue>
struct SkipNode {
    std::pair<TKey, TValue> _data;
    SkipNode<TKey, TValue>** _next;
    size_t _size;

public:
    SkipNode(size_t size) : _data(), _size(size) {
        _next = new SkipNode<TKey, TValue>*[size];
        for (size_t i = 0; i < size; i++)
            _next[i] = nullptr;
    }

    SkipNode(TKey key, TValue value, size_t size) : _data(key, value), _size(size) {
        _next = new SkipNode<TKey, TValue>* [size];
        for (int i = 0; i < size; i++) {
            _next[i] = new SkipNode<TKey, TValue>(size);
        }
    }

    ~SkipNode() {
        delete[] _next;
    }
};

template <class TKey, class TValue>
class SkipList {
    int _max_level;
    size_t _levels = 0;
    TVector<SkipNode<TKey, TValue>*> _heads;

public:
    SkipList(int max_level = -1);

    void insert(const TKey&, const TValue&);
    void print() const noexcept;
private:
    size_t flip_coin() const noexcept;
    TVector<SkipNode<TKey, TValue>*> find_nearest(const TKey&) const;
    void add_levels(size_t);
    std::string to_string(const std::pair<TKey, TValue>&) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(int max_level) : _max_level(max_level), _heads() {
    srand(time(0));
    if (max_level != -1) {
        for (int i = 0; i < max_level; i++) {
            SkipNode<TKey, TValue>* node = new SkipNode<TKey, TValue>(max_level);
            _heads.push_back(node);
        }
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    size_t level = flip_coin();
    if (_max_level == -1 && level > _levels)
        add_levels(level);
    else _levels = std::max(level, _levels);

    TVector<SkipNode<TKey, TValue>*> updates = find_nearest(key);
    SkipNode<TKey, TValue>* new_node = new SkipNode<TKey, TValue>(key, value, level);

    for (int i = 0; i < level; i++) {
        new_node->_next[i] = updates[i]->_next[i];
        updates[i]->_next[i] = new_node;
    }
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    int i = 0;
    std::vector<std::string> elements;
    SkipNode<TKey, TValue>* curr = _heads.back()->_next[0];
    while (curr) {
        std::string data = to_string(curr->_data);
        elements.push_back(data);
        curr = curr->_next[0];
    }

    for (auto it = _heads.begin(); it != _heads.end(); it++, i++) {
        int level = _heads.size() - i - 1;
        SkipNode<TKey, TValue>* curr = (*it)->_next[level];
        std::cout << "Level " << i << ": ";

        do {
            std::string data = to_string(curr->_data);

            for (auto el_it = elements.begin(); el_it != elements.end(); el_it++) {
                data = to_string(curr->_data);

                if ((*el_it) == data) {
                    std::cout << "[" << data << "]-";
                    curr = curr->_next[level];
                }
                else {
                    for (int j = 0; j < (*el_it).size() + 3; j++)
                        std::cout << "-";
                }
            }
        } while (curr != nullptr);
        std::cout << "[NULL]" << std::endl;
    }
}

template <class TKey, class TValue>
TVector<SkipNode<TKey, TValue>*> SkipList<TKey, TValue>::find_nearest(const TKey& key) const {

    TVector<SkipNode<TKey, TValue>*> updates;

    auto it = _heads.rbegin();
    SkipNode<TKey, TValue>* curr;

    for (int i = 0; i < _levels; i++, it--) {
        curr = *it;

        while (curr->_next[i] != nullptr && curr->_next[i]->_data.first < key)
            curr = curr->_next[i];

        if (*curr->_next != nullptr && (*curr->_next)->_data.first == key)
            throw std::invalid_argument("This key already exists");

        updates.push_back(curr);
    }

    return updates;
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    int times = 1;
    int coin;

    do {
        times++;
        coin = 1 + rand() % 100;
        if (_max_level != -1 && times == _max_level)
            break;
    } while (coin > 50);

    return times;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::add_levels(size_t new_max_level) {
    for (int i = _levels; i < new_max_level; i++) {
        SkipNode<TKey, TValue>* node = new SkipNode<TKey, TValue>(new_max_level);
        _heads.push_back(node);
    }

    _levels = new_max_level;
}

template <class TKey, class TValue>
std::string SkipList<TKey, TValue>::to_string(const std::pair<TKey, TValue>& pair) const noexcept{
    if (&pair == NULL) return "";
    std::ostringstream key_out, value_out;
    key_out << pair.first;
    value_out << pair.second;

    return key_out.str() + ": " + value_out.str();
}

#endif // !SKIPLIST_SKIPLIST_H
