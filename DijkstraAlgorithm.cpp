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
    int v;
    double cost;
};

// Create an adjacency list for an undirected graph
vector<vector<Edge>> createAdjList(int vertices, int edges)
{
    vector<vector<Edge>> adj(vertices);

    // First create a connected tree (like in Kruskal)
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
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v)
        {
            bool exists = false;
            for (const auto &e : adj[u])
            {
                if (e.v == v)
                {
                    exists = true;
                    break;
                }
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

// Dijkstra's algorithm from source to all nodes
vector<double> dijkstra(const vector<vector<Edge>> &adj, int source)
{
    int n = adj.size();
    vector<double> dist(n, numeric_limits<double>::infinity());
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    dist[source] = 0;
    pq.push(make_pair(0.0, source));

    while (!pq.empty())
    {
        pair<double, int> top = pq.top();
        pq.pop();

        double d = top.first;
        int u = top.second;

        if (d > dist[u])
            continue;

        for (const auto &edge : adj[u])
        {
            int v = edge.v;
            double cost = edge.cost;

            if (dist[u] + cost < dist[v])
            {
                dist[v] = dist[u] + cost;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main()
{
    srand(time(nullptr));
    int vertexCounts[] = {500, 1000, 5000, 10000, 50000};
    double edgeMultiplier = 3;

    for (int V : vertexCounts)
    {
        int E = V * edgeMultiplier;
        auto adj = createAdjList(V, E);

        auto start = high_resolution_clock::now();
        vector<double> distances = dijkstra(adj, 0); // From source node 0
        auto end = high_resolution_clock::now();

        // Total distance from source to all reachable nodes
        double totalDistance = 0;
        for (double d : distances)
        {
            if (d < numeric_limits<double>::infinity())
                totalDistance += d;
        }

        double elapsed = duration<double>(end - start).count();

        cout << "Vertices: " << V << "\n";
        cout << "Edges: " << E << "\n";
        cout << "Total Distance from Source (0): " << totalDistance << "\n";
        cout << "Time: " << elapsed << " seconds\n";
        cout << "-----------------------------\n";
    }

    return 0;
}
