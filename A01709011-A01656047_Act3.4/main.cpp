/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   Grafos, algoritmos avanzados
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

#include "Graph.h"
#include <iostream>
#include <sstream>

int main()
{
    std::stringstream inputInfo;
    inputInfo << std::cin.rdbuf();
    // Construye un grafo
    Graph g1;
    // Lee de archivo un grafo, dirigido, ponderado
    g1.readGraph(inputInfo);

    g1.maxBPM();

    return 0;
}

/*Creditos
Sesión 11 – Grafos y sus recorridos (https://replit.com/join/lpcvgliwez-ertello)
Maximum Bipartite Matching
(https://www.geeksforgeeks.org/maximum-bipartite-matching/?ref=header_outind)
*/