/**
 * Fernanda Ríos Juárez A01656047
 * Ayetza Yunnuen Infante Garcia A01709011
 *
 *
 * Actividad 3.1 Implementación de "Tries"
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    nix-env -iA nixpkgs.valgrind
 *    valgrind --leak-check=full ./main < TestCases/test01.txt
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main < TestCases/test01.txt
 *
 * en Windows
 * Get-Content test01.txt | ./main
 * test01.txt o test02.txt
 *
 * En macOS
 * clang++ -std=c++11 main.cpp -o main
 *
 **/
#include <iostream>
#include <algorithm>
#include "trie.h"

using namespace std;

int main()
{
    trie T;
    int N = 0;
    int M = 0;
    string palabra = "";
    string prefix = "";

    // Insertar N palabras
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> palabra;
        T.insert(palabra);
    }

    // Recorrido DFS
    T.dfs();

    // Buscar M palabras
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> palabra;
        cout << boolalpha << T.search(palabra) << endl;
    }
    cin >> prefix;

    T.autoComplete(prefix);

    return 0;
}

/*
Referencias
Para poder hacer la implementacion del destructor de la clase trie
(https://stackoverflow.com/questions/49164346/how-to-write-destructor-for-trie-tree)
Para la implementacion del recorrido dfs se uso como guia el siguiente codigo
(https://www.geeksforgeeks.org/trie-display-content/)
*/