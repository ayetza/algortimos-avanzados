#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Graph
{
private:
    // grafo no dirigido
    int numNodes;
    int numEdges;
    // Lista de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<std::pair<int, int>>> adjList;
    std::vector<std::vector<int>> adjMatrix;

    // grafo dirigido
    int numNodes2;
    int numEdges2;
    int start;
    int end;
    // Lista de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<std::pair<int, int>>> adjListDir;

    void split(std::string line, std::vector<int> &res);

    // TSP
    int calculateBound(int cost, int visited);

    // Dinic
    std::vector<int> lvl;
    std::vector<int> destinyNode;
    std::vector<int> capacity;
    std::vector<int> reverseEdge;
    std::vector<int> ptr;
    std::vector<std::vector<int>> adjDinic;

    void addEdge(int u, int v, int c);
    bool BFS();
    int DFS(int u, int flow);

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void readDirected(std::istream &input);
    void readNoDirected(std::istream &input);
    void print();
    int getStart();
    int getEnd();

    // problema1 (MST) -> Prim
    int Prim();

    // problema2 (TSP) -> B&B
    std::pair<int, std::vector<int>> TSP();

    // problema3 (Flujo Max) -> Dinic
    int Dinic();
};

#endif // _GRAPH_H_
