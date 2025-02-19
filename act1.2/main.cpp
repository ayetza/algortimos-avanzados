#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Función para resolver el problema del cambio utilizando programación dinámica
vector<int> cambioDinamico(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> dp(cambio + 1, INT_MAX); // Tabla DP para almacenar el mínimo número de monedas
    dp[0] = 0; // Caso base: 0 monedas para cambio 0

    // Llenar la tabla DP
    for (int i = 1; i <= cambio; ++i) {
        for (int j = 0; j < n; ++j) {
            if (denominaciones[j] <= i && dp[i - denominaciones[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - denominaciones[j]] + 1);
            }
        }
    }

    // Reconstruir la solución
    vector<int> resultado(n, 0);
    int resto = cambio;
    while (resto > 0) {
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
vector<int> cambioAvaro(const vector<int>& denominaciones, int cambio) {
    int n = denominaciones.size();
    vector<int> resultado(n, 0);
    int resto = cambio;

    // Seleccionar las monedas de mayor a menor denominación
    for (int i = n - 1; i >= 0; --i) {
        if (denominaciones[i] <= resto) {
            resultado[i] = resto / denominaciones[i];
            resto %= denominaciones[i];
        }
    }

    return resultado;
}

int main() {
    int N;
    cin >> N; // Leer el número de denominaciones
    vector<int> denominaciones(N);
    for (int i = 0; i < N; ++i) {
        cin >> denominaciones[i]; // Leer las denominaciones
    }

    int P, Q;
    cin >> P >> Q; // Leer el precio y la cantidad con la que se paga
    int cambio = Q - P; // Calcular el cambio

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