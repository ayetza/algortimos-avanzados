#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Graph
{
private:
    int numNodes;
    int numEdges;
    int c; // conductores
    int r; // rutas
    int m; // relaciones
    // Lista de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<int>> adjList;
    std::vector<int> matchR;

    void split(std::string line, std::vector<int> &res);
    bool bpm(int u, std::vector<bool> &seen, std::vector<int> &matchR);

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void print();
    void maxBPM();
    void getMatching();
};

#endif // _GRAPH_H_
