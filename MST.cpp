#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100;
int n, adjMatrix[MAX][MAX], parent[MAX];
string vertexNames[MAX];
map<string, vector<pair<string, int>>> adjList;

struct Edge {
    int u, v, weight;
};

int find(int i) {
    return parent[i] == -1 ? i : parent[i] = find(parent[i]);
}

void union_set(int u, int v) {
    parent[find(u)] = find(v);
}

void DFS(int i, bool visited[]) {
    visited[i] = true;
    for (auto &neighborPair : adjList[vertexNames[i]]) {
        const string &neighbor = neighborPair.first;
        int j = find_if(vertexNames, vertexNames + n, [&](const string &v) { return v == neighbor; }) - vertexNames;
        if (!visited[j]) DFS(j, visited);
    }
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;
    for (int i = 0; i < n; i++) cin >> vertexNames[i];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char conn;
            cout << "Connection between " << vertexNames[i] << " and " << vertexNames[j] << " (y/n)? ";
            cin >> conn;
            if (conn == 'y') {
                int w;
                cin >> w;
                adjMatrix[i][j] = adjMatrix[j][i] = w;
                adjList[vertexNames[i]].push_back({vertexNames[j], w});
                adjList[vertexNames[j]].push_back({vertexNames[i], w});
            }
        }
    }

    bool visited[MAX] = {false};
    DFS(0, visited);
    cout << (all_of(visited, visited + n, [](bool v) { return v; }) ? "Graph is Connected\n" : "Graph is Not Connected\n");

    vector<Edge> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adjMatrix[i][j]) edges.push_back({i, j, adjMatrix[i][j]});

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });
    memset(parent, -1, sizeof(parent));
    int kruskalCost = 0;
    cout << "Kruskal's MST:\n";
    for (auto &[u, v, w] : edges) {
        if (find(u) != find(v)) {
            cout << vertexNames[u] << " - " << vertexNames[v] << " : " << w << endl;
            kruskalCost += w;
            union_set(u, v);
        }
    }
    cout << "Kruskal's Cost: " << kruskalCost << endl;

    int key[MAX], mstSet[MAX] = {0}, primCost = 0;
    fill(key, key + n, 1e9);
    key[0] = 0;

    for (int i = 0; i < n; i++) {
        int u = min_element(key, key + n, [&](int a, int b) { return !mstSet[a] && (mstSet[b] || a < b); }) - key;
        mstSet[u] = 1;
        primCost += key[u];
        for (int v = 0; v < n; v++)
            if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) key[v] = adjMatrix[u][v];
    }
    cout << "Prim's Cost: " << primCost << endl;
    return 0;
}
