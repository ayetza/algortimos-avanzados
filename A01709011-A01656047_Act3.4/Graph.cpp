#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "Graph.h"

using namespace std;

// Complejidad O(1)
Graph::Graph()
{
    adjList.clear();
    numNodes = 0;
    numEdges = 0;
    c = r = m = 0;
}

// Complejidad O(1)
Graph::~Graph()
{
    adjList.clear();
    numNodes = 0;
    numEdges = 0;
    c = r = m = 0;
}

// Complejidad: O(n)
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

// Complejidad: O(n+m})
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
            c = res[0];
            r = res[1];
            m = res[2];
            numNodes = c + r;
            numEdges = m;
            // Reservar memoria para los numNodes renglones y columnas vacias
            adjList.resize(numNodes, std::vector<int>());
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        // Grafos no dirigidos agrega la arista (u,v) y la (v,u)
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        i++;
    }
}

// Complejidad O(n)
bool Graph::bpm(int u, std::vector<bool> &seen, std::vector<int> &matchR)
{

    for (int v : adjList[u])
    {
        int routeIndx = v - c;
        if (!seen[routeIndx])
        {
            seen[routeIndx] = true;
            if (matchR[routeIndx] == -1 || bpm(matchR[routeIndx], seen, matchR))
            {
                matchR[routeIndx] = u;
                return true;
            }
        }
    }
    return false;
}

// Complejidad O(n*m)
void Graph::maxBPM()
{
    std::vector<pair<int, int>> pairs;
    matchR.resize(r, -1);
    int res = 0;
    for (int u = 0; u < c; u++)
    {
        std::vector<bool> seen(r, false);

        if (bpm(u, seen, matchR))
        {
            res++;
        }
    }
    std::cout << "Rutas asignadas: " << res << std::endl;

    for (int i = 0; i < r; i++)
    {
        if (matchR[i] != -1)
        {
            pairs.emplace_back(matchR[i] + 1, i + c + 1); // convertir a 1 basado
        }
    }
    std::sort(pairs.begin(), pairs.end());
    for (const auto &p : pairs)
    {
        std::cout << p.first << " " << p.second << std::endl;
    }
}