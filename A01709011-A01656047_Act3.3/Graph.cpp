
#include "Graph.h"

// Complejidad O(1)
Graph::Graph()
{
    adjList.clear();
    grados.clear();
    numNodes = 0;
    numEdges = 0;
}

// Complejidad O(1)
Graph::~Graph()
{
    adjList.clear();
    grados.clear();
    numNodes = 0;
    numEdges = 0;
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

// Complejidad: O(n+m)
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
            // Reservar memoria para los renglones
            // de la lista de adyacencia
            adjList.resize(numNodes);
            // Reservar memoria para los renglones
            // de la matriz de adyacencia
            adjMatrix.resize(numNodes);
            // Reservar memoria para el vector grados
            grados.resize(numNodes);
            // Declara una lista vacia para cada renglon y
            // la almacena en el vector
            for (int k = 0; k < numNodes; k++)
            {
                std::set<int> tmpSet; // lista de sets(vertice)
                adjList[k] = tmpSet;
                adjMatrix[k] = std::vector<int>();
                grados[k].first = 0;  // grado
                grados[k].second = k; // nodo
            }
            i++;
            continue;
        }
        std::vector<int> res;
        split(line, res);
        int u = res[0] - 1; // convierte nodo a cero-basado
        int v = res[1] - 1; // convierte nodo a cero-basado
        // Grafos dirigidos agrega solo la arista (u,v)
        // Grafo ponderado guarda pares(nodo, peso)
        adjList[u].insert(v);
        adjList[v].insert(u);
        adjMatrix[u].push_back(v);
        adjMatrix[v].push_back(u);
        // El nodo u y v tienen una arista mas
        grados[u].first++;
        grados[v].first++;
        i++;
    }
}

// Complejidad: O(n^2)
void Graph::algoritmoWelshPowell()
{
    // Ordenar el vector grados descendentemente
    std::sort(grados.rbegin(), grados.rend());
    // Vector con el color de cada nodo
    std::vector<int> color(numNodes, 0);
    int colorAssigned = 0;
    for (int i = 0; i < numNodes; i++)
    {
        int u = grados[i].second; // nodo u
        if (!color[u])
        {
            color[u] = ++colorAssigned;
            // conjunto de nodos coloreados con colorAssigned
            std::unordered_set<int> coloredWithColorAssigned;
            coloredWithColorAssigned.insert(u);
            for (int j = i + 1; j < numNodes; j++)
            {
                int v = grados[j].second; // nodo v
                // Verificar si u es vecino de v
                bool notAdyacent = adjList[u].find(v) == adjList[u].end();
                if (!color[v] && notAdyacent)
                {
                    // Verificar si v es adyacente
                    // a vertices coloreados con colorAssigned
                    bool adyacentToColored = false;
                    std::unordered_set<int>::iterator it;
                    for (it = coloredWithColorAssigned.begin(); it != coloredWithColorAssigned.end(); ++it)
                    {
                        int w = *it; // nodo w
                        if (adjList[v].find(w) != adjList[v].end())
                            adyacentToColored = true;
                    }
                    if (!adyacentToColored)
                    {
                        color[v] = colorAssigned;
                        coloredWithColorAssigned.insert(v);
                    }
                }
            }
        }
    }
    for (int u = 0; u < numNodes; u++)
    {
        std::cout << u + 1 << " " << color[u] << std::endl;
    }
}

// Complejidad: O(n+m)
bool Graph::algoritmoBipartite(int V, std::vector<std::vector<int>> adjMatrix)
{
    // vector para guardar los colores de los vertices
    std::vector<int> color(V, -1); // Inizializa todos con -1 (sin color)

    // queue para BFS
    std::queue<int> q;

    // itera sobre todos los vertices
    for (int i = 0; i < V; i++)
    {
        // si el vertice no tiene color, se inicia el BFS desde ahi
        if (color[i] == -1)
        {
            // se asigna el primer color al vertice de inicio
            color[i] = 0;
            q.push(i);

            // BFS
            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                // Pasa por todos los vertices adjacientes
                for (auto &v : adjMatrix[u])
                {

                    // si el vertice adjaciente no tiene color, se le asigna
                    if (color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }

                    // si el vertice tiene el mismo color, no es bipartita
                    if (color[v] == color[u])
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// Complejidad: O(n^2 + m)
void Graph::isBipartite()
{
    bool isB = algoritmoBipartite(numNodes, adjMatrix);
    if (isB == true)
    {
        std::cout << "True" << std::endl;
        algoritmoWelshPowell();
    }
    else
        std::cout << "False" << std::endl;
}
