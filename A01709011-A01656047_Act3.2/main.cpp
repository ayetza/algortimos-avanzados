/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *  Grafos y sus recorridos
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
    // resolucion al problema A
    g1.Dijkstra(inputInfo);
    std::cout << std::endl;
    // resolucion al problema B
    g1.BFS(inputInfo);
    return 0;
}

/*Creditos
Sesión 11 – Grafos y sus recorridos (https://replit.com/join/lpcvgliwez-ertello)
para la implementacion del Dijkstra (https://stackoverflow.com/questions/5493474/graph-implementation-c)
para la modificacion del BFS y solucion del problema B (https://chatgpt.com/share/67e5e520-f56c-8000-831e-b786a552319a)
*/