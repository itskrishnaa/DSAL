#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
using namespace std;
const int MAX = 100;
int n;
string vertex[MAX];
int adjMatrix[MAX][MAX];
map<string, vector<pair<string, int>>> adjList;
bool visited[MAX];
int getIndex(string v)
{
    for (int i = 0; i < n; i++)
    {
        if (vertex[i] == v)
            return i;
    }
    return -1;
}
void DFS(int i)
{
    cout << vertex[i] << " ";
    visited[i] = true;
    for (int j = 0; j < n; j++)
    {
        if (adjMatrix[i][j] && !visited[j])
        {
            DFS(j);
        }
    }
}
void BFS(int start)
{
    queue<int> q;
    memset(visited, false, sizeof(visited));
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << vertex[u] << " ";
        for (auto it : adjList[vertex[u]])
        {
            int v = getIndex(it.first);
            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
int main()
{
    cout << "Enter number of vertices: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter name of vertex " << i + 1 << ": ";
        cin >> vertex[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            char ch;
            cout << "Is there a connection between " << vertex[i] << " and " << vertex[j] << " (y/n)? ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                int w;
                cout << "Enter weight: ";
                cin >> w;
                adjMatrix[i][j] = w;
                adjMatrix[j][i] = w;
                adjList[vertex[i]].push_back({vertex[j], w});
                adjList[vertex[j]].push_back({vertex[i], w});
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
        cout << vertex[i] << " -> ";
        for (auto it : adjList[vertex[i]])
        {
            cout << "(" << it.first << ", " << it.second << ") ";
        }
        cout << endl;
    }
    memset(visited, false, sizeof(visited));
    cout << "\nDFS Traversal: ";
    DFS(0);

    cout << "\nBFS Traversal: ";
    BFS(0);
    return 0;
}
