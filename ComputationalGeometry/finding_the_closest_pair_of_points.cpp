#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cfloat>
using namespace std;
const int maxn = 10000;
 
struct Point {
    double x, y;
    int index;
}X[maxn], Y[maxn];
double ans;
 
bool Cmpx(const Point &a, const Point &b) {
    return a.x < b.x;
}
 
bool Cmpy(const Point &a, const Point &b) {
    return a.y < b.y;
}
 
double Dis(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
 
//暴力枚举
double ForceMinDis(int a, int b) {
    for (int i = a; i < b; i++) {
        for (int j = i + 1; j <= b; j++) {
            double temp = Dis(X[i], X[j]);
            if (ans > temp) {
                ans = temp;
            }
        }
    }
    return ans;
}
 
double MinDis(int a, int b, Point *Y) {
    if (b - a <= 3) {
        return ForceMinDis(a, b);
    }
 
    int mid = (a + b) >> 1;
    Point *Yleft = new Point[mid - a + 1];
    Point *Yright = new Point[b - mid];
 
    for (int i = 0, j = 0, k = 0; i <= b - a; i++) {
        if (Y[i].index <= mid) {
            Yleft[j++] = Y[i];
        } else {
            Yright[k++] = Y[i];
        }
    }
 
    double left_min = MinDis(a, mid, Yleft);
    double right_min = MinDis(mid + 1, b, Yright);
    ans = min(left_min, right_min);
 
    double line = X[mid].x;
    int ind;
    for (int i = 0, ind = 0; i <= b - a; i++) {
        if (fabs(Y[i].x - line) < ans) {
            Y[ind++] = Y[i];
        }
    }
    for (int i = 0; i < ind - 1; i++) {
        for (int j = i + 1; j <= i + 7 && j < ind; j++) {
            double temp = Dis(Y[i], Y[j]);
            if (ans > temp) {
                ans = temp;
            }
        }
    }
    delete Yleft;
    delete Yright;
    return ans;
}
 
int main() {
    int n, i;
    while (scanf("%d", &n), n) {
        ans = DBL_MAX;
        for (i = 0; i < n; i++) {
            scanf("%lf %lf", &X[i].x, &X[i].y);
        }
        sort(X, X + n, Cmpx);
        for (i = 0; i < n; i++) {
            X[i].index = i;
        }
        memcpy(Y, X, n * sizeof(Point));
        sort(Y, Y + n, Cmpy);
        printf("%lf\n", MinDis(0, n - 1, Y));
    }
    return 0;
}