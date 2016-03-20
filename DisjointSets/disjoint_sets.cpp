#include<iostream>
#include<cstdio>
using namespace std;
 
int parent[1002];
 
//查找集合
int Find(int x){
    while (parent[x] != x) {
        x = parent[x];
    }
    return x;
}
 
//合并操作
void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if(x != y) {
        parent[x] = y;
    }
}
 
int main() {
    int n, m;
    while(~scanf("%d", &n), n) {
        //建立集合
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
 
        scanf("%d", &m);
        while (m--) {
            int x, y;
            scanf("%d %d", &x, &y);
            Union(x, y);
        }
 
        //计算不相交集合数
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(parent[i] == i) {
                cnt ++;
            }
        }
        printf("%d\n", cnt - 1);
    }
}