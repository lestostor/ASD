#include "dsu.h" 
#include <stdexcept>

DSU::DSU(size_t size) {
    _size = size;
    _parent = new int[size];
    _rank = new int[size];
    for (int i = 0; i < size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[]_parent;
    delete[]_rank;
}

int DSU::find(int x) const {
    if (x >= _size || x < 0)
        throw std::invalid_argument("Wrong element");

    return find_rec(x);
}

int DSU::find_rec(int x) const {
    if (x == _parent[x]) return x;
    return x = find(_parent[x]);
}

void DSU::unite(int x, int y) {
    if (x >= _size || y >= _size || x < 0 || y < 0)
        throw std::invalid_argument("Wrong elements");
    if (x == y) return;

    int parent_x = find(x);
    int parent_y = find(y);

    if (_rank[parent_x] >= _rank[parent_y])
        _parent[parent_y] = parent_x;
    else if (_rank[parent_y] > _rank[parent_x])
        _parent[parent_x] = parent_y;
    if (_rank[parent_x] == _rank[parent_y])
        _rank[parent_x]++;
}