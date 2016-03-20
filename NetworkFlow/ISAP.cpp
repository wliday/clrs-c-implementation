#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
using namespace std;
 
const int NV = 16;
const int NE = 2002;
 
struct ISAP {
    int n, size;
    int head[NV];
    int dis[NV], gap[NV], pre[NV], cur[NV];
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
        gap[0] = n;
        for (int i = 0; i <= n; i++) {
            dis[i] = gap[i] = 0;
        }
        for (int i = 0; i <= n; i++) {
            cur[i] = head[i];
        }
        int u = pre[src] = src;
        int aug = -1;
        while (dis[src] < n) {//结束条件1
loop:
            for (int &i = cur[u]; i != -1; i = E[i].next) {
                int v = E[i].v;
                if (E[i].w && dis[u] == dis[v] + 1) {
                    aug = min(aug, E[i].w);
                    pre[v] = u;
                    u = v;
                    if (v == des) {//找到一条增广路，更新
                        maxflow += aug;
                        // //修改残余网络
                        for (u = pre[u]; v != src; v = u, u = pre[u]) {
                            E[cur[u]].w -= aug;//正向边
                            E[cur[u]^1].w += aug;//反向边
                        }
                        aug = INT_MAX;
                    }//if
                    goto loop;
                }//for
            }//for
            //寻找最小的距离标号，并修改当前点    为最小的标号+1
            int mdis = n;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].v;
                if (E[i].w && mdis > dis[v]) {
                    cur[u] = i;
                    mdis = dis[v];
                }
            }//for
 
            //GAP 优化 断层则跳出 结束条件2
            if ((--gap[dis[u]]) == 0) {
                break;
            }
            gap[dis[u] = mdis + 1]++;//将拥有该标号的数量加1
            u = pre[u];//当前节点 迁移一个
        }//while
        return maxflow;
    }//ISAP
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