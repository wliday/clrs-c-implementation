//可以顺便AC掉  HDU 1392，去年的代码略加修改
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
 
typedef struct {
    double x;
    double y;
}Point;
Point p[110], stack[110];
 
int N, top;
 
double Direction(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}
 
double Dis(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
 
int cmp(const void *a, const void *b) {
    Point c = *(Point *)a;
    Point d = *(Point *)b;
    double k = Direction(p[0], c, d);
    if(k < 0 || (!k && Dis(c, p[0]) > Dis(d, p[0]))) {
        return 1;
    }
    return -1;
}
 
void Convex() {
    for(int i = 1; i < N; i++) {
        Point temp;
        if(p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x)) {
            temp = p[i];
            p[i] = p[0];
            p[0] = temp;
        }
    }
    qsort(p + 1, N - 1, sizeof(p[0]), cmp);
    stack[0] = p[0];
    stack[1] = p[1];
    stack[2] = p[2];
    top =2;
    for(int i = 3; i < N; i++) {
        while(top >= 2 && Direction(stack[top - 1], stack[top], p[i]) <= 0) {
            top--;
        }
        top++;
        stack[top] = p[i];
    }
}
 
int main() {
    while(~scanf("%d", &N), N){
        for(int i = 0; i < N; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        cout.setf(ios::fixed);
        cout.precision(2);
 
        if(N == 1) {
            puts("0.00");
            continue;
        } else if(N == 2) {
            printf("%.2f\n", Dis(p[0], p[1]));
            continue;
        }
 
        Convex();
        double ans = 0;
        for(int i = 0; i < top; i++) {
            ans += Dis(stack[i],stack[i + 1]);
        }
 
        ans += Dis(stack[top], stack[0]);
        printf("%.2f\n", ans);
    }
    return 0;
}