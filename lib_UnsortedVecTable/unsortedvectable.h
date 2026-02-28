#ifndef UNSORTEDVECTABLE_UNSORTEDVECTABLE_H
#define UNSORTEDVECTABLE_UNSORTEDVECTABLE_H

#include "../lib_ITable/itable.h"
#include "../lib_TVector/tvector.h"
#include <iostream>

#define KEY_WIDTH 10
#define VALUE_WIDTH 50

template <class TKey, class TValue>
class UnsortedVecTable : ITable<TKey, TValue> {
    TVector<std::pair<TKey, TValue>> _rows;
public:
    UnsortedVecTable();
    ~UnsortedVecTable() {}

    void insert(const TKey&, const TValue&);
    void erase(const TKey&);
    TValue* find(const TKey&) const noexcept;
    inline bool is_empty() const noexcept { return _rows.is_empty(); };

    friend std::ostream& operator<<(std::ostream& out, const UnsortedVecTable& table) {
        // head
        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";

        std::cout << "+" << std::endl << "| Key      | Value";
        for (int i = 0; i < VALUE_WIDTH - 6; i++) std::cout << " ";
        std::cout << "|" << std::endl;

        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
        std::cout << "+" << std::endl;

        for (int i = 0; i < table._rows.size(); i++) {
            std::ostringstream key_out, value_out;
            key_out << (table._rows[i]).first;
            value_out << (table._rows[i]).second;
            std::string key = key_out.str(), value = value_out.str();

            // row
            std::cout << "| " << key;
            for (int i = 0; i < KEY_WIDTH - key.size() - 1; i++) std::cout << " ";
            std::cout << "| " << value;
            for (int i = 0; i < VALUE_WIDTH - value.size() - 1; i++) std::cout << " ";
            std::cout << "|" << std::endl;

            // border
            std::cout << "+----------+";
            for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
            std::cout << "+" << std::endl;
        }

        return out;
    };
};

template <class TKey, class TValue>
UnsortedVecTable<TKey, TValue>::UnsortedVecTable() : _rows() {}

template <class TKey, class TValue>
void UnsortedVecTable<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    std::pair<TKey, TValue> row = std::pair<TKey, TValue>(key, value);
    if (find(key) != nullptr)
        throw std::invalid_argument("This key already exists");
    _rows.push_back(row);
}

template <class TKey, class TValue>
void UnsortedVecTable<TKey, TValue>::erase(const TKey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if ((*it).first == key) {
            _rows.erase(it);
            return;
        }
    }

    throw std::logic_error("This key wasn't found");
}

template <class TKey, class TValue>
TValue* UnsortedVecTable<TKey, TValue>::find(const TKey& key) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if ((*it).first == key)
            return &((*it).second);
    }
    return nullptr;
}

#endif // !UNSORTEDVECTABLE_UNSORTEDVECTABLE_H
