#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
 
const int NV = 101;
const int NE = 5011;
 
struct Kruskal {
    int n, size;
    int root[NV];
    int mst;
 
    struct Edge {
        int u, v, w;
        Edge () {}
        Edge (int U, int V, int W = 0) : u(U), v(V), w(W) {}
        bool operator < (const Edge &rhs) const {//从小到大
            return w < rhs.w;
        }
    } E[NE];
 
    inline void init(int x) {
        n = x, size = 0;
        for (int i = 0; i < x; i++) {
            root[i] = i;
        }
    }
 
    inline void insert(int u, int v, int w = 0) {
        E[size++] = Edge(u, v, w);
    }
 
    int Getroot (int n) {
        int r = n;
        while (r != root[r]) r = root[r];
        int x = n, y;
        while (x != r) {
            y = root[x];
            root[x] = r;
            x = y;
        }
        return r;
    }
 
    bool Union(int x, int y) {
        int fx = Getroot(x), fy = Getroot(y);
        if (fx != fy) {
            root[fx] = fy;
            return true;
        }
        return false;
    } 
 
    int kruskal () {
        mst = 0;
        sort(E, E + size);
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (Union(E[i].u, E[i].v)) {
                mst += E[i].w;
                if (++cnt == n - 1) break; // 优化
            }
        }
        return mst;
    } // kruskal O(E)
}G;
 
int main() {
    int n;
    while (~scanf("%d", &n), n) {
        G.init(n);
        int k = n * (n - 1) / 2;
        for (int i = 0; i < k; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            G.insert(a - 1, b - 1, c);
        }
        printf("%d\n", G.kruskal());
    }
    return 0;
}