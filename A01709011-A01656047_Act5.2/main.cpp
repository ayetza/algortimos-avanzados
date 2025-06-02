/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   Algoritmo básico de búsqueda local
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
 * Ejemplo de ejecucion en windows:
 *    Get-Content TestCases/cycle20.txt | ./main.exe 100
 *
 *
 *
 *
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <cmath>
#include "Graph.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <archivo.txt> <parametro>" << std::endl;
        return 1;
    }

    int k = std::stoi(argv[1]);
    int numRuns = 10;

    std::stringstream inputInfo;
    inputInfo << std::cin.rdbuf();

    Graph g1;
    g1.readGraph(inputInfo);
    g1.runMultiple(k, numRuns);

    return 0;
}

/*
Creditos
Sesión 11 – Grafos y sus recorridos (https://replit.com/join/lpcvgliwez-ertello)
Función main y argumentos de la línea de comandos
(https://learn.microsoft.com/es-es/cpp/cpp/main-function-command-line-args?view=msvc-170)
Hill Climbing in Artificial Intelligence
(https://www.geeksforgeeks.org/introduction-hill-climbing-artificial-intelligence/)
How to generate a vector with random values in C++?
(https://www.geeksforgeeks.org/how-to-generate-a-vector-with-random-values-in-c/)
Measure execution time of a function in C++
(https://www.geeksforgeeks.org/measure-execution-time-function-cpp/)
https://chatgpt.com/share/68311806-9a54-8000-907a-01596211fd19
https://chatgpt.com/share/68313113-0d9c-8000-ba52-b9de93af3c56
https://chatgpt.com/share/68314aa6-c654-8000-887f-63cf10f0959d
*/