/*
貌似是最简单的DFS
核心是DFS：
*/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
 
bool prime[41] = {0,
0, 1, 1, 0, 1, 0, 1, 0, 0, 0,
1, 0, 1, 0, 0, 0, 1, 0, 1, 0,
0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
1, 0, 0, 0, 0, 0, 1, 0, 0, 0,};//0~40
int num[21], mark[21];
int n;
 
void Dfs(int t) {
    if (t == n && prime[num[0] + num[n - 1]]) {//如果到最后，输出结果
        printf("%d", num[0]);
        for (int i = 1; i < n; i++) {
            printf(" %d", num[i]);
        }
        puts("");
    } else {
        for (int i = 2; i <= n; i++) {//每次都从头到尾搜一遍有没有符合要求的
            if (!mark[i] && prime[i + num[t - 1]]) {//如果条件成立
                mark[i] = 1;//标记
                num[t] = i;
                Dfs(t + 1);
                mark[i] = 0;//递归返回是撤销标记
            }
        }
    }//else
}//dfs
 
int main() {
    int cases = 1;
    num[0] = 1;
    while (~scanf("%d", &n)) {
        memset(mark, 0, sizeof(mark));
        printf("Case %d:\n", cases++);
        Dfs(1);
        puts("");
    }
    return 0;
}