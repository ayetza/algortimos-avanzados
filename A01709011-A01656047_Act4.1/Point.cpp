#include "Point.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Point::Point() : name(""), x(0), y(0) {}

Point::Point(std::string n, double xCoord, double yCoord) : name(n), x(xCoord), y(yCoord) {}

double Point::getX() const { return x; }
double Point::getY() const { return y; }
std::string Point::getName() const { return name; }

void Point::read(std::istream &input)
{
    input >> name >> x >> y;
}

double Point::distance(const Point &p1, const Point &p2)
{
    double diffX = p2.getX() - p1.getX();
    double diffY = p2.getY() - p1.getY();
    return std::sqrt(diffX * diffX + diffY * diffY);
}

bool Point::compareX(const Point &a, const Point &b)
{
    return a.getX() < b.getX();
}

bool Point::compareY(const Point &a, const Point &b)
{
    return a.getY() < b.getY();
}

std::tuple<Point, Point, double> Point::bruteForce(std::vector<Point> &points)
{
    double minDist = 1e18;
    Point p1, p2;
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double d = distance(points[i], points[j]);
            if (d < minDist)
            {
                minDist = d;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return {p1, p2, minDist};
}

std::tuple<Point, Point, double> Point::closestPairRec(std::vector<Point> &Px, std::vector<Point> &Py)
{
    int n = Px.size();
    if (n <= 3)
    {
        return bruteForce(Px);
    }

    int mid = n / 2;
    Point midPoint = Px[mid];

    std::vector<Point> Pyl, Pyr;
    for (auto &p : Py)
    {
        if (p.getX() <= midPoint.getX())
            Pyl.push_back(p);
        else
            Pyr.push_back(p);
    }

    std::vector<Point> leftPx(Px.begin(), Px.begin() + mid);
    std::vector<Point> rightPx(Px.begin() + mid, Px.end());

    auto [p1l, p2l, dl] = closestPairRec(leftPx, Pyl);
    auto [p1r, p2r, dr] = closestPairRec(rightPx, Pyr);

    double d = std::min(dl, dr);
    Point best1 = dl <= dr ? p1l : p1r;
    Point best2 = dl <= dr ? p2l : p2r;

    std::vector<Point> strip;
    for (auto &p : Py)
    {
        if (std::abs(p.getX() - midPoint.getX()) < d)
            strip.push_back(p);
    }

    int stripSize = strip.size();
    for (int i = 0; i < stripSize; ++i)
    {
        for (int j = i + 1; j < stripSize && (strip[j].getY() - strip[i].getY()) < d; ++j)
        {
            double dist = distance(strip[i], strip[j]);
            if (dist < d)
            {
                d = dist;
                best1 = strip[i];
                best2 = strip[j];
            }
        }
    }

    return {best1, best2, d};
}

std::tuple<Point, Point, double> Point::closestPair(std::vector<Point> &points)
{
    std::vector<Point> Px = points;
    std::vector<Point> Py = points;

    std::sort(Px.begin(), Px.end(), compareX);
    std::sort(Py.begin(), Py.end(), compareY);

    return closestPairRec(Px, Py);
}
