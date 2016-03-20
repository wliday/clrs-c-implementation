#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<climits>
using namespace std;
 
const int NV = 16;
const int NE = 2002;
 
struct EK {
    int n, size;
    int head[NV];
    int que[NV], pre[NV], cur[NV];
    int front, rear;
    int maxflow;
 
    struct Edge {
        int v, w, next;
        Edge () {}
        Edge (int V, int NEXT, int W = 0) : v(V), next(NEXT), w(W) { }
    }E[NE];
 
    void init(int x) {
        n = x, size = 0;
        for (int i = 0; i <= n; i++) {
            head[i] = -1;
        }
    }
 
    inline void insert(int u, int v, int w = 0) {
        E[size] = Edge(v, head[u], w);
        head[u] = size++;
        E[size] = Edge(u, head[v], 0);
        head[v] = size++;
    }
 
    int MaxFlow(int src, int des) {
        maxflow = 0;
        while (true) {
            memset(pre, -1, sizeof(pre));
            que[front = rear = 0] = src;
            while (front <=  rear) {
                int u = que[front++];
                for (int i = head[u]; i != -1; i = E[i].next) {
                    int v = E[i].v;
                    if (pre[v] == -1 && E[i].w) {
                        pre[v] = u;
                        cur[v] = i;
                        que[++rear] = v;
                    }
                }//for
                if (pre[des] != -1) {
                    break;
                }
            }//while
            if (pre[des] == -1) {
                break;
            }
            int aug = INT_MAX;
            for (int v = des; v != src; v = pre[v]) {
                aug = min(aug, E[cur[v]].w);
            }
            for (int v = des; v != src; v = pre[v]) {
                E[cur[v]].w -= aug;
                E[cur[v]^1].w += aug;
            }
            maxflow += aug;
        }
        return maxflow;
    }
}G;
 
int main() {
    int cas, n, m;
    int cases = 1;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &m);
        G.init(n);
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if (u == v) {
                continue;
            }
            G.insert(u, v, w);
        }
        printf("Case %d: ", cases++);
        printf("%d\n", G.MaxFlow(1, n));
    }
    return 0;
}