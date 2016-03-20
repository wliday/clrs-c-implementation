#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
 
const int NV = 101;
const int NE = 101;
 
struct Topo {
    int n, size;
    int dis[NV], head[NV];
    bool in[NV];
    int indegree[NV];
 
    struct edge {
        int v, w, next;
        edge () {}
        edge (int V, int NEXT, int W = 0) : v(V), next(NEXT), w(W) {}
    }E[NE];
 
    void init(int vx) {
        n = vx, size = 0;
        for (int i = 0; i < n; i++) {
            head[i] = -1;
            indegree[i] = 0;
        }
    }
 
    inline void insert(int u, int v, int w = 0) {
        E[size] = edge(v, head[u], w);
        head[u] = size++;
        indegree[v]++;
    }
 
    bool topo() {
        queue<int> Q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                Q.push(i);
                indegree[i]--;
            }
        }//for(i)
 
        int ans = 0;
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
 
            for (int i = head[x]; i != -1; i = E[i].next) {
                indegree[ E[i].v ]--;
                if (indegree[ E[i].v ] == 0) {
                    Q.push (E[i].v);
                }
            }//for(i)
        }//Q
 
        for (int i = 0; i < n; i++) {
            if (indegree[i] > 0) {
                return false;
            }
        }
        return true;
    }
 
    void print() {
        for (int i = 0; i <= n; i++) {
            printf("%d: ", i);
            for (int j = head[i]; j != -1; j = E[j].next) {
                printf(" %d", E[j].v);
            }puts("");
        }
    }
}G;
 
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m), n) {
        G.init(n);
        int a, b;
        while (m--) {
            scanf("%d%d",&a,&b);
            G.insert(a, b);
        }
 
        if (G.topo()) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}