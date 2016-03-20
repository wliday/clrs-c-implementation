/*
运行结果：
_________________________
t1 = 8
t2 = 9
t3 = 3
t4 = 11
t5 = 0
t6 = 1
t7 = 7
匹配位置是：7
t8 = 8
t9 = 4
t10 = 5
t11 = 10
t12 = 11
t13 = 7
伪命中点：13
t14 = 9
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
 
//朴素匹配算法，用于RabinKarp调用
bool NativeStringMatcher(const char *T, const char *P) {
    int n = strlen(T);
    int m = strlen(P);
    for (int j, i = 0; i < n - m; i++) {
        for (j = 0; j < m; j++) {
            if (T[i + j] != P[j]) {
                break;
            }
        }
        if (j == m) {
            return true;
        }
    }
    return false;
}
 
//RabinKarp算法
void RabinKarp(const char *T, const char *P, int d, int q) {
    int n = strlen(T);
    int m = strlen(P);
 
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h *= d;//pow可能会越界，所以用乘法
        if (h >= q) {
            h %= q;
        }
    }
 
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        p = (d * p + (P[i] - '0')) % q;
        t = (d * t + (T[i] - '0')) % q;
    }
 
    for (int i = 0; i < n - m; i++) {
        printf("t%d = %d\n", i + 1, t);
        if (p == t) {
            if (NativeStringMatcher(T + i, P)) {
                printf("匹配位置是：%d\n", NativeStringMatcher(T + i, P) + i);
            } else {
                printf("伪命中点：%d\n", i + 1);
            }
        } 
 
        if (i < n - m) {
            t = (d * (t - h * (T[i] - '0')) + T[i + m] - '0') % q;
            if (t < 0) {
                t += q;
            }
        }
    }
}
 
int main() {
    const char *T = "2359023141526739921";
    const char *P = "31415";
    RabinKarp(T, P, 10, 13);
    return 0;
}