#include "Graph.h"
#include <limits>
#include <queue>

Graph::Graph()
{
    adjList.clear();
    adjListDir.clear();
    adjMatrix.clear();
    adjDinic.clear();
    destinyNode.clear();
    capacity.clear();
    reverseEdge.clear();
    lvl.clear();
    ptr.clear();
    numNodes = 0;
    numEdges = 0;
    numNodes2 = 0;
    numEdges2 = 0;
    start = 0;
    end = 0;
}

Graph::~Graph()
{
    adjList.clear();
    adjListDir.clear();
    adjMatrix.clear();
    adjDinic.clear();
    destinyNode.clear();
    capacity.clear();
    reverseEdge.clear();
    lvl.clear();
    ptr.clear();
    numNodes = 0;
    numEdges = 0;
    numNodes2 = 0;
    numEdges2 = 0;
    start = 0;
    end = 0;
}

int Graph::getEnd()
{
    return this->end;
}

int Graph::getStart()
{
    return this->start;
}

// Complejidad O(n)
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

// Complejidad O(m + n^2)
void Graph::readNoDirected(std::istream &input)
{
    std::string line;
    int i = 0;
    while (std::getline(input, line))
    {
        if (i == 0)
        {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            // Reservar memoria para los numNodes renglones y columnas vacias
            adjList.resize(numNodes);
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        int w = res[2]; // leer el peso
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
        i++;
    }
    // matriz de adyacencia para TSP
    adjMatrix.resize(numNodes, std::vector<int>(numNodes, INT_MAX));
    // O(n^2)
    for (int u = 0; u < numNodes; u++)
    {
        for (int i = 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i].first;
            int w = adjList[u][i].second;
            adjMatrix[u][v] = w;
            adjMatrix[v][u] = w;
        }
        adjMatrix[u][u] = 0;
    }
}

// Complejidad O(n)
void Graph::readDirected(std::istream &input)
{
    std::string line;
    int i = 0;
    while (std::getline(input, line))
    {
        if (i == 0)
        {
            std::vector<int> res;
            split(line, res);
            numNodes2 = res[0];
            numEdges2 = res[1];
            start = res[2] - 1;
            end = res[3] - 1;
            // Reservar memoria para los numNodes renglones y columnas vacias
            adjListDir.resize(numNodes2);
            adjDinic.resize(numNodes2);
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1;
        int v = res[1] - 1;
        int w = res[2]; // leer el peso
        // Grafos dirigidos agrega la arista (u,v) y el peso de v
        adjListDir[u].emplace_back(v, w);
        addEdge(u, v, w);
        i++;
    }
}

// Complejidad O(n)
void Graph::readGraph(std::istream &input)
{
    std::string line;
    // ignorar la primera linea
    std::getline(input, line);

    // primer grafo
    std::getline(input, line); // lee N y M del primer grafo
    std::stringstream g1;
    g1 << line << "\n"; // incluir linea N M en el flujo
    std::vector<int> res;
    split(line, res);
    int numEdgs = res[1];
    // leer aristas del grafo no dirigido
    for (int i = 0; i < numEdgs; i++)
    {
        std::getline(input, line);
        g1 << line << "\n";
    }
    readNoDirected(g1);

    // segundo grafo
    std::getline(input, line);
    std::stringstream g2;
    g2 << line << "\n";
    std::vector<int> res2;
    split(line, res2);
    int numEdgs2 = res2[1];
    // leer aristas del grafo dirigido
    for (int i = 0; i < numEdgs2; i++)
    {
        std::getline(input, line);
        g2 << line << "\n";
    }
    readDirected(g2);
}

// Complejidad O(n+m)
void Graph::print()
{
    std::cout << "Adjacency List - Grafo no dirigido" << std::endl;
    for (int u = 0; u < numNodes; u++)
    {
        std::cout << "vertex " << u + 1 << ":"; // convert to one-based nodes
        for (int j = 0; j < (int)adjList[u].size(); j++)
        {
            std::cout << ' ' << "{" << adjList[u][j].first + 1 << " " << adjList[u][j].second << "}";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Adjacent List - Grafo dirigido" << std::endl;
    for (int u = 0; u < numNodes2; u++)
    {
        std::cout << "vertex " << u + 1 << ":"; // convert to one-based nodes
        for (int j = 0; j < (int)adjListDir[u].size(); j++)
        {
            std::cout << ' ' << "{" << adjListDir[u][j].first + 1 << " " << adjListDir[u][j].second << "}";
        }
        std::cout << std::endl;
    }
    std::cout << "Nodo inicio: " << start + 1 << std::endl;
    std::cout << "Nodo final: " << end + 1 << std::endl;
}

// Complejidad O(E log V)
int Graph::Prim()
{
    std::vector<int> key(numNodes, INT_MAX);
    std::vector<int> parent(numNodes, -1);
    std::vector<bool> visited(numNodes, false);
    // min-heap {peso,nodo}
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    int mstWeight = 0;
    key[0] = 0;
    // peso y nodo en 0
    pq.push({0, 0});

    while (!pq.empty())
    {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;
        mstWeight += w;

        // explorar vecinos
        for (int i = 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i].first;
            int weight = adjList[u][i].second;

            if (!visited[v] && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    std::vector<std::string> mstEdges;
    for (int v = 1; v < numNodes; v++)
    {
        if (parent[v] != -1)
        {
            int u = parent[v];
            int w = key[v];
            mstEdges.push_back(
                "(" + std::to_string(u + 1) +
                ", " + std::to_string(v + 1) +
                ", " + std::to_string(w) + ")"

            );
        }
    }
    std::cout << "MST edges: " << std::endl;
    for (int i = 0; i < mstEdges.size(); i++)
    {
        std::cout << mstEdges[i] << std::endl;
    }
    return mstWeight;
}

// complejidad O(n^2)
int Graph::calculateBound(int cost, int visited)
{
    int sum = cost;
    // calcular las aristas max de salida de los nodos no visitados
    for (int u = 0; u < numNodes; u++)
    {
        // verifica que la ciudad no ha sido visitada usando bitmask
        if (!(visited & (1 << u)))
        {
            int minEdge = INT_MAX;
            for (int v = 0; v < numNodes; v++)
            {
                // busca la arisa mas barata desde u hacia una no visitada
                if (u != v && adjMatrix[u][v] < minEdge)
                {
                    minEdge = adjMatrix[u][v];
                }
            }
            // si se encuentra una arista, se suma al costo
            if (minEdge != INT_MAX)
            {
                sum += minEdge;
            }
        }
    }
    return sum;
}

// complejidad O(n^2*2^n) -> peor caso
std::pair<int, std::vector<int>> Graph::TSP()
{
    std::vector<int> bestPath;
    int bestCost = INT_MAX;

    // comparador para la lista prioritaria con prioridad al costo mas bajo
    auto cmp = [](const std::vector<int> &a, const std::vector<int> &b)
    {
        // menor costo tiene mayor prioridad
        return a[0] > b[0];
    };

    // declara una cola prioritaria que almacena vectores de enteros, ordenados en base a su primera posicion usando el comparados lambda cmp
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, decltype(cmp)> pq(cmp);
    const int startCity = 0;
    // solo ciudad 0 visitada
    int visited = (1 << startCity);
    int cost = 0;
    int lvl = 1;

    // comienza con la ciudad 0
    std::vector<int> path = {startCity};
    // calcula el bound inicial;
    int bound = calculateBound(cost, visited);

    // Inserta el estado inicial en la cola de prioridades
    std::vector<int> state = {bound, cost, lvl, startCity};
    state.insert(state.end(), path.begin(), path.end());
    state.push_back(visited);
    pq.push(state);

    while (!pq.empty())
    {
        // se extrae el estado con mejor bound
        std::vector<int> curr = pq.top();
        pq.pop();

        int bound = curr[0];
        int cost = curr[1];
        int lvl = curr[2];
        int currentCity = curr[3];
        int visited = curr.back();

        // el camino va desde la pos 4 hasta antes del visited
        std::vector<int> path(curr.begin() + 4, curr.end() - 1);

        // si ya es peor que el mejor camino, no seguimos
        if (bound >= bestCost)
        {
            continue;
        }

        // caso base: todas las ciudades visitadas
        if (lvl == numNodes)
        {
            // si ya se visitaron todas las ciudades y hay camino de vuelta al inicio, se calcula costo total
            if (adjMatrix[currentCity][startCity] != INT_MAX)
            {
                int totCost = cost + adjMatrix[currentCity][startCity];

                // si es mejor, se guarda como nueva mejor ruta
                if (totCost < bestCost)
                {
                    bestCost = totCost;
                    bestPath = path;
                    bestPath.push_back(startCity);
                }
            }
            continue;
        }

        // Recorre nodos no visitados y accesibles
        for (int next = 0; next < numNodes; next++)
        {
            if (!(visited & (1 << next)) && adjMatrix[currentCity][next] != INT_MAX)
            {
                int newCost = cost + adjMatrix[currentCity][next];
                int newVisited = visited | (1 << next);
                int newBound = calculateBound(newCost, newVisited);

                // Crear nuevo camino y estado
                // Copia el camino actual
                std::vector<int> newPath = path;
                // Añade la nueva ciudad
                newPath.push_back(next);

                // Se calcula el nuevo estado
                std::vector<int> newState = {newBound, newCost, lvl + 1, next};
                newState.insert(newState.end(), newPath.begin(), newPath.end());
                newState.push_back(newVisited);

                // Si vale la pena, se mete a la cola
                if (newBound < bestCost)
                {
                    pq.push(newState);
                }
            }
        }
    }
    return {bestCost, bestPath};
}

// complejidad O(1)
void Graph::addEdge(int u, int v, int c)
{
    // Arista directa (u -> v)
    destinyNode.push_back(v);
    capacity.push_back(c);
    // indice de reversa en v
    reverseEdge.push_back(adjDinic[v].size());
    // indice de reversa en u
    adjDinic[u].push_back(destinyNode.size() - 1);

    // arista reversa (v <- u)
    destinyNode.push_back(u);
    capacity.push_back(0);
    // indice de reversa en u
    reverseEdge.push_back(adjDinic[u].size() - 1);
    // indice de reversa en v
    adjDinic[v].push_back(destinyNode.size() - 1);
}

// complejidad O(m)
bool Graph::BFS()
{
    // asignacion directa de los nodos, inicializados como no visitados
    lvl.assign(numNodes2, -1);
    std::queue<int> q;
    q.push(start);
    // inicia desde el nodo fuente
    lvl[start] = 0;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        // recorrido de las aristas desde v
        for (int i = 0; i < adjDinic[v].size(); i++)
        {
            int idx = adjDinic[v][i];

            // verifica si la arisra tiene capacidad restante > 0 y el nodo destino aun no se ha visitado
            if (capacity[idx] > 0 && lvl[destinyNode[idx]] == -1)
            {
                // asigna el nivel al nodo destino
                lvl[destinyNode[idx]] = lvl[v] + 1;
                q.push(destinyNode[idx]);
            }
        }
    }
    // true si el nodo destino fue alcanzado
    return lvl[end] != -1;
}

// complejidad O(n)
int Graph::DFS(int v, int flow)
{
    // si no hay flujo o se alcanzo el nodo destino, devuelve el flujo actual
    if (flow == 0 || v == end)
    {
        return flow;
    }

    // itera sobre las aristas v usando ptr como puntero
    for (; ptr[v] < adjDinic[v].size(); ptr[v]++)
    {
        // indice de la arista
        int idx = adjDinic[v][ptr[v]];
        // nodo destino de la arista
        int u = destinyNode[idx];

        // continua si la arista tiene capacidad restante y el sig nodo esta en el sig nivel
        if (capacity[idx] > 0 && lvl[u] == lvl[v] + 1)
        {
            // llamada recursiva para seguir empujando el flujo a traves del grafo
            int minFlow = std::min(flow, capacity[idx]);
            int pushed = DFS(u, minFlow);

            // si se empuja el flujo
            if (pushed > 0)
            {
                // resta flujo en arista directa
                capacity[idx] -= pushed;
                // suma el flujo en la arista inversa
                capacity[idx ^ 1] += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

// complejidad O(n^2 * m)
int Graph::Dinic()
{
    int flow = 0;
    ptr.resize(numNodes2);

    while (BFS())
    {
        for (int i = 0; i < numNodes2; i++)
        {
            // reinicia los punteros ptr de todos los nodos a 0
            ptr[i] = 0;
        }

        while (int pushed = DFS(start, INT_MAX))
        {
            flow += pushed;
        }
    }

    return flow;
}
