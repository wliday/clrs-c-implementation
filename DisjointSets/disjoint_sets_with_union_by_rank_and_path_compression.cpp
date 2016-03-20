#include<iostream>
#include<cstdio>
using namespace std;
#define N 1005
 
//结点ADT
struct Node{
    int parent;
    int weight;
};
Node village[N];
 
//路径压缩，查找
int Find(int n) {//r->root
    int r = n;
    while (r != village[r].parent) {//寻找根节点
        r = village[r].parent;
    }
    int x = n, y;
    while (x != r) {//压缩路径，全部赋值为根节点的值
        y = village[x].parent;
        village[x].parent = r;
        x = y;
    }
    return r;
}
 
//按秩合并
void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) {//如果是同一个集合就不用合并
        return ;
    }
    //按秩合并
    if (village[a].weight >= village[b].weight) {
        village[b].parent = a;
        village[a].weight += village[b].weight;
    } else {
        village[a].parent = b;
        village[b].weight += village[a].weight;
    }
}//Union
 
int main() {
    int n, m;
    while (~scanf("%d", &n), n) {
        //构造集合
        for (int i = 1; i <= n; i++) {
            village[i].parent = i;
            village[i].weight = 1;
        }
 
        scanf("%d", &m);
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            Union(a, b);
        }
 
        //计算集合数
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (village[i].parent == i) {
                res++;
            }
        }
        printf("%d\n", res - 1);
    }
    return 0;
}