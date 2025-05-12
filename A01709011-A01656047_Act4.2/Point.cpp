#include "Point.h"
#include <cmath>
#include <algorithm>
#include <stack>

// Complejidad O(1)
Point::Point()
{
    x = 0;
    y = 0;
}

// Complejidad O(1)
Point::Point(double, double)
{
    this->x;
    this->y;
}

// Complejidad O(1)
double Point::getX() const
{
    return this->x;
}

// Complejidad O(1)
double Point::getY() const
{
    return this->y;
}

// Complejidad O(1)
void Point::read(std::istream &input)
{
    input >> x >> y;
}

bool Point::operator<(const Point &other) const
{
    return (y < other.y) || (y == other.y && x < other.x);
}

// Orientacion de 3 puntos
int Point::orientation(const Point &p, const Point &q, const Point &r)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    // si estan alineados (colineales)
    if (val == 0)
    {
        return 0;
    };

    // 1 si forma un giro en sentido horario
    if (val > 0)
    {
        return 1;
    }
    // 2 si forma un giro en sentido antihorario
    else
    {
        return 2;
    }
}

// distancia al cuadrado
int Point::distSq(const Point &p1, const Point &p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// comparador para ordenacion
bool Point::compare(const Point &p0, const Point &a, const Point &b)
{
    int o = orientation(p0, a, b);

    if (o == 0)
    {
        return distSq(p0, a) < distSq(p0, b);
    }

    return (o == 2);
}

// algoritmo Graham
std::vector<Point> Point::convexHull(std::vector<Point> &puntos)
{
    int n = puntos.size();
    if (n < 3)
    {
        return {};
    };

    // encontrar el punto mas bajo
    int minIndx = 0;
    for (int i = 1; i < n; i++)
    {
        if (puntos[i] < puntos[minIndx])
        {
            minIndx = i;
        }
    };

    std::swap(puntos[0], puntos[minIndx]);
    Point p0 = puntos[0];

    // ordenar por angulo polar respecto a p0
    std::sort(puntos.begin() + 1, puntos.end(),
              [&p0](const Point &a, const Point &b)
              { return compare(p0, a, b); });

    // eliminar puntos colineales
    std::vector<Point> filtered;
    filtered.push_back(puntos[0]);
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, puntos[i], puntos[i + 1]) == 0)
            i++;
        filtered.push_back(puntos[i]);
    }

    if (filtered.size() < 3)
    {
        return {};
    };

    // contruir el hull
    std::stack<Point> S;
    S.push(filtered[0]);
    S.push(filtered[1]);
    S.push(filtered[2]);

    for (int i = 3; i < filtered.size(); i++)
    {
        while (S.size() > 1)
        {
            Point top = S.top();
            S.pop();
            Point nextTop = S.top();

            if (orientation(nextTop, top, filtered[i]) == 2)
            {
                S.push(top);
                break;
            }
        }
        S.push(filtered[i]);
    }

    // Convertir stack a vector
    std::vector<Point> hull;
    while (!S.empty())
    {
        hull.push_back(S.top());
        S.pop();
    }

    std::reverse(hull.begin(), hull.end());

    return hull;
}

double Point::perimeter(const std::vector<Point> &hull)
{
    double perim = 0.0;
    int n = hull.size();

    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        perim += sqrt(distSq(hull[i], hull[j]));
    }
    return perim;
}
