/*
运行结果：
_________________________
朴素算法，匹配位置是：7
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
//朴素匹配算法
void NativeStringMatcher(const char *T, const char *P) {
    int n = strlen(T);
    int m = strlen(P);
    for (int j, i = 0; i < n - m; i++) {
        for (j = 0; j < m; j++) {
            if (T[i + j] != P[j]) {
                break;
            }
        }
        if (j == m) {
            printf("朴素算法，匹配位置是：%d\n", i + 1);
        }
    }
}
 
int main() {
    const char *T = "2359023141526739921";
    const char *P = "31415";
    NativeStringMatcher(T, P);
    return 0;
}