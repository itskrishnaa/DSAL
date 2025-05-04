#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX = 100;
int n;
string vertexNames[MAX];
int adjMatrix[MAX][MAX];
map<string, vector<pair<string, int>>> adjList;
int parent[MAX];
struct Edge
{
    int u, v, weight;
};

int find(int i)
{
    if (parent[i] == -1)
        return i;
    return parent[i] = find(parent[i]);
}

void union_set(int u, int v)
{
    int u_set = find(u);
    int v_set = find(v);
    if (u_set != v_set)
        parent[u_set] = v_set;
}

void DFS(int i, bool visited[])
{
    visited[i] = true;
    for (auto it : adjList[vertexNames[i]])
    {
        int j;
        for (j = 0; j < n; j++)
        {
            if (vertexNames[j] == it.first)
                break;
        }
        if (!visited[j])
            DFS(j, visited);
    }
}

int main()
{
    cout << "Enter number of vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter name of vertex " << i + 1 << ": ";
        cin >> vertexNames[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            char conn;
            cout << "Is there a connection between " << vertexNames[i] << " and " << vertexNames[j] << " (y/n)? ";
            cin >> conn;
            if (conn == 'y' || conn == 'Y')
            {
                int w;
                cout << "Enter weight: ";
                cin >> w;
                adjMatrix[i][j] = w;
                adjMatrix[j][i] = w;
                adjList[vertexNames[i]].push_back({vertexNames[j], w});
                adjList[vertexNames[j]].push_back({vertexNames[i], w});
            }
            else
            {
                adjMatrix[i][j] = adjMatrix[j][i] = 0;
            }
        }
    }

    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++)
    {
        cout << vertexNames[i] << ": ";
        for (auto it : adjList[vertexNames[i]])
        {
            cout << "(" << it.first << ", " << it.second << ") ";
        }
        cout << endl;
    }

    bool visited[MAX];
    memset(visited, false, sizeof(visited));
    DFS(0, visited);
    bool connected = true;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            connected = false;
            break;
        }
    }
    if (connected)
        cout << "\nThe graph is Connected\n";
    else
        cout << "\nThe graph is Not Connected\n";

    vector<Edge> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                edges.push_back({i, j, adjMatrix[i][j]});
            }
        }
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    memset(parent, -1, sizeof(parent));
    int kruskalCost = 0;
    cout << "\nKruskal's Minimum Spanning Tree Edges:\n";
    for (auto e : edges)
    {
        int u_set = find(e.u);
        int v_set = find(e.v);
        if (u_set != v_set)
        {
            cout << vertexNames[e.u] << " - " << vertexNames[e.v] << " : " << e.weight << endl;
            kruskalCost += e.weight;
            union_set(u_set, v_set);
        }
    }
    cout << "Total cost using Kruskal's: " << kruskalCost << endl;

    int key[MAX], mstSet[MAX];
    for (int i = 0; i < n; i++)
        key[i] = 1e9, mstSet[i] = 0;
    key[0] = 0;
    int primCost = 0;

    for (int i = 0; i < n; i++)
    {
        int u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!mstSet[j] && (u == -1 || key[j] < key[u]))
                u = j;
        }
        mstSet[u] = 1;
        primCost += key[u];
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[u][j] && !mstSet[j] && adjMatrix[u][j] < key[j])
            {
                key[j] = adjMatrix[u][j];
            }
        }
    }
    cout << "Total cost using Prim's: " << primCost << endl;
    return 0;
}
