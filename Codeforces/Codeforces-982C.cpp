/*
Problem: https://codeforces.com/problemset/problem/982/C

General Idea:
    Greedy aproach: starting from leaves, traverse tree in root`s direction and make a cut whenever
    the number of processed vertices is even.
    This can be easily done using DFS which returns current size of a subtree. The cut will be made
    at the end of procedure.
*/

#include <iostream>
#include <list>
using namespace std;

struct result
{
    int cuts, left_size;
};

result DFS(list<int> * graph, int v, bool * visited)
{
    visited[v]=true;
    int cuts=0;
    int curr_size=1;
    result pom;

    for (int x: graph[v])
        if (!visited[x])
        {
            pom=DFS(graph,x,visited);
            cuts+=pom.cuts;
            curr_size+=pom.left_size;
        }

    if (curr_size%2==0)
        return {cuts+1,0};
    else
        return {cuts,curr_size};
}

int main ()
{
    ios_base::sync_with_stdio(false);
    int n,u,w;
    cin >> n;
    list<int> graph[n+1];
    bool visited[n+1]={};
    for (int i=1;i<n;i++)
    {
        cin >> u >> w;
        graph[u].push_back(w);
        graph[w].push_back(u);
    }

    result source =  DFS(graph,1,visited);

    if (source.left_size==0)
        cout << source.cuts - 1;
    else
        cout << -1;
}
