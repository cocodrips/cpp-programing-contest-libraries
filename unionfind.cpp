class UnionFind{
public:
    int *par;
    int *rank;
    UnionFind(int n) {
        par = new int[n]; rank = new int[n];
        for (int i = 0; i < n; ++i){ par[i] = i; rank[i] = 0;}
    }

    ~UnionFind() { delete par; delete rank; }

    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) return;
        if(rank[x] < rank[y]) par[x] = y;
        else{
            par[y] = x;
            if(rank[x] == rank[y]) rank[x]++;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// test
#include <iostream>
int main(int argc, char const *argv[])
{
    int n = 10;
    UnionFind *unionfind = new UnionFind(n);
    for (int i = 0; i < 5; ++i){
        unionfind -> unite(i, i+1);
    }
    std::cout<< unionfind -> same(1,2) << std::endl;
    std::cout<< unionfind -> same(1,5) << std::endl;
    std::cout<< unionfind -> same(7,8) << std::endl;
    return 0;
}
