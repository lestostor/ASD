#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include "../lib_queue/queue.h"
#include "../lib_BSTree/bstree.h"

template <class TKey, class TValue>
struct AVLNode {
    std::pair<TKey, TValue> _data;
    AVLNode<TKey, TValue>* _left, * _right, * _parent;
    int _height;

    AVLNode(const TKey& key, const TValue& value, AVLNode<TKey, TValue>* parent = nullptr, int height = 1,
        AVLNode<TKey, TValue>* left = nullptr, AVLNode<TKey, TValue>* right = nullptr) :
        _data(key, value), _left(left), _right(right), _parent(parent), _height(height) {}
};

template <class TKey, class TValue>
class AVLTree {
    AVLNode<TKey, TValue>* _root;

public:
    AVLTree(AVLNode<TKey, TValue>* root = nullptr);
    ~AVLTree();

    inline AVLNode<TKey, TValue>* root() const noexcept { return _root; }

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey&);
    void clear() noexcept;
    inline bool is_empty() const noexcept { return _root == nullptr; }

private:
    void left_rotate(AVLNode<TKey, TValue>*);
    void right_rotate(AVLNode<TKey, TValue>*);
    void RR(AVLNode<TKey, TValue>*);
    void LL(AVLNode<TKey, TValue>*);
    void RL(AVLNode<TKey, TValue>*);
    void LR(AVLNode<TKey, TValue>*);
    inline int get_height(AVLNode<TKey, TValue>* node) const noexcept { return (node) ? node->_height : 0; }
    inline int calc_balance(AVLNode<TKey, TValue>* node) const noexcept { return get_height(node->_right) - get_height(node->_left); }
    void recalc_height(AVLNode<TKey, TValue>*) noexcept;
    void recover_balance(AVLNode<TKey, TValue>*) noexcept;

    AVLNode<TKey, TValue>* bstree_insert(const TKey&, const TValue&);
    AVLNode<TKey, TValue>* bstree_erase(const TKey&);
    AVLNode<TKey, TValue>* delete_node(AVLNode<TKey, TValue>*& node) noexcept;
    AVLNode<TKey, TValue>* find_max_left(AVLNode<TKey, TValue>* node) const noexcept;
    AVLNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(AVLNode<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear();
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* node = bstree_insert(key, value);

    if (node == _root)
        return;

    AVLNode<TKey, TValue>* P = node->_parent, *G = nullptr;
    recalc_height(P);
    if (P)
        G = P->_parent;
    if (!G)
        return;

    AVLNode<TKey, TValue>* curr = G;
    while (curr) {
        int balance = calc_balance(curr);

        if (abs(balance) > 1) {
            recover_balance(curr);
            return;
        }
        curr = curr->_parent;
    }

    curr = G;
    int prev_height;
    while (curr) {
        prev_height = curr->_height;
        recalc_height(curr);
        if (prev_height == curr->_height)
            break;

        curr = curr->_parent;
    }
}

template <class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::find(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* parent = find_parent(key);

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
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    AVLNode<TKey, TValue>* node = bstree_erase(key);

    while (node) {
        int balance = calc_balance(node);
        int old_height = node->_height;

        if (abs(balance) > 1)
            recover_balance(node);

        recalc_height(node);
        if (old_height == node->_height)
            break;

        node = node->_parent;
        if (node && node->_parent)
            node = node->_parent;
    }
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear() noexcept {
    if (is_empty()) return;

    Queue<AVLNode<TKey, TValue>*> q;
    q.push(_root);
    AVLNode<TKey, TValue>* curr = nullptr;

    while (!q.is_empty()) {
        curr = q.head();
        AVLNode<TKey, TValue>* deleted = curr;
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
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node, * P = G->_right;
    // G                  P
    //   \              /   \
    //    P     --->   G     C
    //  /   \            \
    // T    C             T

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
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node, * P = G->_left;
    //             G             P
    //           /             /   \
    //          P      --->   C     G
    //        /   \               /
    //       C     T             T

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
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    left_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    right_rotate(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    // G                G                 C
    //  \                \              /   \
    //   P     --->       C     --->   G     P
    //  /                  \
    // C                    P

    AVLNode<TKey, TValue>* G = node, * P = G->_right;
    right_rotate(P);
    left_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    //   G               G               C
    //  /               /              /   \
    // P     --->      C     --->     P     G
    //  \             /
    //   C           P

    AVLNode<TKey, TValue>* G = node, * P = G->_left;
    left_rotate(P);
    right_rotate(G);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) noexcept {
    if (!node) return;

    recalc_height(node->_left);
    recalc_height(node->_right);

    node->_height = 1 + std::max(get_height(node->_left), get_height(node->_right));
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) noexcept {
    int balance = calc_balance(node);

    if (balance < -1) {  // left subtree
        balance = calc_balance(node->_left);

        if (balance > 0)
            LR(node);
        else LL(node);
    }
    else {  // right subtree
        balance = calc_balance(node->_right);

        if (balance > 0)
            RR(node);
        else RL(node);
    }

    recalc_height(node->_parent);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::bstree_insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new AVLNode<TKey, TValue>(key, value);
        return _root;
    }
    if (parent->_data.first < key && !parent->_right) {
        parent->_right = new AVLNode<TKey, TValue>(key, value, parent);
        return parent->_right;
    }
    if (parent->_data.first > key && !parent->_left) {
        parent->_left = new AVLNode<TKey, TValue>(key, value, parent);
        return parent->_left;
    }

    throw std::invalid_argument("This key already exists");
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::bstree_erase(const TKey& key) {
    AVLNode<TKey, TValue>* parent = find_parent(key);

    if (parent && parent->_right && parent->_right->_data.first == key)
        return delete_node(parent->_right);
    else if (parent && parent->_left && parent->_left->_data.first == key)
        return delete_node(parent->_left);
    else if (parent && parent == _root)
        return delete_node(_root);
    else
        throw std::invalid_argument("This key wasn't found");
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::delete_node(AVLNode<TKey, TValue>*& node) noexcept {
    AVLNode<TKey, TValue>* parent_deleted = nullptr;
    if (!node->_left && !node->_right) {
        parent_deleted = node->_parent;
        delete node;
        node = nullptr;
    }
    else if (!node->_left) {
        AVLNode<TKey, TValue>* deleted = node;
        parent_deleted = deleted->_parent;
        node = node->_right;
        delete deleted;
    }
    else if (!node->_right) {
        AVLNode<TKey, TValue>* deleted = node;
        parent_deleted = deleted->_parent;
        node = node->_left;
        delete deleted;
    }
    else {
        AVLNode<TKey, TValue>* max_left = find_max_left(node), *parent_deleted = find_parent(max_left->_data.first);
        node->_data = max_left->_data;
        if (parent_deleted->_left == max_left) {
            delete max_left;
            parent_deleted->_left = nullptr;
        }
        else {
            delete max_left;
            parent_deleted->_right = nullptr;
        }
    }

    return parent_deleted;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_max_left(AVLNode<TKey, TValue>* node) const noexcept {
    AVLNode<TKey, TValue>* curr = node->_left, *max = curr;

    while (curr) {
        if (curr->_data.first > max->_data.first)
            max = curr;
        curr = curr->_right;
    }

    return max;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    if (_root->_data.first == key) return _root;

    AVLNode<TKey, TValue>* curr = _root;

    while (true) {
        if (curr->_data.first > key) {
            if (!curr->_left)  // parent for insert
                return curr;
            if (curr->_left && curr->_left->_data.first == key)  // parent for find
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

#endif // !AVLTREE_AVLTREE_H
