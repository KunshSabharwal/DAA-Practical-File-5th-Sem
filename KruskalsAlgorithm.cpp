#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <limits>
using namespace std;
using namespace chrono;

struct Edge
{
    int u, v;
    double cost;

    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }
};

class DisjointSet
{
public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent, rank;
};

double kruskalMST(const vector<Edge> &edges, int vertices)
{
    DisjointSet ds(vertices);
    double totalCost = 0;

    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    for (const auto &edge : sortedEdges)
    {
        int u = edge.u, v = edge.v;
        double cost = edge.cost;

        if (ds.find(u) != ds.find(v))
        {
            ds.unionSets(u, v);
            totalCost += cost;
        }
    }

    return totalCost;
}

vector<Edge> createGraph(int vertices, int edges)
{
    vector<Edge> graph;

    for (int i = 1; i < vertices; i++)
    {
        int connectTo = rand() % i;
        double cost = (rand() % 100) + 1;
        graph.push_back({i, connectTo, cost});
        graph.push_back({connectTo, i, cost});
    }

    int addedEdges = vertices - 1;
    while (addedEdges < edges)
    {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v)
        {
            bool edgeExists = false;
            for (auto &edge : graph)
            {
                if ((edge.u == u && edge.v == v) || (edge.u == v && edge.v == u))
                {
                    edgeExists = true;
                    break;
                }
            }
            if (!edgeExists)
            {
                double cost = (rand() % 100) + 1;
                graph.push_back({u, v, cost});
                graph.push_back({v, u, cost});
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
        double mstWeight = kruskalMST(graph, V);
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
