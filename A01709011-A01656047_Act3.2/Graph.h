#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <map>

class Graph
{
private:
    int numNodes;
    int numEdges;
    int s; // ciudad origen
    int t; // ciudad destino
    int L; // distancia maxima
    // Lista de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<std::pair<int, int>>> adjList;

    void split(std::string line, std::vector<int> &res);

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void print();
    void DFS(int v);
    // problema A
    void Dijkstra(std::istream &input);
    // problema B
    void BFS(std::istream &input);
};

#endif // _GRAPH_H_
