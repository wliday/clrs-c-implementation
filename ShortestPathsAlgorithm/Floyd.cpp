#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<climits>
 
const int N = 101;
int map[N][N];
 
void Floyd(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if((map[i][k] != INT_MAX) && (map[k][j] != INT_MAX)
                    &&(map[i][j] > map[i][k] + map[k][j] || map[i][j] == INT_MAX)) {
                        map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }
}
 
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m), n | m) {
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                map[i][j] = map[j][i] = INT_MAX;
            }
        }
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            map[u][v] = map[v][u] = w;
        }
        Floyd(n);
        printf("%d\n",map[1][n]);
    }
    return 0;
}