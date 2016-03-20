/*
运行结果：
————————————————
匹配位置: 1
匹配位置: 12
*/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
 
//伪代码中的fail数组，用fail来表示
int fail[1000];
 
//预处理fail数组
void ComputePrefixFunction(char *P) {
    int m = strlen(P);
    memset(fail, 0, sizeof(fail));
    fail[0] = 0;
    int k = 0;
    for (int i = 2; i <= m; i++) {
        while (k > 0 && P[k] != P[i - 1]) {
            k = fail[k - 1];
        }
        if (P[k] == P[i - 1]) {
            k = k + 1;
        }
        fail[i - 1] = k;
    }
}
 
void KMPMatcher(char *T, char *P) {
    int n = strlen(T);
    int m = strlen(P);
 
    int q = 0;
    for (int i = 1; i <= n; i++) {
        while (q > 0 && P[q] != T[i - 1]) {
            q = fail[q - 1];
        }
 
        if(P[q] == T[i - 1]) {
            q = q + 1;
        }
 
        if(q == m) {
            printf("匹配位置: %d\n", i - m + 1);
            q = fail[q - 1];
        }
    }
}
 
int main() {
    KMPMatcher("123451233211234561234", "12345");
    return 0;
}