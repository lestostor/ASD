#include "dsu.h" 
#include <stdexcept>

DSU::DSU(size_t size) {
    _size = size;
    _parent = new int[size];
    _rank = new int[size];
    for (size_t i = 0; i < size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[]_parent;
    delete[]_rank;
}

int DSU::find(int x) {
    if (x >= _size || x < 0)
        throw std::invalid_argument("Wrong element");

    return _parent[x] = find_rec(_parent[x]);
}

int DSU::find_rec(int x)  {
    if (x == _parent[x]) return x;
    return _parent[x] = find_rec(_parent[x]);
}

void DSU::unite(int x, int y) {
    if (x >= _size || y >= _size || x < 0 || y < 0)
        throw std::invalid_argument("Wrong elements");
    if (x == y) return;

    int parent_x = find(x);
    int parent_y = find(y);

    if (_rank[parent_x] >= _rank[parent_y])
        _parent[parent_y] = parent_x;
    else
        _parent[parent_x] = parent_y;
    if (_rank[parent_x] == _rank[parent_y])
        _rank[parent_x]++;
}