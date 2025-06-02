/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   E2. Actividad Integradora 2
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
    // Lee de archivo un grafo, no dirigido, no ponderado
    g1.readGraph(inputInfo);
    // g1.print();
    // std::cout << std::endl;

    // problema 1
    std::cout << "Problem 1" << std::endl;
    int mstCost = g1.Prim();
    std::cout << "MST cost: " << mstCost << std::endl
              << std::endl;

    // problema 2
    std::cout << "Problem 2" << std::endl;
    auto [cost, path] = g1.TSP();
    std::cout << "Path:" << std::endl;
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i] + 1 << " ";
    }
    std::cout << std::endl;
    std::cout << "Optimal cost: " << cost << std::endl;

    // problema 3
    std::cout << std::endl;
    std::cout << "Problem 3" << std::endl;
    std::cout << "Maximum flow from " << g1.getStart() + 1 << " to " << g1.getEnd() + 1 << ": " << g1.Dinic() << std::endl;

    return 0;
}

/*
Referencias:
Para la lectura de los txt de entrada (https://chatgpt.com/share/680c0eff-b3d4-8000-8f19-26129bef3b5a)
Para lectura del grafo no dirigido:
Sesión 11 – Grafos y sus recorridos (https://replit.com/join/lpcvgliwez-ertello)
Para lectura del grafo dirigido: se baso en la lectura de grafo dirigido empleada en la entrega de la Act 3.2
Prim (https://chatgpt.com/share/68127ec8-d904-8000-b44c-8f2398d99c32)
TSP (https://chatgpt.com/share/681573c5-81f4-8000-bdea-b6a946284fab)
Dinic (https://chatgpt.com/share/6815aae3-4c60-8000-9d05-880c7906359c)
*/