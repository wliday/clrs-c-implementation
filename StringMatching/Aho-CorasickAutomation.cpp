#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 10001
#define MAXM 51
#define KIND 26
 
struct node {
    int prefix;
    node *fail;
    node *next[26];
    void init() {
        prefix = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
}*que[MAXN * MAXM], trie[MAXN * MAXM],  *root;
 
int cnt;
char keyword[MAXM];
char str[MAXN * 2];
 
void Insert(node *root, char *str) {
    node *ptr = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        if (ptr->next[x] == NULL) {
            trie[cnt].init();
            ptr->next[x] = &trie[cnt++];
        }
        ptr = ptr->next[x];
    }
    ptr->prefix++;
}//insert
 
void Build(node *root) {
    int head = 0, tail = 0;
    root->fail = NULL;
    que[head++] = root;
    while (head != tail) {
        node *tmp = que[tail++];
        node *ptr = NULL;
        for (int i = 0; i < KIND; i++) {
            if (tmp->next[i] != NULL) {
                if (tmp == root) {
                    tmp->next[i]->fail = root;
                } else {
                    ptr = tmp->fail;
                    while (ptr != NULL) {
                        if (ptr->next[i] != NULL) {
                            tmp->next[i]->fail = ptr->next[i];
                            break;
                        }
                        ptr = ptr->fail;
                    }
                    if (ptr == NULL) {
                        tmp->next[i]->fail = root;
                    }
                }//if_else
                que[head++] = tmp->next[i];
            }//if
        }//for(i)
    }//while (head != tail)
}//Build
 
int Query(node *root, char *str) {
    int ret = 0;
    node *ptr = root;
    for (int i = 0; str[i]; i++) {
        int x = str[i] - 'a';
        while (ptr->next[x] == NULL && ptr != root) {
            ptr = ptr->fail;
        }
        ptr = ptr->next[x];
        if (ptr == NULL) {
            ptr = root;
        }
        node *tmp = ptr;
        while (tmp != root && tmp->prefix != -1) {
            ret += tmp->prefix;
            tmp->prefix = -1;
            tmp = tmp->fail;
        }
    }//for(i)
    return ret;
}
 
int main() {
    int cas, n;
    scanf("%d", &cas);
    while (cas--) {
        // head = tail = 0;
        cnt = 0;
        trie[cnt].init();
        root = &trie[cnt++];
 
        scanf("%d%*c", &n);
        while (n--) {
            gets(keyword);
            Insert(root, keyword);
        }
        Build(root);//构造自动机
        scanf("%s", str);
        printf("%d\n", Query(root, str));
    }
    return 0;
}