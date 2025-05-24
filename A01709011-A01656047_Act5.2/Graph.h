#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

class Graph
{
private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia
    // vector de vectores de enteros
    std::vector<std::vector<int>> adjList;
    // vector de solución actual tamaño numNodes
    std::vector<int> currentSol;
    int currentScore;

    std::mt19937 g;

    void split(std::string line, std::vector<int> &res);
    int evaluate(const std::vector<int> &currentSol);
    std::vector<int> generateInitialSol();

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void localSearch(int k);
    std::pair<int, double> printSol(int k);
    void runMultiple(int k, int numRuns);
};

#endif // _GRAPH_H_
