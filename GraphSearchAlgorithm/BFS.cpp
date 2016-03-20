//queue  -->>  Q.front();
//priority_queue ->> Q.top();
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define N 21
 
struct Node {
    int x, y;
};
 
int sx, sy, ex, ey;
int n, m;
char map[N][N];
int mark[N][N];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
 
//判断是否越界
bool Overmap(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) {
        return true;
    }
    else {
        return false;
    }
}
 
int Bfs() {
    memset(mark, 0, sizeof(mark));
    queue<Node> Q;
    Node first, next;
    first.x = sx, first.y = sy;
    mark[sx][sy] = 1;
    Q.push(first);
    int cnt = 0;
    while (!Q.empty()) {
        cnt++;
        first = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++) {
            next.x = first.x + dir[i][0];
            next.y = first.y + dir[i][1];
            if (Overmap(next.x, next.y) || mark[next.x][next.y] || map[next.x][next.y] == '#') {
                continue;
            }
            mark[next.x][next.y] = 1;
            Q.push(next);
        }//for
    }//while
    return cnt;
}