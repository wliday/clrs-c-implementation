#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
 
const int NV = 20005;
const int NE = 50005;
 
struct Tarjan {
    int dfn[NV];//深度优先搜索访问次序
    int low[NV];//能追溯到的最早的次序
    int index, scc, n;//index->索引号，scc->强连通分量个数
    bool instack[NV];//检查是否在栈中
    int root[NV];//记录每个点在第几号强连通分量里
 
    stack<int> S;
    struct Edge{
        int v , next, w;
        Edge () {}
        Edge (int V, int NEXT, int W) : v(V), next(NEXT), w(W){}
    }E[NE];
    int head[NV], size;
 
    inline void init (int nn) {
        n = nn, size = 0;
        memset(head, -1, sizeof(int) * (n + 1));
    }
 
    inline void insert (int u , int v, int w = 1) {
        E[size] = Edge(v, head[u], w);
        head[u] = size++;
    }
 
    void tarjan (int i) {
        dfn[i] = low[i] = ++index;
        instack[i] = true;
        S.push(i);
        for (int k = head[i]; k != -1; k = E[k].next) {
            int v = E[k].v;
            if (!dfn[v]) {
                tarjan(v);
                if(low[v] < low[i]) low[i] = low[v];
            } else if (instack[v] && dfn[v] < low[i])
                low[i] = dfn[v];
        }
        if (dfn[i] == low[i]) {
            scc++;
            int x;
            do{
                x = S.top();
                S.pop();
                instack[x] = false;
                root[x] = scc;
            }while (x != i);
        }
    }
 
    void Solve(){
        while (!S.empty()) S.pop();
        memset(dfn,0,sizeof(dfn));
        index = scc = 0;
        for (int i = 1; i <= n; i++) {
            if(!dfn[i]) tarjan(i);
        }
    }
 
    struct Relation {
        int u,v;
    }re[NE];
}G;
 
int main() {
    int n, m, in[NV], out[NV];
    int cas;
    scanf("%d",&cas);
    while(cas--) {
        scanf("%d%d", &n, &m);
        G.init(n);
        if (m == 0) {
            printf("%d\n", n);
            continue;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d",&a, &b);
            G.insert(a, b);
            G.re[i].u = a, G.re[i].v = b;
        }
 
        G.Solve();
        if (G.scc == 1) {
            puts("0");
            continue;
        }
        for (int i = 1; i <= G.scc; i++) {
            in[i] = out[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            if (G.root[G.re[i].u] == G.root[G.re[i].v]) continue;
            in[ G.root[ G.re[i].u] ]++;
            out[ G.root[G.re[i].v] ]++;
        }
        int cnt_in = 0 , cnt_out = 0;
        for (int i = 1; i <= G.scc; i++ ) {
            if (in[i] == 0) cnt_in++;
            if (out[i] == 0) cnt_out++;
        }
        printf("%d\n", max(cnt_in,cnt_out));
    }
    return 0;
}