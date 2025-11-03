#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits>
using namespace std;
using namespace chrono;

struct Edge
{
    int v;
    double cost;
};

vector<vector<Edge>> createAdjList(int vertices, int edges)
{
    vector<vector<Edge>> adj(vertices);
    for (int i = 1; i < vertices; i++)
    {
        int connectTo = rand() % i;
        double cost = (rand() % 100) + 1;
        adj[i].push_back({connectTo, cost});
        adj[connectTo].push_back({i, cost});
    }
    int addedEdges = vertices - 1;
    while (addedEdges < edges)
    {
        int u = rand() % vertices, v = rand() % vertices;
        if (u != v)
        {
            bool exists = false;
            for (auto &e : adj[u])
                if (e.v == v)
                {
                    exists = true;
                    break;
                }
            if (!exists)
            {
                double cost = (rand() % 100) + 1;
                adj[u].push_back({v, cost});
                adj[v].push_back({u, cost});
                addedEdges++;
            }
        }
    }
    return adj;
}

vector<vector<double>> createAdjMatrix(const vector<vector<Edge>> &adj)
{
    int n = adj.size();
    vector<vector<double>> dist(n, vector<double>(n, numeric_limits<double>::infinity()));
    for (int i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
        for (auto &e : adj[i])
            dist[i][e.v] = e.cost;
    }
    return dist;
}

void floydWarshall(vector<vector<double>> &dist)
{
    int n = dist.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main()
{
    srand(time(nullptr));
    int vertexCounts[] = {100, 200, 300, 400, 500};
    double edgeMultiplier = 3;

    for (int V : vertexCounts)
    {
        int E = V * edgeMultiplier;
        auto adj = createAdjList(V, E);
        auto dist = createAdjMatrix(adj);

        auto start = high_resolution_clock::now();
        floydWarshall(dist);
        auto end = high_resolution_clock::now();

        double totalDistance = 0;
        int count = 0;
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (i != j && dist[i][j] < numeric_limits<double>::infinity())
                {
                    totalDistance += dist[i][j];
                    count++;
                }

        double elapsed = duration<double>(end - start).count();
        cout << "Vertices: " << V << "\nEdges: " << E
             << "\nTotal Distance: " << totalDistance
             << "\nAverage Distance: " << (count ? totalDistance / count : 0)
             << "\nTime: " << elapsed << " seconds\n-----------------------------\n";
    }
}
