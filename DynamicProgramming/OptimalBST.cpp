/*
e[i][j] :
0.05 0.45 0.90 1.25 1.75 2.75
     0.10 0.40 0.70 1.20 2.00
          0.05 0.25 0.60 1.30
               0.05 0.30 0.90
                    0.05 0.50
                         0.10
 
w[i][j]：
0.05 0.30 0.45 0.55 0.70 1.00
     0.10 0.25 0.35 0.50 0.80
          0.05 0.15 0.30 0.60
               0.05 0.20 0.50
                    0.05 0.35
                         0.10
 
root[i][j]:
1 1 2 2 4
  2 2 2 4
    3 4 5
      4 5
        5
*/
#include<iostream>
#include<cstdio>
#include<climits>
using namespace std;
 
//以5个元素为例
//k1 < k2 < k3 < k4 < k5
double p[6] = {0, 0.15, 0.1, 0.05, 0.1, 0.2};
double q[6] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};
 
double e[10][10], w[10][10];
int  root[10][10];
 
const int N = 5;
 
void OptimalBST(int n) {
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }//for(r)
        }//for(i)
    }//for(l)
}
 
int main() {
     OptimalBST(N);
     puts("e[i][j] :");
     for (int i = 1; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            if (!e[i][j]) {
                printf("     ");
                continue;
            }
            printf("%.2f ", e[i][j]);
        }puts("");
     }
 
     puts("\nw[i][j]：");
     for (int i = 1; i <= 6; i++) {
        for (int j = 0; j <= 5; j++) {
            if (!w[i][j]) {
                printf("     ");
                continue;
            }
            printf("%.2f ", w[i][j]);
        }puts("");
     }
 
     puts("\nroot[i][j]:");
     for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (!root[i][j]) {
                printf("  ");
                continue;
            }
            printf("%d ", root[i][j]);
        }puts("");
     }
     return 0;
}