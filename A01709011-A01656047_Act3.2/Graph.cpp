#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <stack>
#include <algorithm>

#include "Graph.h"

Graph::Graph()
{
    adjList.clear();
    numNodes = 0;
    numEdges = 0;
}

Graph::~Graph()
{
    adjList.clear();
    numNodes = 0;
    numEdges = 0;
}

// Complejidad: O(n+m)
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

// Complejidad: O(n+m)
void Graph::readGraph(std::istream &input)
{
    std::string line;
    int i = 1;
    while (std::getline(input, line))
    {
        if (i == 1) // Leemos numNodes y numEdges
        {
            std::vector<int> res;
            split(line, res);
            s = res[0] - 1;
            t = res[1] - 1;
            L = res[2];
            i++;
            continue;
        }
        else if (i == 2)
        {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            //  Reservar memoria para los renglones de la lista de adyacencia (cero basada)
            adjList.resize(numNodes);
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        int weight = res[2]; // leer el peso
        // Grafos dirigidos agrega la arista (u,v) y el peso de v
        adjList[u].emplace_back(v, weight);
        i++;
    }
}

// Complejidad O(n+m)
void Graph::print()
{
    std::cout << "Adjacency List" << std::endl;
    for (int u = 0; u < numNodes; u++)
    {
        std::cout << "vertex " << u + 1 << ":";
        for (const auto &neighbour : adjList[u])
        {
            std::cout << " {" << neighbour.first + 1 << ", " << neighbour.second << "}";
        }
        std::cout << std::endl;
    }
}

// Complejidad O(n+m)
// Recorrido del grafo DFS a partir del nodo v (cero-basado)
void Graph::DFS(int v)
{
    // Declaramos un set del STL de C++ (elementos unicos y ordenados)
    std::set<int> visited;
    // Creamos un stack
    std::stack<int> stack;
    bool isInVisited = false;
    std::cout << "Recorrido DFS " << std::endl;
    // Entra al stack el vertice inicial
    stack.push(v);
    while (!stack.empty())
    {
        // Extraemos un vertice del stack y lo procesamos (print)
        v = stack.top();
        stack.pop();
        isInVisited = visited.find(v) != visited.end();
        if (!isInVisited)
        {
            visited.insert(v);
            // convierte nodo a uno-basado
            std::cout << v + 1 << " ";
        }
        // Obtenemos los vertices adyacentes del vertice v
        // Si estos no han sido visitados se marcan como visitados
        // y los metemos al stack
        for (int j = 0; j < (int)adjList[v].size(); j++)
        {
            int u = adjList[v][j].first;
            // Verificar si el vecino u ya fue visitado
            isInVisited = visited.find(u) != visited.end();
            if (!isInVisited) // no visitado
                stack.push(u);
        }
    }
    std::cout << std::endl;
}

// Complejidad O(m log n)
void Graph::Dijkstra(std::istream &input)
{
    std::vector<int> dist(numNodes, std::numeric_limits<int>::max());
    dist[s] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, s);

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (const auto &neighbour : adjList[u])
        {
            int v = neighbour.first;
            int weight = neighbour.second;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = std::max(d, weight);
                pq.emplace(dist[v], v);
            }
        }
    }

    if (dist[t] == std::numeric_limits<int>::max())
    {
        std::cout << "No existe un camino para ir a la ciudad" << s + 1 << "";
    }
    else
        std::cout << "La autonomia minima de la bateria de un vehiculo electrico para viajar de "
                  << s + 1 << " a " << t + 1 << " es: " << dist[t];
}

// Complejidad O(n+m)
void Graph::BFS(std::istream &input)
{
    int v = s;
    // Declaramos un set del STL de C++ (elementos unicos y ordenados)
    std::set<int> visited;
    // Creamos una queue
    std::queue<std::pair<int, std::vector<int>>> queue; //(nodo actual, camino recorrido)
    // inicializa una queue con un par (nodo de inicio, vector que contiene el nodo de inicio)
    queue.push({v, {v}});
    while (!queue.empty())
    {
        // se sacan el nodo y el camino de la cola
        auto [v, path] = queue.front();
        queue.pop();

        if (v == t)
        {
            for (int i = 0; i < path.size(); i++)
            {
                std::cout << path[i] + 1 << " ";
            }
            return;
        }
        if (visited.find(v) == visited.end())
        {
            visited.insert(v);
        }
        // Obtenemos los vertices adyacentes con aristas <= L
        for (int j = 0; j < adjList[v].size(); j++)
        {
            int u = adjList[v][j].first;
            int dist = adjList[v][j].second;
            if (visited.find(u) == visited.end() && dist <= L)
            {
                std::vector<int> newPath = path;
                newPath.push_back(u);
                queue.push({u, newPath});
            }
        }
    }
    std::cout << "No existe un camino factible para ir de la ciudad " << s + 1
              << " a la ciudad " << t + 1 << " usando un vehiculo con autonomia " << L << std::endl;
}