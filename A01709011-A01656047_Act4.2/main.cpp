/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   Algoritmos para construcción de la cubierta convexa
 *
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main < TestCases/test01.txt
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 *
 * Ejecucion en windows:
 *    Get-Content TestCases/test01.txt | ./main
 *
 * En Mac:
 *    ./main < TestCases/test01.txt
 *
 *
 **/
#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"

int main()
{
    int N, C;
    std::cin >> N >> C;
    std::vector<Point> arboles(N);

    for (int i = 0; i < N; ++i)
    {
        arboles[i].read(std::cin);
    }

    std::vector<Point> hull = Point::convexHull(arboles);
    double cost = Point::perimeter(hull) * C;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << cost << std::endl;

    return 0;
}

/*
Creditos
https://chatgpt.com/share/6822690c-2490-8000-b54e-133e637a0ed0
Convex Hull using Graham Scan (https://www.geeksforgeeks.org/convex-hull-using-graham-scan/)
Presentacion vista en clase (sesion21-CubiertasConvexas.pdf)
*/