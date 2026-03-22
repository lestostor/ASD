#ifndef SORTEDTREETABLE_SORTEDTREETABLE_H
#define SORTEDTREETABLE_SORTEDTREETABLE_H

#include "../lib_BSTree/bstree.h"
#include "../lib_ITable/itable.h"
#include <iostream>

#define KEY_WIDTH 10
#define VALUE_WIDTH 50

template <class TKey, class TValue>
class SortedTreeTable : ITable<TKey, TValue> {
    BSTree<TKey, TValue> _rows;

public:
    SortedTreeTable();
    ~SortedTreeTable() {}

    void insert(const TKey& key, const TValue& value) { _rows.insert(key, value); }
    void erase(const TKey& key) { _rows.erase(key); }
    TValue* find(const TKey& key) const noexcept { return _rows.find(key); }
    inline bool is_empty() const noexcept { return _rows.is_empty(); }

    friend std::ostream& operator<<(std::ostream& out, const SortedTreeTable<TKey, TValue>& table) {
        if (table.is_empty()) return out;

        // head
        out << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) out << "-";

        out << "+" << std::endl << "| Key      | Value";
        for (int i = 0; i < VALUE_WIDTH - 6; i++) out << " ";
        out << "|" << std::endl;

        out << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) out << "-";
        std::cout << "+" << std::endl;

        table.print_rec(table._rows.root());
    }

private:
    void print_rec(Node<TKey, TValue>*) const noexcept;
    void print_row(const TKey&, const TValue&) const noexcept;
};
template <class TKey, class TValue>
SortedTreeTable<TKey, TValue>::SortedTreeTable() : _rows() {}

template <class TKey, class TValue>
void SortedTreeTable<TKey, TValue>::print_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_rec(node->_left);
    print_row(node->_data.first, node->_data.second);
    print_rec(node->_right);
}

template <class TKey, class TValue>
void SortedTreeTable<TKey, TValue>::print_row(const TKey& key, const TValue& value) const noexcept {
    std::ostringstream key_out, value_out;
    key_out << key;
    value_out << value;
    std::string key_str = key_out.str(), value_str = value_out.str();

    // row
    std::cout << "| " << key_str;
    for (int i = 0; i < KEY_WIDTH - key_str.size() - 1; i++) std::cout << " ";
    std::cout << "| " << value_str;
    for (int i = 0; i < VALUE_WIDTH - value_str.size() - 1; i++) std::cout << " ";
    std::cout << "|" << std::endl;

    // border
    std::cout << "+----------+";
    for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
    std::cout << "+" << std::endl;
}

#endif // !SORTEDTREETABLE_SORTEDTREETABLE_H
