#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <chrono>
#include <limits>
using namespace std;
using namespace chrono;

struct Edge
{
    int node;
    double cost;
};

double primMST(const vector<vector<Edge>> &graph, int vertices)
{
    vector<bool> visited(vertices, false);
    vector<double> minCost(vertices, numeric_limits<double>::max());
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    minCost[0] = 0;
    pq.push({0, 0});
    double totalCost = 0;

    while (!pq.empty())
    {
        int current = pq.top().second;
        double cost = pq.top().first;
        pq.pop();

        if (visited[current])
            continue;

        visited[current] = true;
        totalCost += cost;

        for (auto &edge : graph[current])
        {
            int nextNode = edge.node;
            double nextCost = edge.cost;

            if (!visited[nextNode] && nextCost < minCost[nextNode])
            {
                minCost[nextNode] = nextCost;
                pq.push({nextCost, nextNode});
            }
        }
    }

    return totalCost;
}

vector<vector<Edge>> createGraph(int vertices, int edges)
{
    vector<vector<Edge>> graph(vertices);

    for (int i = 1; i < vertices; i++)
    {
        int connectTo = rand() % i;
        double cost = (rand() % 100) + 1;
        graph[i].push_back({connectTo, cost});
        graph[connectTo].push_back({i, cost});
    }

    int addedEdges = vertices - 1;
    while (addedEdges < edges)
    {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v)
        {
            bool edgeExists = false;
            for (auto &edge : graph[u])
            {
                if (edge.node == v)
                {
                    edgeExists = true;
                    break;
                }
            }
            if (!edgeExists)
            {
                double cost = (rand() % 100) + 1;
                graph[u].push_back({v, cost});
                graph[v].push_back({u, cost});
                addedEdges++;
            }
        }
    }

    return graph;
}

int main()
{
    srand(time(nullptr));
    int vertexCounts[] = {100, 500, 1000, 5000, 10000};
    double edgeMultiplier = 3;

    for (int V : vertexCounts)
    {
        int E = V * edgeMultiplier;
        auto graph = createGraph(V, E);

        auto start = high_resolution_clock::now();
        double mstWeight = primMST(graph, V);
        auto end = high_resolution_clock::now();

        double elapsed = duration<double>(end - start).count();

        cout << "Vertices: " << V << "\n";
        cout << "Edges: " << E << "\n";
        cout << "MST Weight: " << mstWeight << "\n";
        cout << "Time: " << elapsed << " seconds\n";
        cout << "-----------------------------\n";
    }

    return 0;
}
