/*
Problem: https://codeforces.com/problemset/problem/986/A

General Idea:
    For each vertex 'u' keep track of each good acquired so far. Use BFS to calculate costs of shipping each good to each city.
	Stop when all cities have enough good to organise a fair.
*/

#include <iostream>
#include <set>
#include <stack>
#include <algorithm>
#include <list>
using namespace std;
 
struct graph
{
    int result=0;
    list <int> adj;
    bool * acq;
    int acq_size=1;
};
 
int main ()
{
    ios_base::sync_with_stdio(false);
    int v,e,u,w,k,s;
    cin >> v >> e >> k >> s;
    graph G[v+1];
    for (int i=1;i<=v;i++)
    {
        G[i].acq=new bool [k+1];
        for (int j=1;j<=k;j++)
            G[i].acq[j]=false;
    }
 
    stack <pair <int,int>> * g1=new stack <pair <int,int>>, *g2=new stack <pair <int,int>>;
    int left=v, order=1, town, good;
 
    for (int i=1;i<=v;i++)
    {
        cin >> u;
        G[i].acq[u]=true;
        g1->push({i,u});
    }
 
    for (int i=0;i<e;i++)
    {
        cin >> u >> w;
        G[u].adj.push_back(w);
        G[w].adj.push_back(u);
    }
 
    if (s!=1)
    while(left)
    {
        while(!g1->empty())
        {
            town=g1->top().first;
            good=g1->top().second;
            g1->pop();
 
            for (int x: G[town].adj)
                if (G[x].acq_size < s && !G[x].acq[good])
                {
                    G[x].result+=order;
                    G[x].acq[good]=true;
                    G[x].acq_size++;
                    g2->push({x,good});
                    if (G[x].acq_size==s)
                        left--;
                }
        }
        swap(g1,g2);
        order++;
    }
 
    for (int i=1;i<=v;i++)
        cout << G[i].result << " ";
 
}