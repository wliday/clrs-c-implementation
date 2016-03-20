/*Kosaraju算法解法，加多少条边，可以让图变成强连通图*/
/*
2
4 0
3 2
1 2
1 3
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
 
const int N = 20050;
 
vector<int> v1[N], v2[N];
int order[N], id[N];
int in[N], out[N];
bool mark[N];
int n, m, cnt, scc;
 
void DFS1 (int x) {//正向深搜一遍
    int size = v1[x].size();
    mark[x] = true;
    for (int i = 0; i < size; i++) {
        if (!mark[v1[x][i]]) {
            DFS1(v1[x][i]);
        }
    }
    order[cnt++] = x;//sample，储存的顺序是 1 2 5 3 4
}
 
void DFS2(int x) {//反向深搜一遍，目的是找到没有入度的点
    int size = v2[x].size();
    mark[x] = true;
    id[x] = scc;//id[1 …… 5] = {0 0 1 2 0}
    for (int i = 0; i < size; i++) {
        if (!mark[v2[x][i]]) {
            DFS2(v2[x][i]);
        }
    }
}
 
void Kosaraju() {
    cnt = 0;
    memset(mark, false, sizeof(mark));
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            DFS1(i);
        }
    }
    memset(mark, false, sizeof(mark));
    scc = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (mark[order[i]]) continue;
        DFS2(order[i]);
        scc++;
    }
}
 
int main() {
    int size, ans1, ans2;
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &m);
        if (m == 0) {
            printf("%d\n", n);
            continue;
        }
        for (int i = 0; i < n; i++) {
            v1[i].clear();
            v2[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            v1[a - 1].push_back(b - 1);
            v2[b - 1].push_back(a - 1);
        }
 
        Kosaraju();
 
        if (scc == 1) {
            puts("0");
            continue;
        }//只有一个强连通图，只要一个点就可以到达所有的点，且不用加边
 
        for (int i = 0; i < n; i++) {
            in[i] = out[i] = 0;
        }
 
        for (int i = 0; i < n; i++) {
            size = v1[i].size();
            for (int j = 0; j < size; j++) {
                if (id[i] == id[v1[i][j]]) continue;
                out[ id[i] ]++;//0强连通图出度+1
                in[ id[v1[i][j]] ]++;//另外一个强连通图入度+1
            }
        }
 
        ans1 = ans2 = 0;
        for (int i = 0; i < scc; i++) {
            if (in[i] == 0) ans1++;
            if (out[i] == 0) ans2++;
        }
        printf("%d\n", max(ans1, ans2));
    }
    return 0;
}