#ifndef _POINT_
#define _POINT_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Point
{
private:
    double x, y;
    bool operator<(const Point &other) const;

public:
    Point();
    Point(double, double);
    double getX() const;
    double getY() const;
    void read(std::istream &input);
    static int orientation(const Point &p, const Point &q, const Point &r);
    static int distSq(const Point &p1, const Point &p2);
    static bool compare(const Point &p0, const Point &a, const Point &b);
    static std::vector<Point> convexHull(std::vector<Point> &puntos);
    static double perimeter(const std::vector<Point> &hull);
};

#endif // _POINT_