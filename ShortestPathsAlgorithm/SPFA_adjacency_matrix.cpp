#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
 
const int NV = 101;
const int inf = INT_MAX >> 1;
 
int m, n;
int map[NV][NV];
int dis[NV];
bool mark[NV];
 
int Spfa (int src, int des) {
    for (int i = 0; i <= n; i++) {
        mark[i] = false;
        dis[i] = inf;
    }
    queue<int> Q;
    mark[src] = true;
    dis[src] = 0;
 
    Q.push(src);
    while (!Q.empty()) {
        int first = Q.front();
        Q.pop();
        mark[first] = false;
        for (int i = 1; i <= n; i++) {
            if (dis[first] + map[first][i] < dis[i]) {
                if (!mark[i]) {
                    Q.push(i);
                }
                dis[i] = dis[first] + map[first][i];
                mark[i] = true;
            }
        }//for
    }//while
    return  dis[des];
}
 
int main() {
    while (~scanf("%d%d", &n, &m), n | m) {
        int a, b, c;
        for (int i = 1; i <= n; i++) {
            map[i][i] = inf;
            for (int j = i + 1; j <= n; j++) {
                map[i][j] = map[j][i] = inf;
            }
        }
        while (m--) {
            scanf("%d%d%d", &a, &b, &c);
            map[a][b] = map[b][a] = c;
        }
        printf("%d\n", Spfa(1, n));
    }
    return 0;
}