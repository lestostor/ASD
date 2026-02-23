#ifndef SORTEDVECTABLE_SORTEDVECTABLE_H
#define SORTEDVECTABLE_SORTEDVECTABLE_H

#include "../lib_ITable/itable.h"
#include "../lib_TVector/tvector.h"

#define KEY_WIDTH 10
#define VALUE_WIDTH 50

template <class TKey, class TValue>
class SortedVecTable {
    TVector<std::pair<TKey, TValue>> _rows;
public:
    SortedVecTable();
    ~SortedVecTable() {}

    void insert(const TKey&, const TValue&);
    void erase(const TKey&);
    TValue* find(const TKey&) const noexcept;
    inline bool is_empty() const noexcept { return _rows.is_empty(); }

    friend std::ostream& operator<<(std::ostream& out, const SortedVecTable& table) {
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
SortedVecTable<TKey, TValue>::SortedVecTable() : _rows() {}

template <class TKey, class TValue>
void SortedVecTable<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (find(key) != nullptr)
        throw std::invalid_argument("This key already exist");

    std::pair<TKey, TValue> row = std::pair<TKey, TValue>(key, value);
    if (_rows.is_empty()) {
        _rows.push_back(row);
        return;
    }

    int l = 0, r = _rows.size() - 1, i;

    while (l <= r) {
        if (l == r ) {
            _rows.insert(_rows.begin() + l + 1, row);
            return;
        }
        i = (l + r) / 2;

        if (_rows[i].first > key) r = i - 1;
        else l = i + 1;
    }
}

template <class TKey, class TValue>
void SortedVecTable<TKey, TValue>::erase(const TKey& key) {
    int l = 0, r = _rows.size() - 1, i;

    while (l <= r) {
        i = (l + r) / 2;

        if (_rows[i].first == key) {
            _rows.erase(_rows.begin() + i);
            return;
        }
        else if (_rows[i].first > key) r = i - 1;
        else l = i + 1;
    }

    throw std::logic_error("This key wasn't found");
}

template <class TKey, class TValue>
TValue* SortedVecTable<TKey, TValue>::find(const TKey& key) const noexcept {
    int l = 0, r = _rows.size() - 1, i;

    while (l <= r) {
        i = (l + r) / 2;

        if (_rows[i].first == key)
            return new TValue(_rows[i].second);
        else if (_rows[i].first > key) r = i - 1;
        else l = i + 1;
    }
    return nullptr;
}

#endif // !SORTEDVECTABLE_SORTEDVECTABLE_H
