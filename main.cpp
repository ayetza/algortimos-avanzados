/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011


Implementación de la técnica de programación programación dinámica y algoritmos avaros

Compilacion para debug:
    g++ -std=c++17 -Wall -g -o main *.cpp
 Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main *.cpp
Ejecucion:
    ./main
También puede ejecutarse únicamente haciendo click en el botón de "Run"

Compilacion
g++ -std=c++11 main.cpp 

Despues de compilar ejecutar el programa
Get-Content in1.txt | ./main
in1.txt o in2.txt o in3.txt

En macOS
clang++ -std=c++11 main.cpp -o main

Despues de compilar ejecutar el programa
./main < in1.txt o in2.txt o in3.txt

 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

//complejidad O(cambio*n)
// Función para resolver el problema del cambio utilizando programación dinámica
vector<int> cambioDinamico(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> dp(cambio + 1, INT_MAX); 
    dp[0] = 0; 

    // Llenar la tabla DP
    for (int i = 1; i <= cambio; ++i) { //O(cambio)
        for (int j = 0; j < n; ++j) { //O(n)
            if (denominaciones[j] <= i && dp[i - denominaciones[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - denominaciones[j]] + 1); //O(1)
            }
        }
    }

    // Reconstruir la solución
    vector<int> resultado(n, 0);
    int resto = cambio;
    while (resto > 0) { //O(cambio)
        for (int j = n - 1; j >= 0; --j) { 
            if (denominaciones[j] <= resto && dp[resto] == dp[resto - denominaciones[j]] + 1) {
                resultado[j]++;
                resto -= denominaciones[j];
                break;
            }
        }
    }

    return resultado;
}

// Función para resolver el problema del cambio utilizando un algoritmo avaro
//Complejidad O(n)
vector<int> cambioAvaro(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> resultado(n, 0);
    int resto = cambio;

    // Seleccionar las monedas de mayor a menor denominación
    for (int i = n - 1; i >= 0; --i) { //O(n)
        if (denominaciones[i] <= resto) {
            resultado[i] = resto / denominaciones[i];
            resto %= denominaciones[i];
        }
    }

    return resultado;
}

int main() {
    int N;
    cin >> N; 
    vector<int> denominaciones(N);
    for (int i = 0; i < N; ++i) {
        cin >> denominaciones[i]; 
    }

    int P, Q;
    cin >> P >> Q; 
    int cambio = Q - P; 

    if (cambio < 0) {
        cout << "El pago es insuficiente." << endl;
        return 0;
    }

    // Ordenar las denominaciones de menor a mayor
    sort(denominaciones.begin(), denominaciones.end());

    // Resolver con programación dinámica
    vector<int> resultadoDinamico = cambioDinamico(denominaciones, cambio);
    cout << "Programación Dinámica:" << endl;
    for (int i = N - 1; i >= 0; --i) {
        cout << resultadoDinamico[i] << endl;
    }

    // Resolver con algoritmo avaro
    vector<int> resultadoAvaro = cambioAvaro(denominaciones, cambio);
    cout << "Algoritmo Avaro:" << endl;
    for (int i = N - 1; i >= 0; --i) {
        cout << resultadoAvaro[i] << endl;
    }

    return 0;
}

// Créditos:
// Parte de la implementacion de la solución con programación dinámica fue implementada
// con ayuda de ideas dadas por OpenAI con la finalidad de entender mejor esta misma
// y llegar a una solución óptima

