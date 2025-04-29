/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   Conceptos básicos de geometría computacional
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
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<Point> talleres(N);

    for (int i = 0; i < N; ++i)
    {
        talleres[i].read(cin);
    }

    auto [t1, t2, dist] = Point::closestPair(talleres);

    cout << fixed << setprecision(2);
    cout << "Los dos talleres que mas riesgo representan en Tultepec son "
         << t1.getName() << " y " << t2.getName()
         << " (distancia " << dist << ")" << endl;

    return 0;
}

/*
Creditos
https://chatgpt.com/share/681015a3-e3dc-8000-bee4-099bc1f33eae
Presentacion vista en clase (sesion19-GC-ConceptosBasicos.pdf)
*/