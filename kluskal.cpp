#include <algorithm>
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

struct edge{ int u, v, cost; };
int kluskal(edge es[], int V, int E) {
    std::sort(es, es + E, [](const edge& e1, const edge& e2){ return e1.cost < e2.cost; });
    UnionFind unionfind(V);
    int res = 0;
    for (int i = 0; i < E; ++i){
        edge e = es[i];
        if(unionfind.same(e.u, e.v)) continue;
        unionfind.unite(e.u, e.v);
        res += e.cost;
    }
    return res;
}

#include <iostream>
int main(){
    const int n = 10;
    edge es[n];
    for (int i = 0; i < n - 1; ++i){
        edge e = edge();
        e.u = i;
        e.v = i + 1;
        e.cost = i;
        es[i] = e;
    }

    int cost = kluskal(es, n, n - 1);
    std::cout << cost << std::endl;
    
    return 0;
}

