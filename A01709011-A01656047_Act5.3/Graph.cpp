#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_set>
#include <numeric>
#include <cmath>
#include <climits>
#include <cstdlib>

// complejidad O(1)
Graph::Graph()
{
    adjList.clear();
    currentSol.clear();
    numNodes = 0;
    numEdges = 0;
    currentScore = 0;
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    g.seed(seed);
    bestSol.clear();
    revAdjList.clear();
    bestScore = 0;
}

// complejidad O(n)
Graph::~Graph()
{
    adjList.clear();
    currentSol.clear();
    numNodes = 0;
    numEdges = 0;
    currentScore = 0;
    bestSol.clear();
    revAdjList.clear();
    bestScore = 0;
}

// complejidad O(n)
void Graph::split(std::string line, std::vector<int> &res)
{
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos)
    {
        res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
        lastPos = strPos + 1;
        strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// Complejidad O(n + m)
void Graph::readGraph(std::istream &input)
{
    std::string line;
    int i = 1;
    while (std::getline(input, line))
    {
        if (i == 1)
        {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            adjList.resize(numNodes, std::vector<int>());
            revAdjList.resize(numNodes, std::vector<int>());
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        adjList[u].push_back(v);
        revAdjList[v].push_back(u);
        i++;
    }
}

// complejidad O(n+m)
//  evalua max{0,π(v)-π(u)}
int Graph::evaluate(const std::vector<int> &currentSol)
{
    int score = 0;

    for (int u = 0; u < numNodes; u++)
    {
        for (int v : adjList[u])
        {
            int contribution = std::max(0, currentSol[v] - currentSol[u]);
            score += contribution;
        }
    }
    return score;
}

// Complejidad O(A(u)+A(v))
int Graph::deltaEvaluate(int u, int v, const std::vector<int> &sol, int currentScore)
{
    if (u == v)
        return currentScore;

    int delta = 0;
    const int old_u_pos = sol[u];
    const int old_v_pos = sol[v];

    // Conjunto de nodos afectados (u, v y sus vecinos)
    std::unordered_set<int> affected = {u, v};
    for (int neighbor : adjList[u])
        affected.insert(neighbor);
    for (int neighbor : adjList[v])
        affected.insert(neighbor);
    for (int pred : revAdjList[u])
        affected.insert(pred);
    for (int pred : revAdjList[v])
        affected.insert(pred);

    // Calcular contribución antes del swap
    for (int node : affected)
    {
        for (int neighbor : adjList[node])
        {
            if (affected.find(neighbor) != affected.end())
            {
                delta -= std::max(0, sol[neighbor] - sol[node]);
            }
        }
    }

    // Función para obtener la posición después del swap
    auto swappedPos = [&](int node)
    {
        if (node == u)
            return old_v_pos;
        if (node == v)
            return old_u_pos;
        return sol[node];
    };

    // Calcular contribución después del swap
    for (int node : affected)
    {
        for (int neighbor : adjList[node])
        {
            if (affected.find(neighbor) != affected.end())
            {
                delta += std::max(0, swappedPos(neighbor) - swappedPos(node));
            }
        }
    }

    return currentScore + delta;
}

// complejidad O(n)
//  permutacion inicial aleatoria de nodos
std::vector<int> Graph::generateInitialSol()
{
    std::vector<int> solution(numNodes);

    for (int i = 0; i < numNodes; ++i)
    {
        solution[i] = i;
    }

    std::shuffle(solution.begin(), solution.end(), g);

    return solution;
}

// Complejidad O(maxItex * n^2 * (A(u) + A(v)))
void Graph::tabuSearch(int maxIter, int Lmin, int Lmax)
{
    currentSol = generateInitialSol();
    currentScore = evaluate(currentSol);

    bestSol = currentSol;
    bestScore = currentScore;

    // Iteraciones sin mejora
    int NI = 0;
    int iter = 0;

    // Memoria tabú como matriz 2D (almacena la iteración de expiración)
    std::vector<std::vector<int>> tabuMatrix(numNodes, std::vector<int>(numNodes, 0));
    std::uniform_int_distribution<> tabuLengthDist(Lmin, Lmax);
    int tabuTenure = tabuLengthDist(g);

    // O(maxIter)
    while (iter < maxIter)
    {
        bool improvementFound = false;
        std::pair<int, int> bestMove{-1, -1};
        int bestNeighborScore = INT_MIN;

        // Determinar el número de movimientos a evaluar (muestreo para grafos grandes)
        const long long totalPairs = static_cast<long long>(numNodes) * (numNodes - 1) / 2;
        const int maxCandidates = (numNodes > 100) ? std::min(5000, static_cast<int>(totalPairs)) : totalPairs;

        if (numNodes <= 100)
        {
            // Búsqueda exhaustiva para grafos pequeños
            for (int u = 0; u < numNodes && !improvementFound; u++)
            {
                for (int v = u + 1; v < numNodes; v++)
                {
                    if (currentSol[u] == currentSol[v])
                        continue;

                    // Verifica si el movimiento es tabú (iter actual < iter de expiración)
                    bool isTabu = (iter < tabuMatrix[u][v]) || (iter < tabuMatrix[v][u]);

                    // O(A(u) + A(v))
                    int neighborScore = deltaEvaluate(u, v, currentSol, currentScore);
                    bool aspiration = (neighborScore > bestScore);

                    // Si no es tabú o cumple aspiración, y es mejor que el mejor vecino actual
                    if ((!isTabu || aspiration) && neighborScore > bestNeighborScore)
                    {
                        bestMove = {u, v};
                        bestNeighborScore = neighborScore;
                        if (neighborScore > currentScore)
                        {
                            improvementFound = true;
                        }
                    }
                }
            }
        }
        else
        {
            // Muestreo aleatorio para grafos grandes
            for (int i = 0; i < maxCandidates && !improvementFound; i++)
            {
                int u = g() % numNodes;
                int v = g() % numNodes;
                if (u == v)
                    continue;
                if (u > v)
                    std::swap(u, v); // Para mantener u < v y usar la misma memoria tabú

                if (currentSol[u] == currentSol[v])
                    continue;

                bool isTabu = (iter < tabuMatrix[u][v]) || (iter < tabuMatrix[v][u]);
                int neighborScore = deltaEvaluate(u, v, currentSol, currentScore);
                bool aspiration = (neighborScore > bestScore);

                if ((!isTabu || aspiration) && neighborScore > bestNeighborScore)
                {
                    bestMove = {u, v};
                    bestNeighborScore = neighborScore;
                    if (neighborScore > currentScore)
                    {
                        improvementFound = true;
                    }
                }
            }
        }

        // Aplica el mejor movimiento encontrado
        if (bestMove.first != -1)
        {
            // Realiza el intercambio
            std::swap(currentSol[bestMove.first], currentSol[bestMove.second]);
            currentScore = bestNeighborScore;

            // Actualizar la memoria tabú (establece la iteración de expiración)
            tabuMatrix[bestMove.first][bestMove.second] = iter + tabuTenure;
            tabuMatrix[bestMove.second][bestMove.first] = iter + tabuTenure;

            // Actualizar la mejor solución global
            if (currentScore > bestScore)
            {
                bestScore = currentScore;
                bestSol = currentSol;
                NI = 0;
            }
            else
            {
                NI++;
            }
        }
        else
        {
            NI++;
        }

        // Ajusta la tenencia del tabú dinámicamente
        if (NI > numNodes / 2 && tabuTenure < Lmax)
        {
            tabuTenure++;
        }
        else if (NI == 0 && tabuTenure > Lmin)
        {
            tabuTenure--;
        }

        // Diversificacion controlada
        if (NI >= numNodes)
        {
            // Perturbación con actualización incremental
            int perturbations = std::min(numNodes / 4, 20);
            for (int i = 0; i < perturbations; i++)
            {
                int u = g() % numNodes;
                int v = g() % numNodes;
                if (u == v)
                    continue;

                // Actualiza score incrementalmente
                currentScore = deltaEvaluate(u, v, currentSol, currentScore);
                std::swap(currentSol[u], currentSol[v]);

                // Actualiza la memoria tabú
                tabuMatrix[u][v] = iter + tabuTenure;
                tabuMatrix[v][u] = iter + tabuTenure;
            }

            NI = 0;
        }

        iter++;
    }
}

// Complejidad O(maxItex * n^2 * (A(u) + A(v)))
std::pair<int, double> Graph::printSol(int maxIter, int Lmin, int Lmax)
{
    auto start = std::chrono::high_resolution_clock::now();
    tabuSearch(maxIter, Lmin, Lmax);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return {bestScore, duration.count()};
}

// Complejidad O(numRuns * maxItex * n^2 * (A(u) + A(v)))
void Graph::runMultiple(int maxIter, int Lmin, int Lmax)
{
    int numRuns = 10;
    std::vector<int> scores;
    std::vector<double> times;

    int bestScoreGlobal = std::numeric_limits<int>::min();
    double bestTime = 0.0;
    std::vector<int> bestSolutionGlobal;

    for (int i = 0; i < numRuns; ++i)
    {
        auto result = printSol(maxIter, Lmin, Lmax);
        scores.push_back(result.first);
        times.push_back(result.second);

        if (result.first > bestScoreGlobal)
        {
            bestScoreGlobal = result.first;
            bestTime = result.second;
            bestSolutionGlobal = bestSol; // Guardar la mejor solución encontrada
        }
    }

    // Estadisticas
    double avgScore = std::accumulate(scores.begin(), scores.end(), 0.0) / numRuns;
    double avgTime = std::accumulate(times.begin(), times.end(), 0.0) / numRuns;

    auto minScore = *std::min_element(scores.begin(), scores.end());
    auto maxScore = *std::max_element(scores.begin(), scores.end());

    double sumSquaredDiff = 0;

    for (int i = 0; i < scores.size(); ++i)
    {
        sumSquaredDiff += (scores[i] - avgScore) * (scores[i] - avgScore);
    }

    double stdDev = std::sqrt(sumSquaredDiff / numRuns);

    // impresion de estadisticas
    std::cout
        << "Estadisticas de " << numRuns << " ejecuciones:\n";
    std::cout << "Promedio score: " << avgScore << "\n";
    std::cout << "Mejor score: " << maxScore << "\n";
    std::cout << "Peor score: " << minScore << "\n";
    std::cout << "Desviacion estandar: " << stdDev << "\n";
    std::cout << "Tiempo promedio: " << avgTime << " segs\n";

    // Convertir la mejor solución a formato de orden
    std::vector<int> order(numNodes);
    for (int node = 0; node < numNodes; node++)
    {
        int position = bestSolutionGlobal[node];
        order[position] = node;
    }

    std::cout << "----------------------------------------------------\n";
    std::cout << bestScoreGlobal << "\n";
    std::cout << bestTime << "\n";
    for (int pos = 0; pos < numNodes; pos++)
    {
        std::cout << (order[pos] + 1) << " ";
    }
    std::cout << "\n";
}