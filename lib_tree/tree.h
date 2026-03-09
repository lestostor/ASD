#ifndef TREE_TREE_H
#define TREE_TREE_H

#include "../lib_queue/queue.h"
#include <iostream>

template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> _data;
    Node<TKey, TValue>* _left;
    Node<TKey, TValue>* _right;

    Node<TKey, TValue>(const TKey& key, const TValue& value, Node<TKey, TValue>* left = nullptr, Node<TKey, TValue>* right = nullptr) :
        _data(key, value), _left(left), _right(right) {}
};

template <class TKey, class TValue>
class Tree {
    Node<TKey, TValue>* _root;

public:
    Tree(Node<TKey, TValue>* root = nullptr);
    ~Tree();

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey&);
    inline bool is_empty() const noexcept { return _root == nullptr; }
    void clear() noexcept;

    void print_w() const noexcept;
    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;

private:
    void print_lcr_rec(Node<TKey, TValue>*) const noexcept;
    void print_clr_rec(Node<TKey, TValue>*) const noexcept;
    void print_lrc_rec(Node<TKey, TValue>*) const noexcept;
    void clear_rec();
    TValue* find_rec(const TKey&, Node<TKey, TValue>*) const;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree(Node<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    if (is_empty()) return;

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);
    Node<TKey, TValue>* curr = nullptr;

    while (!q.is_empty()) {
        curr = q.head();
        Node<TKey, TValue>* deleted = curr;
        q.pop();
        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(curr->_right);

        delete deleted;
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TKey, TValue>* node = new Node<TKey, TValue>(key, value);

    if (is_empty()) {
        _root = node;
        return;
    }

    Node<TKey, TValue>* curr = nullptr;
    Queue<Node<TKey, TValue>*> q;
    q.push(_root);
    while (true) {
        curr = q.head();
        q.pop();
        if (!curr->_left) {
            curr->_left = node;
            return;
        }
        if (!curr->_right) {
            curr->_right = node;
            return;
        }

        q.push(curr->_left);
        q.push(curr->_right);
    }
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
    return find_rec(key, _root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    Node<TKey, TValue>* curr = nullptr, *deleted = nullptr, *prev = nullptr;
    Queue<Node<TKey, TValue>*> q;
    bool right_is_found = false, left_is_found = false;
    q.push(_root);

    do {
        curr = q.head();
        q.pop();
        if (!left_is_found && curr->_left && curr->_left->_data.first == key) {
            deleted = curr->_left;
            prev = curr;
            left_is_found = true;
        }
        else if (!right_is_found && curr->_right && curr->_right->_data.first == key) {
            deleted = curr->_right;
            prev = curr;
            right_is_found = true;
        }

        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(curr->_right);
    } while (!q.is_empty());

    if (left_is_found)
        prev->_left = new Node<TKey, TValue>(curr->_data.first, curr->_data.second,
            deleted->_left, deleted->_right);
    else if (right_is_found)
        prev->_right = new Node<TKey, TValue>(curr->_data.first, curr->_data.second,
            deleted->_left, deleted->_right);
    else throw std::invalid_argument("This key wasn't found");

    curr = nullptr;  // ???
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find_rec(const TKey& key, Node<TKey, TValue>* node) const {
    if (node && node->_data.first == key) return &(node->_data.second);

    TValue* val = nullptr;
    if (node && node->_left)
        val = find_rec(key, node->_left);
    if (node && node->_right && !val)
        val = find_rec(key, node->_right);

    return val;
}

#endif // !TREE_TREE_H
