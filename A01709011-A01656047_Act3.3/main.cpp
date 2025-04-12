/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *  Grafos, algoritmos
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

    // Construye un grafo a partir de la consola usando
    // representacion de Lista de adyacencia
    Graph g1;
    g1.readGraph(inputInfo);

    g1.isBipartite();
    return 0;
}

/*
Creditos:
Sesión 13 – Grafos, coloreo con algoritmo Welsh Powell (https://replit.com/join/xrsckjrbiy-ertello)
Check whether a given graph is Bipartite or not (https://www.geeksforgeeks.org/bipartite-graph/)
*/