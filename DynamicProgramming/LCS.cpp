#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
 
const int N = 1002;
const bool left_side = 0;//代表朝左箭头
const bool up = 1;//代表朝上箭头
int c[N][N], b[N][N];
char str1[N], str2[N];
int len1, len2;
 
// str1 = {A, B, C, B, D, A, B}
// str2 = {B, D, C, A, B, A}
int LCSLength(int b[][1002], int c[][1002]) {
    for (int i = 0; i < len1; i++) {
        c[i][0] = 0;
    }
    for (int i = 0; i < len2; i++) {
        c[0][i] = 0;
    }
 
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (str1[i] == str2[j]) {
                c[i + 1][j + 1] = c[i][j] + 1;
                b[i + 1][j + 1] = 0;
            } else {
                if (c[i][j + 1] >= c[i + 1][j]) {
                    c[i + 1][j + 1] = c[i][j + 1];
                    b[i + 1][j + 1] = 2;
                } else {
                    c[i + 1][j + 1] = c[i + 1][j];
                    b[i + 1][j + 1] = 1;
                }
            }//if
        }//for(j)
    }//for(i)
    return c[len1][len2];
}
 
void PrintLCS(int b[][1002], int i, int j) {
    if (i == 0 || j == 0) {
        return ;
    }
    if (b[i][j] == left_side) {
        PrintLCS(b, i - 1, j - 1);
        printf("%c", str1[i - 1]);
    } else if (b[i][j] == up) {
        PrintLCS(b, i - 1, j);
    } else {
        PrintLCS(b, i, j - 1);
    }
}
 
//打印辅助函数
void Print(int aa[][1002]) {
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            cout << aa[i][j] << ' ';
            }cout << endl;
   }
}
 
int main() {
    while (~scanf("%s %s", str1, str2)) {
        len1 = strlen(str1);
        len2 = strlen(str2);
        int res = LCSLength(b, c);
        printf("LCS长度为：%d\n", res);
        printf("DP过程：\n");
        Print(c);
 
        printf("LCS为： ");
        PrintLCS(b, len1, len2);
    }
    return 0;
}
 
/*
ABCBDAB BDCABA
 
LCS长度为：4
DP过程：
0 0 0 0 0 0 0
0 0 0 0 1 1 1
0 1 1 1 1 2 2
0 1 1 2 2 2 2
0 1 1 2 2 3 3
0 1 2 2 2 3 3
0 1 2 2 3 3 4
0 1 2 2 3 4 4
LCS为： BDAB
 
*/