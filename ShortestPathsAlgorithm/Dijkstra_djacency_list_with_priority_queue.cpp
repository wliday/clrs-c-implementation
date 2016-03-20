/*邻接表 +  优先队列 + Dijkstra求最短路*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
#include<queue>
using namespace std;
 
const int NV = 102;
const int NE = 20002;
int n, m;
 
struct Dijkstra {
    int n, size;
    int dis[NV], head[NV];
    int mark[NV];
 
    struct node {
        int v, dis;
        node () {}
        node (int V, int DIS) : v(V), dis(DIS) {}
        friend bool operator < (const node a, const node b) {
            return a.dis > b.dis;
        }
    };
 
    struct edge {
        int v, w, next;
        edge () {}
        edge (int V, int NEXT, int W = 0) : v(V), next(NEXT), w(W) {}
    }E[NE];
 
    inline void init(int vx) {
        n = vx, size = 0;
        memset(head, -1, sizeof(int) * (vx + 1));
    }
 
    inline void insert(int u, int v, int w) {
        E[size] = edge(v, head[u], w);
        head[u] = size++;
    }
 
    void print() {
        for (int i = 0; i < n; i++) {
            printf("%d: ", i);
            for (int j = head[i]; j != -1; j = E[j].next) {
                printf(" %d", E[j].v);
            }puts("");
        }
    }
 
    int dijkstra(int src, int des) {
        node first, next;
        priority_queue <node> Q;
        for (int i = 0; i <= n; i++) {
            dis[i] = INT_MAX;
            mark[i] = false;
        }
 
        dis[src] = 0;
        Q.push(node(src, 0));
 
        while (!Q.empty()) {
            first = Q.top();
            Q.pop();
            mark[first.v] = true;
 
            for (int i = head[first.v]; i != -1; i = E[i].next) {
                if (mark[E[i].v]) continue;
                next = node(E[i].v, first.dis + E[i].w);
                if (next.dis < dis[next.v]) {
                    dis[next.v] = next.dis;
                    Q.push(next);
                }
            }
        }//while
        return dis[des];
    }//Dij
}G;
 
int main() {
    while (~scanf("%d%d", &n, &m), n || m) {
        G.init(n);
        while (m--) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            G.insert(u - 1, v - 1, w);
            G.insert(v - 1, u - 1, w);
        }
        //G.print();
        printf("%d\n", G.dijkstra(0, n - 1));
    }
    return 0;
}