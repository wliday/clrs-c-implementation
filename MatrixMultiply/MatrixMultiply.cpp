/*
矩阵A为：
——————————————————————————
1 4 9 8
2 5 1 1
5 7 1 2
2 1 8 7
 
矩阵B为:
——————————————————————————
7 0 4 8
4 5 7 1
2 6 4 3
2 6 5 6
 
矩阵A * B = C：
——————————————————————————
57 122 108 87
38 37 52 30
69 53 83 62
48 95 82 83
 
*/
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
 
const int N = 4; 
 
//输出
void print(int n, int C[][N]) {
    puts("——————————————————————————");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }puts("");
    }puts("");
}
 
//加法
void Matrix_Add(int n, int X[][N], int Y[][N], int Z[][N]) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            Z[i][j] = X[i][j] + Y[i][j];
        }
    }
}
 
//减法
void Matrix_Sub(int n, int X[][N], int Y[][N], int Z[][N]) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            Z[i][j] = X[i][j] - Y[i][j];
        }
    }
}
 
//乘法，A * B = C
void Matrix_Multiply(int A[][N], int B[][N], int C[][N]) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            C[i][j] = 0;
            for(int t = 0; t < 2; t++) {
                C[i][j] = C[i][j] + A[i][t]*B[t][j];
            }
        }
    }
}
 
/**
参数n指定矩阵A,B,C的阶数，因为随着递归调用Strassen函数
矩阵A,B,C的阶数是递减的N只是预留足够空间而已
*/
void Strassen(int n, int A[][N], int B[][N], int C[][N]) {
    int A11[N][N], A12[N][N], A21[N][N], A22[N][N];
    int B11[N][N], B12[N][N], B21[N][N], B22[N][N];
    int C11[N][N], C12[N][N], C21[N][N], C22[N][N];
    int M1[N][N], M2[N][N], M3[N][N], M4[N][N], M5[N][N], M6[N][N], M7[N][N];
    int AA[N][N], BB[N][N];
 
    if(n == 2) {   //2-order
        Matrix_Multiply(A, B, C);
    } else {
        //将矩阵A和B分成阶数相同的四个子矩阵，即分治思想。
        for(int i = 0; i < n / 2; i++) {
            for(int j = 0; j < n / 2; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n / 2];
                A21[i][j] = A[i + n / 2][j];
                A22[i][j] = A[i + n / 2][j + n / 2];
 
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n / 2];
                B21[i][j] = B[i + n / 2][j];
                B22[i][j] = B[i + n / 2][j + n / 2];
            }
        }  
 
        //M1 = (A0 + A3) × (B0 + B3)
        Matrix_Add(n / 2, A11, A22, AA);
        Matrix_Add(n / 2, B11, B22, BB);
        Strassen(n / 2, AA, BB, M1);
 
        //M2 = (A2 + A3) × B0
        Matrix_Add(n / 2, A21, A22, AA);
        Strassen(n / 2, AA, B11, M2);
 
        //M3 = A0 × (B1 - B3)
        Matrix_Sub(n / 2, B12, B22, BB);
        Strassen(n / 2, A11, BB, M3);
 
        //M4 = A3 × (B2 - B0)
        Matrix_Sub(n / 2, B21, B11, BB);
        Strassen(n / 2, A22, BB, M4);
 
        //M5 = (A0 + A1) × B3
        Matrix_Add(n / 2, A11, A12, AA);
        Strassen(n / 2, AA, B22, M5);
 
        //M6 = (A2 - A0) × (B0 + B1)
        Matrix_Sub(n / 2, A21, A11, AA);
        Matrix_Add(n / 2, B11, B12, BB);
        Strassen(n / 2, AA, BB, M6);
 
        //M7 = (A1 - A3) × (B2 + B3)
        Matrix_Sub(n / 2, A12, A22, AA);
        Matrix_Add(n / 2, B21, B22, BB);
        Strassen(n / 2, AA, BB, M7);
 
        //C0 = M1 + M4 - M5 + M7
        Matrix_Add(n / 2, M1, M4, AA);
        Matrix_Sub(n / 2, M7, M5, BB);
        Matrix_Add(n / 2, AA, BB, C11);
 
        //C1 = M3 + M5
        Matrix_Add(n / 2, M3, M5, C12);
 
        //C2 = M2 + M4
        Matrix_Add(n / 2, M2, M4, C21);
 
        //C3 = M1 - M2 + M3 + M6
        Matrix_Sub(n / 2, M1, M2, AA);
        Matrix_Add(n / 2, M3, M6, BB);
        Matrix_Add(n / 2, AA, BB, C22);
 
        for(int i = 0; i < n / 2; i++) {
            for(int j = 0; j < n / 2; j++) {
                C[i][j] = C11[i][j];
                C[i][j + n / 2] = C12[i][j];
                C[i + n / 2][j] = C21[i][j];
                C[i + n / 2][j + n / 2] = C22[i][j];
            }
        }
    }
}
 
int main() {
    int A[N][N],B[N][N],C[N][N];
    //对A和B矩阵赋值，下边赋值测试用
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
 
    Strassen(N, A, B, C);
    puts("矩阵A为：");
    print(N, A);
    puts("矩阵B为: ");
    print(N, B);
    puts("矩阵A * B = C：");
    print(N, C);
    return 0;
}