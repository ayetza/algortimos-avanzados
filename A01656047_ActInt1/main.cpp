/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011

Evidencia 1

Compilacion para debug:
   g++ -std=c++17 -Wall -g -o main main.cpp bitacora.cpp algoritmos.cpp
Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main main.cpp bitacora.cpp algoritmos.cpp
Ejecucion:
    ./main
**/

#include "Bitacora.h"

int main()
{
    generateReport();
    return 0;
}

/*
Referencias
Para la funcion del suffix array y prefix array se emplearon las funciones vistas en clase e implementadas en el
replit del profesor(Sesión 8 – Arreglo de sufijos https://replit.com/join/tqorckiesg-ertello)
Para la funcion del palindromo mas largo se empleo la funcion vista en clase del algoritmo Manacher
e implementada en el replit del profesor
(Sesión 7 – Algoritmos para palíndromos (Naive, Manacher) https://replit.com/join/szakyzniqs-ertello)
Para la funcion de KMP se emplearon las funciones vistas en clase e implementadas en el replit del profesor
(Sesión 6 – Algoritmo KMP https://replit.com/join/ttoptfrszh-ertello)
*/