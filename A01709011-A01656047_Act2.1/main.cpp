/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011


 Implementación de Hash String

Compilacion para debug:
    g++ -std=c++17 -Wall -g -o main *.cpp
 Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main *.cpp
Ejecucion:
    ./main
También puede ejecutarse únicamente haciendo click en el botón de "Run"

Compilacion
g++ -std=c++11 main.cpp -o main.exe

Despues de compilar ejecutar el programa en Windows
Get-Content input0.txt | .\main.exe


En macOS
clang++ -std=c++11 main.cpp -o main

Despues de compilar ejecutar el programa
./main < in1.txt o in2.txt o in3.txt

 **/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

long long prfh(const string &S);

// Complejidad O(m)
void hashingString(const string &fileName, int n)
{
    ifstream file(fileName);
    if (!file.is_open()) // O(1)
    {
        throw runtime_error("No se pudo abrir el archivo");
    }

    // comprobar que n es multiplo de 4 entre 4 y 64
    if (n < 4 || n > 64 || n % 4 != 0) // O(1)
    {
        throw runtime_error("n debe ser múltiplo de 4 entre 4 y 64");
    }

    // leer contenido del archivo
    string content;
    char c;
    while (file.get(c)) // O(m)
    {
        content += c;
    }
    file.close();

    // rellenar con 'a' segun sea necesario
    int falta = (n - (content.size() % n)) % n; // O(1)
    content.append(falta, 'a');

    // dividir en columnas de n caracteres
    vector<string> col;
    for (size_t i = 0; i < content.size(); i += n) // O(m/n)
    {
        col.push_back(content.substr(i, n));
    }

    // generar la cadena hexadecimal
    string result;
    // O(m/n) * O(n) = O(m)
    for (const string &column : col) // O(m/n)
    {
        long long hash = prfh(column); // O(n)
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << hash; // O(1)
        result += ss.str();                                        // O(1)
    }

    cout << result;
}

// polynomial rolling hash function que suma valores ASCII
// Complejidad O(n)
long long prfh(const string &S)
{
    const int m = 256;
    long long valorHash = 0;
    for (char c : S)
    {
        valorHash = (valorHash + static_cast<unsigned char>(c)) % m;
    }
    return valorHash;
}

int main()
{
    string fileName;
    int n;
    cin >> fileName >> n;

    hashingString(fileName, n);

    return 0;
}

/* Creditos
Se empleo parte del codigo visto en clase para polynomial rolling hashing function
ademas de ayuda de OpenAI para la parte del ACII, el manejo del archivo y la correccion de errores
para, de esta forma, poder tener una mejor comprension del problema y de la aplicacion de funciones hash
*/