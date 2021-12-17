// программа проверки графа на двудольность
#include <bits/stdc++.h>
using namespace std;
 
// функция добавления ребра в граф
void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
// функция проверки графа на двудольность
bool isBipartite(vector<int> adj[], int v,
                 vector<bool>& visited, vector<int>& color)
{
 
    for (int u : adj[v]) {
 
        if (visited[u] == false) {
 
            visited[u] = true;
 
            color[u] = !color[v];
 
            if (!isBipartite(adj, u, visited, color))
                return false;
        }
 
        else if (color[u] == color[v])
            return false;
    }
    return true;
}

// главный метод
int main()
{
    int N = 6;
 
    vector<int> adj[N + 1];
 
    vector<bool> visited(N + 1);
 
    vector<int> color(N + 1);
 
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 6);
    addEdge(adj, 6, 1);
 
    visited[1] = true;
 
    color[1] = 0;
 
    if (isBipartite(adj, 1, visited, color)) {
        cout << "Graph is Bipartite\n";
    }
    else {
        cout << "Graph is not Bipartite\n";
    }
 
    return 0;
}
