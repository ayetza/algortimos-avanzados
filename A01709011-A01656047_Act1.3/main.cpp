/**
Fernanda Ríos Juárez A01656047
Ayetza Yunnuen Infante Garcia A01709011


Implementación de la técnica de programación backtracking y ramificación y poda

Compilacion para debug:
    g++ -std=c++17 -Wall -g -o main *.cpp
 Compilacion para ejecucion:
    g++ -std=c++17 -O3 -o main *.cpp
Ejecucion:
    ./main
También puede ejecutarse únicamente haciendo click en el botón de "Run"

Compilacion
g++ -std=c++11 main.cpp

Despues de compilar ejecutar el programa en Windows
Get-Content in1.txt | ./main
in1.txt o in2.txt o in3.txt

En macOS
clang++ -std=c++11 main.cpp -o main

Despues de compilar ejecutar el programa
./main < in1.txt o in2.txt o in3.txt

 **/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

//---------------Backtracking--------------------

// Función para verificar si una celda es válida
// O(1)
bool isValid(int row, int col, int N, int M,
             vector<vector<int>> &labyrinth, vector<vector<bool>> &visited)
{
    return row >= 0 && col >= 0 && row < N && col < M && labyrinth[row][col] == 1 && !visited[row][col];
}

// Complejidad O(n*m)
//  Función recursiva para encontrar el camino usando backtracking
bool findPath(int row, int col, int N, int M, vector<vector<int>> &labyrinth,
              vector<vector<int>> &answ, vector<vector<bool>> &visited)
{
    // Si llegamos a la meta, retornamos true
    // O(1)
    if (row == N - 1 && col == M - 1)
    {
        answ[row][col] = 1;
        return true;
    }

    // Verificamos si la celda actual es válida
    // O(1)
    if (isValid(row, col, N, M, labyrinth, visited))
    {
        // Marcamos la celda como visitada y parte de la solución
        visited[row][col] = true;
        answ[row][col] = 1;

        // Movimientos posibles: abajo, derecha, arriba, izquierda
        int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Exploramos todas las direcciones
        // O(1)
        for (int i = 0; i < 4; i++)
        {
            int newRow = row + dir[i][0];
            int newCol = col + dir[i][1];

            // Llamada recursiva para explorar la nueva celda
            // O(n*m)
            if (findPath(newRow, newCol, N, M, labyrinth, answ, visited))
            {
                return true;
            }
        }

        // Si no se encuentra una solución, desmarcamos la celda (backtracking)
        answ[row][col] = 0;
        visited[row][col] = false;
    }

    return false;
}

//--------------------------------B&B-----------------------------------------

// Estructura para almacenar las celdas en la cola de prioridad
// O(1)
struct Cell
{
    int x, y;
    vector<pair<int, int>> path;
};

// Complejidad O(n*m)
// Función para encontrar el camino usando ramificación y poda
vector<pair<int, int>> findPathBandB(vector<vector<int>> &labyrinth, int N, int M)
{
    queue<Cell> q;
    q.push({0, 0, {{0, 0}}});

    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // O(n*m)
    while (!q.empty())
    {
        Cell current = q.front();
        q.pop();

        int x = current.x;
        int y = current.y;

        // Si llegamos a la meta, retornamos el camino
        if (x == N - 1 && y == M - 1)
        {
            return current.path;
        }

        // Movimientos posibles: abajo, derecha, arriba, izquierda
        int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // O(1)
        for (int i = 0; i < 4; i++)
        {
            int newX = x + dir[i][0];
            int newY = y + dir[i][1];

            if (newX >= 0 && newY >= 0 && newX < N && newY < M && labyrinth[newX][newY] == 1 && !visited[newX][newY])
            {
                visited[newX][newY] = true;
                vector<pair<int, int>> newPath = current.path;
                newPath.push_back({newX, newY});
                q.push({newX, newY, newPath});
            }
        }
    }

    return {};
}

// Función para imprimir la solución
void printSolution(const vector<vector<int>> &sol)
{
    for (const auto &row : sol)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> labyrinth(N, vector<int>(M));
    vector<vector<int>> answ(N, vector<int>(M, 0));
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // Leer matriz
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> labyrinth[i][j];
        }
    }

    // Solución usando backtracking
    if (findPath(0, 0, N, M, labyrinth, answ, visited))
    {
        cout << "Solución con Backtracking:" << endl;
        printSolution(answ);
    }
    else
    {
        cout << "No hay solución con Backtracking" << endl;
    }

    cout << endl;

    // Solución usando ramificación y poda
    vector<pair<int, int>> path = findPathBandB(labyrinth, N, M);
    if (!path.empty())
    {
        vector<vector<int>> solBandB(N, vector<int>(M, 0));
        for (const auto &p : path)
        {
            solBandB[p.first][p.second] = 1;
        }
        cout << "Solución con Ramificación y Poda:" << endl;
        printSolution(solBandB);
    }
    else
    {
        cout << "No hay solución con Ramificación y Poda" << endl;
    }

    return 0;
}

// Créditos
// la implementación del código para Backtracking se logró mediante la consulta
// al problema Rat in Maze de GeeksforGeeks (https://www.geeksforgeeks.org/rat-in-a-maze/)
// y a la ayuda de openAI con la finalidad de resolver dudas, localizar errores y entender
// mejor la implementación del programa