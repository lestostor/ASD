#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H

#include "../lib_queue/queue.h"
#include <utility>
#include <string>
#include <iostream>
#include <vector>

enum Color {red, black};

template <class TKey, class TValue>
struct RBNode {
    std::pair<TKey, TValue> _data;
    RBNode<TKey, TValue>* _left;
    RBNode<TKey, TValue>* _right;
    RBNode<TKey, TValue>* _parent;
    Color _color;

    RBNode<TKey, TValue>(const TKey& key, const TValue& val, RBNode<TKey, TValue>* parent = nullptr, Color color = black,
        RBNode<TKey, TValue>* left = nullptr, RBNode<TKey, TValue>* right = nullptr) :
        _data(key, val), _parent(parent), _left(left), _right(right), _color(color) {}
};

template <class TKey, class TValue>
class RBTree {
    RBNode<TKey, TValue>* _root;

public:
    RBTree(RBNode<TKey, TValue>* root = nullptr);
    ~RBTree();

    inline RBNode<TKey, TValue>* root() const noexcept { return _root; }

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    inline bool is_empty() const noexcept { return _root == nullptr; }
    void clear() noexcept;
    int height(RBNode<TKey, TValue>*) const noexcept;

    void print() const noexcept;


private:
    void swap_colors(RBNode<TKey, TValue>*, RBNode<TKey, TValue>*);
    void recover_balance(RBNode<TKey, TValue>*);
    void recolor(RBNode<TKey, TValue>*);
    void left_rotate(RBNode<TKey, TValue>*);
    void right_rotate(RBNode<TKey, TValue>*);
    void RR(RBNode<TKey, TValue>*);
    void LL(RBNode<TKey, TValue>*);
    void RL(RBNode<TKey, TValue>*);
    void LR(RBNode<TKey, TValue>*);

    RBNode<TKey, TValue>* bstree_insert(const TKey&, const TValue&);
    RBNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;

    void print_visual_rec(RBNode<TKey, TValue>*, int) const noexcept;
    std::string data_string(RBNode<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree(RBNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
RBTree<TKey, TValue>::~RBTree() {
    clear();
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    RBNode<TKey, TValue>* node = bstree_insert(key, value);

    if (node == _root) {
        recolor(node);
        return;
    }

    if (node->_parent->_color == red) {
        recover_balance(node);
        return;
    }
}

template <class TKey, class TValue>
TValue* RBTree<TKey, TValue>::find(const TKey& key) const noexcept {
    RBNode<TKey, TValue>* parent = find_parent(key);

    if (!parent)
        return nullptr;
    if (parent->_left && parent->_left->_data.first == key)
        return &parent->_left->_data.second;
    if (parent->_right && parent->_right->_data.first == key)
        return &parent->_right->_data.second;
    if (parent == _root && parent->_data.first == key)
        return &_root->_data.second;

    return nullptr;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    Queue<RBNode<TKey, TValue>*> q;
    q.push(_root);
    RBNode<TKey, TValue>* curr = nullptr;

    while (!q.is_empty()) {
        curr = q.head();
        RBNode<TKey, TValue>* deleted = curr;
        q.pop();
        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(curr->_right);

        delete deleted;
    }

    _root = nullptr;
}

template <class TKey, class TValue>
int RBTree<TKey, TValue>::height(RBNode<TKey, TValue>* node) const noexcept {
    if (!node) return 0;

    return std::max(height(node->_left), height(node->_right)) + 1;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print() const noexcept {
    print_visual_rec(_root, 0);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print_visual_rec(RBNode<TKey, TValue>* node, int level) const noexcept {
    if (!node) return;

    print_visual_rec(node->_right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "          ";
    }
    std::string data = data_string(node);
    std::cout << data;

    int num_length = data.size();
    for (int j = 0; j < num_length; j++) {
        std::cout << "  ";
    }
    std::cout << std::endl;

    print_visual_rec(node->_left, level + 1);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::swap_colors(RBNode<TKey, TValue>* node1, RBNode<TKey, TValue>* node2) {
    std::swap(node1->_color, node2->_color);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recover_balance(RBNode<TKey, TValue>* node) {
    //        GB                     GB                      GR
    //      /   \                  /   \                   /   \
    //     UR   PR     --->       UB   PB      --->       UB   PB
    //            \                     \                       \
    //            CR                    CR                      CR
    //

    RBNode<TKey, TValue>* C = node, *P = C->_parent, * G = P->_parent, *U = G->_right == P ? G->_left : G->_right;
    while (U && U->_color == red && P->_color == red) {
        recolor(U);
        recolor(P);
        if (_root == G) break;
        recolor(G);
    
        C = G;
        P = C->_parent;
        G = P->_parent;
        if (G)
            U = G->_right == P ? G->_left : G->_right;
        else U = nullptr;
    }

    if (P->_color == black) return;

    if (G->_right == P && P->_right == C) {
        //     GB                                 PR
        //   /   \                              /   \
        //  UB   PR                            GB   CR    ---> swap_color(P, G);
        // / \   / \             --->         / \   / \
        //T1 T2 T3  CR                       UB T3 T4 T5
        //         / \                      / \
        //        T4  T5                   T1 T2

        RR(G);
        swap_colors(P, G);
    }
    else if (G->_right == P && P->_left == C) {
        //     GB                                 GB                   CR
        //   /   \                              /   \                /   \
        //  UB   PR                            UB   CR              GB   PR     ---> swap_color(C, G);
        // / \   / \             --->         / \   / \     --->   / \   / \
        //T1 T2 CR T5                        T1 T2 T3 PR          UB T3 T4 T5
        //     /  \                                  /  \        /  \
        //    T3  T4                                T4  T5      T1  T2

        RL(G);
        swap_colors(C, G);
    }
    else if (G->_left == P && P->_left == C) {
        LL(G);
        swap_colors(P, G);
    }
    else if (G->_left == P && P->_right == C) {
        LR(G);
        swap_colors(C, G);
    }
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::recolor(RBNode<TKey, TValue>* node) {
    if (node->_color == red)
        node->_color = black;
    else
        node->_color = red;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, * P = G->_right;

    P->_parent = G->_parent;
    G->_right = P->_left;
    P->_left = G;

    if (G->_parent && G->_parent->_right == node)
        G->_parent->_right = P;
    else if (G->_parent && G->_parent->_left == node)
        G->_parent->_left = P;

    G->_parent = P;

    if (G->_right)
        G->_right->_parent = G;
    if (G == _root)
        _root = P;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, * P = G->_left;

    P->_parent = G->_parent;
    G->_left = P->_right;
    P->_right = G;

    if (G->_parent && G->_parent->_right == node)
        G->_parent->_right = P;
    else if (G->_parent && G->_parent->_left == node)
        G->_parent->_left = P;

    G->_parent = P;

    if (G->_left)
        G->_left->_parent = G;
    if (G == _root)
        _root = P;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RR(RBNode<TKey, TValue>* node) {
    left_rotate(node);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::LL(RBNode<TKey, TValue>* node) {
    right_rotate(node);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::RL(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, * P = G->_right;
    right_rotate(P);
    left_rotate(G);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::LR(RBNode<TKey, TValue>* node) {
    RBNode<TKey, TValue>* G = node, * P = G->_left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::bstree_insert(const TKey& key, const TValue& value) {
    RBNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new RBNode<TKey, TValue>(key, value, nullptr, red);
        return _root;
    }
    if (parent->_data.first < key && !parent->_right) {
        parent->_right = new RBNode<TKey, TValue>(key, value, parent, red);
        return parent->_right;
    }
    if (parent->_data.first > key && !parent->_left) {
        parent->_left = new RBNode<TKey, TValue>(key, value, parent, red);
        return parent->_left;
    }

    throw std::invalid_argument("This key already exists");
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    if (_root->_data.first == key) return _root;

    RBNode<TKey, TValue>* curr = _root;

    while (true) {
        if (curr->_data.first > key) {
            if (!curr->_left)
                return curr;
            if (curr->_left && curr->_left->_data.first == key)
                return curr;
            curr = curr->_left;
        }
        else {
            if (!curr->_right)
                return curr;
            if (curr->_right && curr->_right->_data.first == key)
                return curr;
            curr = curr->_right;
        }
    }
}

//template <class TKey, class TValue>
//void RBTree<TKey, TValue>::print_lines(const std::vector<RBNode<TKey, TValue>*>& nodes, int level, int width) const noexcept {
//    for (int i = 0; i < nodes.size(); i++)
//        std::cout << std::string(width - i - 1, ' ') << (nodes[i]->_left ? "/" : " ") << std::string(width + data_string(nodes[i]).size(), ' ') << (nodes[i]->_right ? "\\" : "");
//    std::cout << std::endl;
//}

template <class TKey, class TValue>
std::string RBTree<TKey, TValue>::data_string(RBNode<TKey, TValue>* node) const noexcept {
    std::ostringstream key_out, value_out;
    key_out << node->_data.first;
    value_out << node->_data.second;
    std::string key_str = key_out.str(), value_str = value_out.str();

    return std::string(node->_color == black ? "[" : "(") + key_str + ": " + value_str + (node->_color == black ? "]" : ")");
}

#endif // !RBTREE_RBTREE_H
