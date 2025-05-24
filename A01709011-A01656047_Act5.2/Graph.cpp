#include "Graph.h"

// complejidad O(1)
Graph::Graph()
{
    adjList.clear();
    currentSol.clear();
    numNodes = 0;
    numEdges = 0;
    currentScore = 0;
}

// complejidad O(n)
Graph::~Graph()
{
    adjList.clear();
    currentSol.clear();
    numNodes = 0;
    numEdges = 0;
    currentScore = 0;
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

// complejidad O(n + m)
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
            // Reservar memoria para los numNodes renglones y columnas vacias
            adjList.resize(numNodes, std::vector<int>());
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        // Grafos dirigidos agrega la arista (u,v)
        adjList[u].push_back(v);
        i++;
    }
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

    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);

    std::shuffle(solution.begin(), solution.end(), g);

    return solution;
}

// complejidad O(n+m)
//  evalua max{0,π(v)-π(u)} para cada permutacion
int Graph::evaluate(const std::vector<int> &currentSol)
{
    int score = 0;
    std::vector<int> pos(numNodes);

    for (int i = 0; i < numNodes; i++)
    {
        pos[currentSol[i]] = i; // posición en la permutación
    }

    for (int u = 0; u < numNodes; u++)
    {
        for (int v : adjList[u])
        {
            int contribution = std::max(0, pos[v] - pos[u]);
            score += contribution;
        }
    }
    return score;
}

// complejidad O(k*(n+m))
void Graph::localSearch(int k)
{
    currentSol = generateInitialSol();
    currentScore = evaluate(currentSol);

    int i = 0, j = 1;
    int counter = 0;

    while (counter < k && i < numNodes - 1)
    {
        std::vector<int> neighbor = currentSol;
        std::swap(neighbor[i], neighbor[j]);

        int neighborScore = evaluate(neighbor);

        if (neighborScore > currentScore)
        {
            // std::cout << neighborScore << " ";
            currentSol = neighbor;
            currentScore = neighborScore;

            i = 0;
            j = 1;
        }
        else
        {
            j++;
            if (j >= numNodes)
            {
                i++;
                j = i + 1;
            }
        }
        counter++;
    }
}

// complejidad O(k*(n+m))
std::pair<int, double> Graph::printSol(int k)
{

    auto start = std::chrono::high_resolution_clock::now();

    localSearch(k);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    return {currentScore, duration.count()};
}

// complejidad O(numRun*k*(n+m))
void Graph::runMultiple(int k, int numRuns)
{
    std::vector<int> scores;
    std::vector<double> times;

    int bestScore = std::numeric_limits<int>::min();
    double bestTime = 0.0;
    std::vector<int> bestSolution;

    for (int i = 0; i < numRuns; ++i)
    {
        auto result = printSol(k);
        scores.push_back(result.first);
        times.push_back(result.second);

        if (result.first > bestScore)
        {
            bestScore = result.first;
            bestTime = result.second;
            bestSolution = currentSol;
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

    /*Impresion de estadisticas
    std::cout << "Estadisticas de " << numRuns << " ejecuciones:\n";
    std::cout << "Promedio score: " << avgScore << "\n";
    std::cout << "Mejor score: " << maxScore << "\n";
    std::cout << "Peor score: " << minScore << "\n";
    std::cout << "Desviacion estandar: " << stdDev << "\n";
    std::cout << "Tiempo promedio: " << avgTime << " segs\n";
    */

    std::cout << "----------------------------------------------------\n";
    std::cout << bestScore << "\n";
    std::cout << bestTime << "\n";
    for (int val : bestSolution)
    {
        std::cout << (val + 1) << " ";
    }
    std::cout << "\n";
}
