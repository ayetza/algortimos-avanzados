#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <functional>
#include <climits>
#include <numeric>
#include <cmath>
#include <list>

class Graph
{
private:
    int numNodes;
    int numEdges;
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> revAdjList;
    std::vector<int> currentSol;
    int currentScore;

    std::vector<int> bestSol;
    int bestScore;
    std::mt19937 g;

    void split(std::string line, std::vector<int> &res);
    int evaluate(const std::vector<int> &sol);
    int deltaEvaluate(int u, int v, const std::vector<int> &sol, int currentScore);
    std::vector<int> generateInitialSol();

public:
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void tabuSearch(int maxIter, int Lmin, int Lmax);
    std::pair<int, double> printSol(int maxIter, int Lmin, int Lmax);
    void runMultiple(int maxIter, int Lmin, int Lmax);
    // void testDeltaEvaluate();
};

#endif // GRAPH_H