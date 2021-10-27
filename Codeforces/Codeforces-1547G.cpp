/*
Problem: https://codeforces.com/problemset/problem/1547/G

General idea:
    Traverse graph using DFS. For each vertex 'u', store paths leading to it (or -1 if there was cycle detected - inifinite paths).
	For each of it`s neighbours 'v':
		- if 'v has already been visited or we detected cycle before getting to 'u': start DFS from 'v' with v.paths = -1 (cycle)
		- else, if we still haven`t found multiple paths leading to 'v': start DFS from 'v' with v.paths = max(u.paths, v.paths + 1)
*/

#include <iostream>
#include <list>
 
using namespace std;
 
struct graph
{
    int paths = 0;
    bool visited = false;
    list<int> neighbours;
};
 
void dfs(graph* G, int u, int val)
{
    G[u].visited = true;
    if (val == -1)
        G[u].paths = val;
    else
        G[u].paths = max(G[u].paths + 1, val);
 
    for (int v: G[u].neighbours)
    {
        if (G[v].paths != -1)
        {
            if (G[v].visited || G[u].paths == -1)
                dfs(G, v, -1);
            else
                if (G[v].paths < 2)
                    dfs(G, v, G[u].paths);
        }
    }
 
    G[u].visited = false;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    int t, n, m, a, b;
    graph* G;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        G = new graph[n + 1];
        while (m--)
        {
            cin >> a >> b;
            G[a].neighbours.push_back(b);
        }
 
        dfs(G, 1, 0);
 
        for (int i=1; i<=n; ++i)
            cout << G[i].paths << " ";
        cout << endl;
 
        delete[] G;
    }
}