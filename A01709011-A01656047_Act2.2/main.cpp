/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011


 Implementación de Sufix Array

Compilacion para debug:
    g++ -std=c++17 -Wall -g -o main *.cpp
 Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main *.cpp
Ejecucion:
    ./main
También puede ejecutarse únicamente haciendo click en el botón de "Run"

Compilacion
g++ -std=c++11 main.cpp -o main.exe

En macOS
clang++ -std=c++11 main.cpp -o main


 **/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// O(n log n)
vector<pair<string, int>> createSuffixArray(string S)
{
    string T = S + "$";
    int n = T.length();
    map<string, int> Map;
    vector<pair<string, int>> suffix;
    // crear sufijos y ordenarlos
    string sub = "";
    for (int i = n - 1; i >= 0; i--)
    {
        sub = T[i] + sub;
        Map[sub] = i + 1; // hacerlo 1 basado en vez de 0 basado
    }
    // recuperar los valor del map ya ordenados
    for (auto x : Map)
        suffix.push_back(make_pair(x.first, x.second));
    return suffix;
}

int main()
{
    string text;
    cin >> text;
    vector<pair<string, int>> suffixArray(createSuffixArray(text));
    for (int i = 0; i < suffixArray.size(); i++)
    {
        cout << suffixArray[i].first << " " << suffixArray[i].second << endl;
    }
    cout << endl;
}

/*
Referencias
Para la funcion del suffix array se empleo la funcion vista en clase e implementada en el
replit del profesor(Sesión 8 – Arreglo de sufijos https://replit.com/join/tqorckiesg-ertello)
*/