//新写一个，这个代码可以顺便AC掉 HDU 1086
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point
{
    double x, y;
};

double Direction(Point p1, Point p2, Point p0 )
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool OnSegment( Point p1, Point p2, Point p0)
{
    if (min(p1.x, p2.x) <= p0.x && p0.x <= max(p1.x, p2.x) &&
            min(p1.y, p2.y) <= p0.y && p0.y <= max(p1.y, p2.y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SegmentsIntersert(Point p1, Point p2, Point p3, Point p4)
{
    double d1 = Direction(p3, p4, p1);
    double d2 = Direction(p3, p4, p2);
    double d3 = Direction(p1, p2, p3);
    double d4 = Direction(p1, p2, p4);

    if (d1 * d2 < 0 && d3 * d4 < 0)
    {
        return true;
    }
    else if (d1 == 0 && OnSegment (p3, p4, p1))
    {
        return true;
    }
    else if (d2 == 0 && OnSegment (p3, p4, p2))
    {
        return true;
    }
    else if (d3 == 0 && OnSegment (p1, p2, p3))
    {
        return true;
    }
    else if (d4 == 0 && OnSegment (p1, p2, p4))
    {
        return false;
    }
    return 0;
}

int main()
{
    int n;
    Point a[105], b[105];
    while (~scanf("%d", &n), n)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%lf %lf %lf %lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (SegmentsIntersert (a[i], b[i], a[j], b[j]))
                {
                    cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}