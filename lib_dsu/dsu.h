#ifndef DSU_DSU_H
#define DSU_DSU_H

class DSU {
    int* _parent;
    int* _rank;
    size_t _size;

public:
    DSU(size_t);
    ~DSU();

    int find(int);
    void unite(int, int);
private:
    int find_rec(int);
};

#endif // !DSU_DSU_H
