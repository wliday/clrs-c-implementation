#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
 
const int NV = 101;
 
struct Edge {
    int u, v, w;
}gra[NV * NV];
 
int dis[NV];
 
void BellmanFord(int n, int m) {
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dis[gra[j].u] + gra[j].w < dis[gra[j].v]) {
                dis[gra[j].v] = dis[gra[j].u] + gra[j].w;
            }
            if (dis[gra[j].v] + gra[j].w < dis[gra[j].u]) {
                dis[gra[j].u] = dis[gra[j].v] + gra[j].w;
            }
        }
    }
}
 
int main() {
    int n, m;
    while (~scanf("%d %d", &n, &m), n | m) {
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            gra[i].u = u, gra[i].v = v, gra[i].w = w;
        }
        BellmanFord(n, m);
        printf("%d\n", dis[n]);
    }
    return 0;
}