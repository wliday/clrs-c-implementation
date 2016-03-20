//HDU 1251 代码，字典树模板
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
 
const int MAXN = 100010, MAXM = 11, KIND = 26;
//小写字母->26 ，大小混写->52，大小写+数字->62
int m;
struct node {
    char* s;
    int prefix;
    bool isword;
    node* next[KIND];
    void init() {
        s = NULL;
        prefix = 0;//前缀
        isword = false;
        memset(next, 0, sizeof(next));
    }
}a[MAXN*MAXM], *root;//根
 
void insert(node *root, char *str) {//插入
    node *p = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        p->s = str + i;
        if (p->next[x] == NULL) {
            a[m].init();
            p->next[x] = &a[m++];
        }
        p = p->next[x];
        p->prefix++;
    }
    p->isword = true;
}
 
bool del(node *root, char *str) {//删除
    node *p = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        if (p->next[x] == NULL) {
            return false;
        }
        p = p->next[x];
    }//for(i)
    if (p->isword) {
        p->isword = false;
    } else {
        return false;
    }
    return true;
}
 
bool search(node *root, char* str) {//查找
    node* p = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        if (p->next[x] == NULL) {
            return false;
        }
        p = p->next[x];
    }//for(i)
    return p->isword;
}
 
int count(node *root, char *str) {//统计后缀
    node *p = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        if (p->next[x] == NULL) {
            return 0;
        }
        p = p->next[x];
    }//for(i)
    return p->prefix;
}
 
int main() {
    m = 0;
    a[m].init();
    root = &a[m++];
    char str[MAXM];
 
    while (gets(str), strcmp(str, "")) {
        insert(root, str);
    }
 
    while (gets(str)) {
        printf("%d\n", count(root,str));
    }
}