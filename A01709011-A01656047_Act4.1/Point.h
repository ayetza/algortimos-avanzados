#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <tuple>

class Point
{
private:
    std::string name;
    double x, y;

public:
    Point();
    Point(std::string n, double xCoord, double yCoord);

    double getX() const;
    double getY() const;
    std::string getName() const;

    void read(std::istream &input);

    static double distance(const Point &p1, const Point &p2);
    static bool compareX(const Point &a, const Point &b);
    static bool compareY(const Point &a, const Point &b);

    static std::tuple<Point, Point, double> bruteForce(std::vector<Point> &points);
    static std::tuple<Point, Point, double> closestPairRec(std::vector<Point> &Px, std::vector<Point> &Py);
    static std::tuple<Point, Point, double> closestPair(std::vector<Point> &points);
};

#endif
