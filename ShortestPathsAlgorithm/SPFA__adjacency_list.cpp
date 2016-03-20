#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
#include<queue>
#include<stack>
using namespace std;
 
const int NV = 101;
const int NE = 20001;
const int inf = INT_MAX >> 1;
 
struct SPFA {
    int n, size;
    int dis[NV], head[NV];
    bool in[NV];
 
    struct edge {
        int v, w, next;
        edge () {}
        edge (int V, int NEXT, int W = 0) : v(V), next(NEXT), w(W) {}
    }E[NE];
 
    void init(int nn) {
        n = nn, size = 0;
        for (int i = 0; i <= n; i++) {
            head[i] = -1;
            in[i] = 0;
            dis[i] = inf;
        }
    }
 
    inline void insert(int u, int v, int w) {
        E[size] = edge(v, head[u], w);
        head[u] = size++;
    }
 
    inline bool relax(int u, int v, int w) {
        if (dis[v] == inf || dis[u] + w < dis[v]) {
            dis[v] = dis[u] + w;
            return true;
        }
        return false;
    }
 
    int spfa(int src, int des) {
        queue<int> que;
        dis[src] = 0;
        que.push(src);
        in[src] = true;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            in[u] = false;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].v;
                if (relax(u, v, E[i].w) && !in[v] ) {
                    in[v] = true;
                    que.push(v);
                }//if
            }//for
        }//while
        return dis[des];
    }//SFPA
}G;
 
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m), n | m) {
        G.init(n);
        int a, b, c;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            G.insert(a, b, c);
            G.insert(b, a, c);
        }
        printf("%d\n", G.spfa(1, n));
    }
    return 0;
}
两大最强最