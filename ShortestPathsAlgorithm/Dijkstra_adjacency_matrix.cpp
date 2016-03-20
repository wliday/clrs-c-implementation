/*邻接矩阵 +  Dijkstra求最短路*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<climits>
using namespace std;
 
const int NV = 102;
const int inf = INT_MAX >> 1;
 
int map[NV][NV];
bool mark[NV];
int dis[NV];
int n, m;
 
void Dijkstra(int src) {
    for (int i = 0; i < n; i++) {
        dis[i] = map[src][i];
        mark[i] = false;
    }
    dis[src] = 0;
    mark[src] = true;
    for (int i = 1; i < n; i++) {
        int minn = inf;
        int k = src;
        for (int j = 0; j < n; j++) {
            if (!mark[j] && dis[j] < minn) {
                k = j;
                minn = dis[j];
            }
        }
        mark[k] = true;
        for (int j = 0; j < n; j++) {
            int tmp = map[k][j] + dis[k];
            if (!mark[j] && tmp < dis[j]) {
                dis[j] = tmp;
            }
        }
    }
}
 
int main() {
    while (~scanf("%d%d", &n, &m), n || m) {
        for (int i = 0; i < n; i++) {
            map[i][i] = inf;
            for (int j = i + 1; j < n; j++) {
                map[i][j] = inf;
                map[j][i] = inf;
            }
        }
 
        while (m--) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if (map[u - 1][v - 1] > w) {
                map[u - 1][v - 1] = w;
                map[v - 1][u - 1] = w;
            }
        }
        Dijkstra(0);
        printf("%d\n", dis[n - 1]);
    }
    return 0;
}