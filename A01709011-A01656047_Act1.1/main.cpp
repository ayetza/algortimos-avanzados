/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011


Implementación de la técnica de programación divide y vencerás

Compilacion para debug:
    g++ -std=c++17 -Wall -g -o main *.cpp
 Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main *.cpp
Ejecucion:
    ./main
También puede ejecutarse únicamente haciendo click en el botón de "Run"

Compilacion
g++ -std=c++11 main.cpp -o mergesort

Despues de compilar ejecutar el programa
Get-Content in1.txt | ./mergesort
in1.txt o in2.txt o in3.txt

En macOS
clang++ -std=c++11 main.cpp -o mergesort

Despues de compilar ejecutar el programa
./mergesort < in1.txt o in2.txt o in3.txt

 **/

#include "mergesort.h"
#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<double> arr(N);

    for (int i = 0; i < N; ++i)
    {
        std::cin >> arr[i];
    }

    mergeSort(arr, 0, N - 1);

    for (const double &num : arr)
    {
        std::cout << num << std::endl;
    }

    return 0;
}

// créditos
// El código base de la actividad fue basado en uno realizado en la materia TC1031
// Programación de estructuras de datos y algoritmos fundamentales con nombre de Sort-algorythms3