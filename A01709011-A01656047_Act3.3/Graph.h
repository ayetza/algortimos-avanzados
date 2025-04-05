#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_set>

class Graph
{
private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia
    // vector de listas ligadas de sets (vertices)
    std::vector<std::set<int>> adjList;
    // Matriz de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<int>> adjMatrix;
    // vector de pares (grado, vertice)
    std::vector<std::pair<int, int>> grados;

    void split(std::string line, std::vector<int> &res);
    bool algoritmoBipartite(int V, std::vector<std::vector<int>> adjMatrix);

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void print();
    void algoritmoWelshPowell();
    void isBipartite();
};

#endif // _GRAPH_H_
