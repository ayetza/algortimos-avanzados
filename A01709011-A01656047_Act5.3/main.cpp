/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 *   Algoritmo Metaheurístico (Simulated Annealing o Tabu Search)
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
 *    ./main TestCases/test01.txt 1000 5 15
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
    if (argc < 5)
    {
        std::cerr << "Uso: " << argv[0] << " <archivo.txt> <maxIter> <Lmin> <Lmax>" << std::endl;
        return 1;
    }

    // Leer archivo
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: no se pudo abrir el archivo " << argv[1] << std::endl;
        return 1;
    }

    int maxIter = std::stoi(argv[2]);
    int Lmin = std::stoi(argv[3]);
    int Lmax = std::stoi(argv[4]);

    // Solo una declaración de inputInfo
    std::stringstream inputInfo;
    inputInfo << inputFile.rdbuf();
    inputFile.close();

    Graph g1;
    g1.readGraph(inputInfo);

    g1.runMultiple(maxIter, Lmin, Lmax);

    return 0;
}

/*
Creditos
Actividad 5.2 Algoritmo básico de búsqueda local
https://chatgpt.com/share/6838b782-c97c-8000-b312-4b5c84fe0e6e
https://chatgpt.com/share/683a5322-8f78-8000-af63-d8716ddbb49e
https://chatgpt.com/share/683a545d-c9f4-8000-befa-f0372b6ff290

*/